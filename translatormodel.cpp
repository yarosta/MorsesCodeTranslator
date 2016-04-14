#include "translatormodel.h"

TranslatorModel::TranslatorModel(QObject *parent) : QObject(parent)
{
    normalText="";
    morseCodeText="";

    // big letters
    alphabetOfMorse.insert(65,".-");
    alphabetOfMorse.insert(66,"-...");
    alphabetOfMorse.insert(67,"-.-.");
    alphabetOfMorse.insert(68,"-..");
    alphabetOfMorse.insert(69,".");
    alphabetOfMorse.insert(70,"..-.");
    alphabetOfMorse.insert(71,"--.");
    alphabetOfMorse.insert(72,"....");
    alphabetOfMorse.insert(73,"..");
    alphabetOfMorse.insert(74,".---");
    alphabetOfMorse.insert(75,"-.-");
    alphabetOfMorse.insert(76,".-..");
    alphabetOfMorse.insert(77,"--");
    alphabetOfMorse.insert(78,"-.");
    alphabetOfMorse.insert(79,"---");
    alphabetOfMorse.insert(80,".--.");
    alphabetOfMorse.insert(81,"--.-");
    alphabetOfMorse.insert(82,".-.");
    alphabetOfMorse.insert(83,"...");
    alphabetOfMorse.insert(84,"-");
    alphabetOfMorse.insert(85,"..-");
    alphabetOfMorse.insert(86,"...-");
    alphabetOfMorse.insert(87,".--");
    alphabetOfMorse.insert(88,"-..-");
    alphabetOfMorse.insert(89,"-.--");
    alphabetOfMorse.insert(90,"--..");

    // digits
    alphabetOfMorse.insert(48,"-----"); // 0
    alphabetOfMorse.insert(49,".----");
    alphabetOfMorse.insert(50,"..---");
    alphabetOfMorse.insert(51,"...--");
    alphabetOfMorse.insert(52,"....-");
    alphabetOfMorse.insert(53,".....");
    alphabetOfMorse.insert(54,"-....");
    alphabetOfMorse.insert(55,"--...");
    alphabetOfMorse.insert(56,"---..");
    alphabetOfMorse.insert(57,"----."); // 9

    // other characters
    alphabetOfMorse.insert(59,"-.-.-."); // ;
    alphabetOfMorse.insert(58,"---..."); // :
    alphabetOfMorse.insert(39,".----."); // '
    alphabetOfMorse.insert(34,".-..-."); // "
    alphabetOfMorse.insert(47,"-..-."); // /
    alphabetOfMorse.insert(92,".-..."); // \ //
    alphabetOfMorse.insert(61,"-...-"); // =
    alphabetOfMorse.insert(43,".-.-."); // +
    alphabetOfMorse.insert(45,"-....-"); // -
    alphabetOfMorse.insert(95,"..--.-"); // _
    alphabetOfMorse.insert(41,"-.--.-"); // )
    alphabetOfMorse.insert(40,"-.--."); // (
    alphabetOfMorse.insert(94,".-.-."); // ^
    alphabetOfMorse.insert(37,"...-."); // %
    alphabetOfMorse.insert(36,".-..."); // $
    alphabetOfMorse.insert(64,"...-.-"); // @
    alphabetOfMorse.insert(126,"-.-.-"); // ~
    alphabetOfMorse.insert(46,".-.-.-"); // .
    alphabetOfMorse.insert(44,"--..--"); // ,
    alphabetOfMorse.insert(63,"..--.."); // ?
}

const QString& TranslatorModel::getMorseCodeText()
{
    return morseCodeText;
}

const QString& TranslatorModel::getNormalText()
{
    return normalText;
}

void TranslatorModel::rewriteNormalText(QString text)
{
    normalText = text;
}

void TranslatorModel::translateIntoMorseCode()
{
    morseCodeText="";
    int textLength;
    textLength = normalText.size();
    for (int actualCharacter=0; actualCharacter<textLength; actualCharacter++)
    {
        QChar character = normalText.at(actualCharacter);
        QString morseCode = translateCharacter(character);
        morseCodeText += morseCode;
        if (actualCharacter < (textLength-1)) morseCodeText+=" "; // adding space at the end of character, except end of entire text
    }
    emit morseCodeTextChanged();
}

QString TranslatorModel::translateCharacter(QChar& character)
{
    int unicode;
    unicode = character.unicode();
    // --- changing small letters to big letters ---
    if(unicode >= 97 && unicode <= 122)
    {
        unicode-=32;
    }
    QString morseCode="";
    morseCode = alphabetOfMorse.value(unicode);
    return morseCode;
}

void TranslatorModel::rewriteMorseCodeText(QString text)
{
    morseCodeText = text;
}

void TranslatorModel::translateIntoNormalText()
{
    normalText = "";
    int textLength;
    textLength = morseCodeText.size();
    int beginOfCharacter;
    beginOfCharacter = 0; // index of begin of actual character
    int actualPosition;
    actualPosition = 0;
    while (actualPosition < textLength)
    {
        if (morseCodeText.at(actualPosition) == ' ' || actualPosition == (textLength-1))
        {
            QString character;
            if (actualPosition == (textLength-1) && morseCodeText.at(actualPosition) != ' ') actualPosition += 1;
            // if the last character of analising text isn't a space I must to increment actualPosition to correct creating string of morse's code characters
            character = morseCodeText.mid(beginOfCharacter, actualPosition - beginOfCharacter);
            QChar normalCharacter;
            normalCharacter = translateMorseCharacter(character);
            normalText += normalCharacter;
            beginOfCharacter = actualPosition + 1;
            if (morseCodeText.at(actualPosition) == ' ' && actualPosition != (textLength-1))
            // it's a case when there're two spaces in Morse's code text(end of word)
            {
                if (morseCodeText.at(actualPosition+1) == ' ')
                {
                    normalText += " ";
                    actualPosition++;
                    beginOfCharacter = actualPosition + 1;
                }
            }
        }
        actualPosition++;
    }
    emit normalTextChanged();
}

QChar TranslatorModel::translateMorseCharacter(QString character)
{
    int unicode;
    unicode = alphabetOfMorse.key(character);
    QChar normalCharacter(unicode);
    return normalCharacter;
}
