#ifndef TRANSLATORWINDOW_H
#define TRANSLATORWINDOW_H

#include <QMainWindow>
#include "translatorview.h"

namespace Ui {
class TranslatorWindow;
}

class TranslatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TranslatorWindow(QWidget *parent = 0);
    ~TranslatorWindow();

private:
    Ui::TranslatorWindow *ui;
        TranslatorView* translatorView;
};

#endif // TRANSLATORWINDOW_H
