#ifndef TRANSLATORVIEW_H
#define TRANSLATORVIEW_H

#include <QWidget>
#include "translatormodel.h"
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QTextStream>

class TranslatorView : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorView(QWidget *parent = 0);
    QString openFile();
    void saveFile(QString fileContent);
signals:

public slots:
    void translateIntoMorseCode();
    void updateTextEditMorseCode();

    void translateIntoNormalText();
    void updateTextEditNormalText();

    void openNormalTextFile();
    void saveNormalTextFile();

    void openMorseCodeTextFile();
    void saveMorseCodeTextFile();

private:
    TranslatorModel* translatorModel;

    QLabel* labelNormalText;
    QPlainTextEdit* textEditNormalText;
    QPushButton* buttonGenerateMorseCode;
    QPushButton* buttonOpenFromFileNormalText;
    QPushButton* buttonSaveToFileNormalText;

    QLabel* labelMorseCodeText;
    QPlainTextEdit* textEditMorseCode;
    QPushButton* buttonGenerateNormalText;
    QPushButton* buttonOpenFromFileMorseCode;
    QPushButton* buttonSaveToFileMorseCode;
};

#endif // TRANSLATORVIEW_H
