#include "ocralgorithmutils.h"
#include "ocrcryptographichash.h"

#include <QCryptographicHash>

QByteArray OCRUtils::Algorithm::md5(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Md5);
}

QByteArray OCRUtils::Algorithm::sha1(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Sha1);
}

QString OCRUtils::Algorithm::mdII(const QString &data, bool encode)
{
    OCRCryptographicHash hash;
    return encode ? hash.encrypt(data, ALG_URL_KEY) : hash.decrypt(data, ALG_URL_KEY);
}

QString OCRUtils::Algorithm::mdII(const QString &data, const QString &key, bool encode)
{
    OCRCryptographicHash hash;
    return encode ? hash.encrypt(data, key) : hash.decrypt(data, key);
}
