#include "ocrimageutils.h"

#include <QBuffer>
#include <QPixmap>

QByteArray TTK::Image::generatePixmapData(const QPixmap &input)
{
    if(input.isNull())
    {
        return {};
    }

    QByteArray data;
    QBuffer buffer(&data);
    if(buffer.open(QIODevice::WriteOnly))
    {
        input.save(&buffer, "jpg");
    }
    buffer.close();
    return data;
}
