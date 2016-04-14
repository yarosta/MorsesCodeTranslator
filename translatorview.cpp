#include "translatorview.h"

TranslatorView::TranslatorView(QWidget *parent) : QWidget(parent)
{
    translatorModel = new TranslatorModel(this);

    QVBoxLayout* mainLayout = new QVBoxLayout();

    mainLayout->addSpacing(10);

    labelNormalText = new QLabel("Normal text:");
    mainLayout->addWidget(labelNormalText);

    textEditNormalText = new QPlainTextEdit();
    mainLayout->addWidget(textEditNormalText);

    QHBoxLayout* normalTextButtons = new QHBoxLayout();

    buttonGenerateMorseCode = new QPushButton(QIcon(":img/Arrow_Down"),"Generate Morse's Code");
    buttonOpenFromFileNormalText = new QPushButton(QIcon(":img/Open_Folder"),"Open from file ..");
    buttonSaveToFileNormalText = new QPushButton(QIcon(":img/Save"),"Save to file ..");

    normalTextButtons->addStretch(10);
    normalTextButtons->addWidget(buttonGenerateMorseCode);
    normalTextButtons->addSpacing(30);
    normalTextButtons->addWidget(buttonOpenFromFileNormalText);
    normalTextButtons->addWidget(buttonSaveToFileNormalText);
    normalTextButtons->addStretch(10);

    mainLayout->addLayout(normalTextButtons);
    mainLayout->addSpacing(10);

    labelMorseCodeText = new QLabel("Morse's code text:");
    mainLayout->addWidget(labelMorseCodeText);

    textEditMorseCode = new QPlainTextEdit();
    mainLayout->addWidget(textEditMorseCode);

    QHBoxLayout* morseCodeButtons = new QHBoxLayout();

    buttonGenerateNormalText = new QPushButton(QIcon(":img/Arrow_Up"),"Generate Normal Text");
    buttonOpenFromFileMorseCode = new QPushButton(QIcon(":img/Open_Folder"),"Open from file ..");
    buttonSaveToFileMorseCode = new QPushButton(QIcon(":img/Save"),"Save to file ..");

    morseCodeButtons->addStretch(10);
    morseCodeButtons->addWidget(buttonGenerateNormalText);
    morseCodeButtons->addSpacing(30);
    morseCodeButtons->addWidget(buttonOpenFromFileMorseCode);
    morseCodeButtons->addWidget(buttonSaveToFileMorseCode);
    morseCodeButtons->addStretch(10);

    mainLayout->addLayout(morseCodeButtons);
    mainLayout->addSpacing(10);

    setLayout(mainLayout);

    connect(buttonGenerateMorseCode,SIGNAL(clicked()),this,SLOT(translateIntoMorseCode()));
    // after clicking buttonGenerateMorseCode content of textEditNormalText(where user writes normal text) will be rewriting into translatorModel->normalText
    // content of translatorModel->normalText will be translate into Morse's code and will be saved in translatorModel->morseCodeText
    // function translatorModel->translateIntoMorseCode will emit SIGNAL morseCodeTextChanged
    connect(translatorModel,SIGNAL(morseCodeTextChanged()),this,SLOT(updateTextEditMorseCode()));
    // after that content of textEditMorseCode(where user writes Morse's code text) will be update according with content of translateModel->morseCodeText

    connect(buttonGenerateNormalText,SIGNAL(clicked()),this,SLOT(translateIntoNormalText()));
    // analogous to translating into Morse's code
    connect(translatorModel,SIGNAL(normalTextChanged()),this,SLOT(updateTextEditNormalText()));

    connect(buttonOpenFromFileNormalText,SIGNAL(clicked()),this,SLOT(openNormalTextFile()));
    connect(buttonSaveToFileNormalText,SIGNAL(clicked()),this,SLOT(saveNormalTextFile()));

    connect(buttonOpenFromFileMorseCode,SIGNAL(clicked()),this,SLOT(openMorseCodeTextFile()));
    connect(buttonSaveToFileMorseCode,SIGNAL(clicked()),this,SLOT(saveMorseCodeTextFile()));
}

void TranslatorView::translateIntoMorseCode()
{   
    translatorModel->rewriteNormalText(textEditNormalText->toPlainText());
    translatorModel->translateIntoMorseCode();
}

void TranslatorView::updateTextEditMorseCode()
{
    textEditMorseCode->setPlainText(translatorModel->getMorseCodeText());
}

void TranslatorView::translateIntoNormalText()
{
    translatorModel->rewriteMorseCodeText(textEditMorseCode->toPlainText());
    translatorModel->translateIntoNormalText();
}

void TranslatorView::updateTextEditNormalText()
{
    textEditNormalText->setPlainText(translatorModel->getNormalText());
}

void TranslatorView::openNormalTextFile()
{
    QString fileContent;
    fileContent = openFile();
    textEditNormalText->setPlainText(fileContent);
}

void TranslatorView::saveNormalTextFile()
{
    QString fileContent;
    fileContent = textEditNormalText->toPlainText();
    saveFile(fileContent);
}

void TranslatorView::openMorseCodeTextFile()
{
    QString fileContent;
    fileContent = openFile();
    textEditMorseCode->setPlainText(fileContent);
}

void TranslatorView::saveMorseCodeTextFile()
{
    QString fileContent;
    fileContent = textEditMorseCode->toPlainText();
    saveFile(fileContent);
}

QString TranslatorView::openFile()
{
    QString fileContent;
    fileContent = "";
    QString newFileName = QFileDialog::getOpenFileName(this);
    if (!newFileName.isEmpty())
    {
        QFile file (newFileName);
        if (file.open (QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&file);
            fileContent = in.readAll();
            file.close();
        }
    }
    return fileContent;
}

void TranslatorView::saveFile(QString fileContent)
{
    QString newFileName = QFileDialog::getSaveFileName(this);
    if(!newFileName.isEmpty())
    {
        QFile file (newFileName);
        if (file.open (QFile::WriteOnly | QFile::Text))
        {
            QTextStream out (&file);
            out << fileContent;
            file.close();
        }
    }
}
