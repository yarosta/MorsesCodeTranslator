#include "translatorwindow.h"
#include "ui_translatorwindow.h"

TranslatorWindow::TranslatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TranslatorWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Morse's code translator.");
    this->setWindowIcon(QIcon(":img/Comment_Dots"));
    translatorView = new TranslatorView();
    setCentralWidget(translatorView);
}

TranslatorWindow::~TranslatorWindow()
{
    delete ui;
}
