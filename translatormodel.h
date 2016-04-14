#ifndef TRANSLATORMODEL_H
#define TRANSLATORMODEL_H

#include <QObject>
#include <QMap>

class TranslatorModel : public QObject
{
    Q_OBJECT
public:
    explicit TranslatorModel(QObject *parent = 0);

    const QString& getMorseCodeText();
    const QString& getNormalText();

    void rewriteNormalText(QString text);
    void translateIntoMorseCode();
    QString translateCharacter(QChar& character);

    void rewriteMorseCodeText(QString text);
    void translateIntoNormalText();
    QChar translateMorseCharacter(QString character);

signals:
    void morseCodeTextChanged();
    void normalTextChanged();

public slots:

private:
    QString normalText;
    QString morseCodeText;
    QMap<int,QString> alphabetOfMorse;
};

#endif // TRANSLATORMODEL_H
