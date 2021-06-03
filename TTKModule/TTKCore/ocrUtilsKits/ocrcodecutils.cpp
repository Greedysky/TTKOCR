#include "ocrcodecutils.h"
#include "ocrobject.h"

#include <QTextCodec>

QString OCRUtils::Codec::toUnicode(const char *chars, const char *format)
{
    QTextCodec *codec = QTextCodec::codecForName(format);
    return codec->toUnicode(chars);
}

QString OCRUtils::Codec::toUnicode(const QByteArray &chars, const char *format)
{
    QTextCodec *codec = QTextCodec::codecForName(format);
    return codec->toUnicode(chars);
}

QByteArray OCRUtils::Codec::fromUnicode(const QString &chars, const char *format)
{
    QTextCodec *codec = QTextCodec::codecForName(format);
    return codec->fromUnicode(chars);
}

void OCRUtils::Codec::setLocalCodec(const char *format)
{
    QTextCodec *codec = QTextCodec::codecForName(format);
    QTextCodec::setCodecForLocale(codec);
#if !TTK_QT_VERSION_CHECK(5,0,0)
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif
}

const char* OCRUtils::Codec::toLocal8Bit(const QString &str)
{
    return str.toLocal8Bit().constData();
}

const char* OCRUtils::Codec::toUtf8(const QString &str)
{
    return str.toUtf8().constData();
}
