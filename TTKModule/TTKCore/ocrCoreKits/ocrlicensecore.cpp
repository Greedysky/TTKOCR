#include "ocrlicensecore.h"
#include "ocralgorithmutils.h"

#include <QStringList>
#include <QNetworkInterface>

#define VALUE0   "ds231'332c53sd3!3d50147562s21.^6"
#define VALUE1   ".,lflfgdfKfdgdf2031..s121&&%%##"

OCRLicenseCore::OCRLicenseCore(QObject *parent)
    : QObject(parent)
{

}

QString OCRLicenseCore::getEncodeKey(const QString &key)
{
    return splitString(key.toUtf8(), VALUE1);
}

bool OCRLicenseCore::checkLicense(const QString &str)
{
    for(const QString &key : getCharacteristicStrings())
    {
        if(str == getEncodeKey(key))
        {
            return true;
        }
    }
    return false;
}

QString OCRLicenseCore::getCharacteristicString()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    if(!nets.isEmpty())
    {
        QString adds = nets.first().hardwareAddress();
        return splitString(adds.toUtf8(), VALUE0);
    }
    return QString();
}

QString OCRLicenseCore::getCharacteristicStringNormal()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    if(!nets.isEmpty())
    {
        QString adds = nets.first().hardwareAddress();
        return hmacSha1(adds.toUtf8(), VALUE0).toHex().mid(15, 10);
    }
    return QString();
}

QStringList OCRLicenseCore::getCharacteristicStrings()
{
    QStringList data;
    for(const QNetworkInterface &nets : QNetworkInterface::allInterfaces())
    {
        data << splitString(nets.hardwareAddress().toUtf8(), VALUE0);
    }
    return data;
}

QByteArray OCRLicenseCore::hmacSha1(const QByteArray &data, const QByteArray &key)
{
    int blockSize = 64;
    QByteArray newSecretKey = key;
    if(newSecretKey.length() > blockSize)
    {
        newSecretKey = OCRUtils::Algorithm::sha1(newSecretKey);
    }

    QByteArray innerPadding(blockSize, char(0x36));
    QByteArray outerPadding(blockSize, char(0x5c));

    for(int i = 0; i < key.length(); i++)
    {
        innerPadding[i] = innerPadding[i] ^ key.at(i);
        outerPadding[i] = outerPadding[i] ^ key.at(i);
    }

    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(data);
    total.append(OCRUtils::Algorithm::sha1(part));
    return OCRUtils::Algorithm::sha1(total);
}

QString OCRLicenseCore::splitString(const QByteArray &data, const QByteArray &key)
{
    QString value = hmacSha1(data, key).toHex().mid(10, 20);
    int count = value.count();
    for(int i=1; i<count/5; ++i)
    {
        value.insert(count - 5*i, "-");
    }
    return value;
}
