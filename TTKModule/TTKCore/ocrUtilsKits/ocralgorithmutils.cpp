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

QByteArray OCRUtils::Algorithm::hmacSha1(const QByteArray &data, const QByteArray &key)
{
    int blockSize = 64;
    QByteArray newSecretKey = key;
    if(newSecretKey.length() > blockSize)
    {
        newSecretKey = OCRUtils::Algorithm::sha1(newSecretKey);
    }

    QByteArray innerPadding(blockSize, char(0x36));
    QByteArray outerPadding(blockSize, char(0x5C));

    for(int i = 0; i < key.length(); i++)
    {
        innerPadding[i] = innerPadding[i] ^ key.at(i);
        outerPadding[i] = outerPadding[i] ^ key.at(i);
    }

    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(data);
    total.append(OCRUtils::Algorithm::sha1(part));
    QByteArray hashed = OCRUtils::Algorithm::sha1(total);
    return hashed;
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
