#include "ocrwidgetutils.h"
#include "ocrobject.h"

#include <QBuffer>
#include <QPainter>
#include <QFileDialog>

QByteArray OCRUtils::Widget::GeneratePixmapData(const QPixmap &pix)
{
    if(pix.isNull())
    {
        return QByteArray();
    }

    QByteArray data;
    QBuffer buffer(&data);
    if(buffer.open(QIODevice::WriteOnly))
    {
        pix.save(&buffer, JPG_FILE_PREFIX);
    }
    buffer.close();
    return data;
}

QStringList OCRUtils::Widget::getOpenFilesDialog(QWidget *obj, const QString &filter)
{
    return QFileDialog::getOpenFileNames(obj, QObject::tr("choose a filename to open under"), QDir::currentPath(), filter);
}
