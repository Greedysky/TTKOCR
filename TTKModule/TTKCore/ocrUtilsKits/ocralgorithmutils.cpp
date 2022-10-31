#include "ocralgorithmutils.h"
#include "ttkcryptographichash.h"

#include <QCryptographicHash>

QByteArray OCRUtils::Algorithm::sha1(const QByteArray &data)
{
    return QCryptographicHash::hash(data, QCryptographicHash::Sha1);
}

QString OCRUtils::Algorithm::mdII(const QString &data, bool encode)
{
    TTKCryptographicHash hash;
    return encode ? hash.encrypt(data, "13.015?sdf;/?dd") : hash.decrypt(data, "13.015?sdf;/?dd");
}

