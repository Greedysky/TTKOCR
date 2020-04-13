#include "ocrwidgetutils.h"

#include <QComboBox>
#include <QBitmap>
#include <QPainter>
#include <QBuffer>
#include <QFileDialog>

void OCRUtils::Widget::setLabelFontSize(QWidget *widget, int size)
{
    QFont font = widget->font();
    font.setPointSize(size);
    widget->setFont(font);
}

QString OCRUtils::Widget::elidedText(const QFont &font, const QString &text,
                                       Qt::TextElideMode mode, int width)
{
    QFontMetrics ft(font);
    return ft.elidedText(text, mode, width);
}

void OCRUtils::Widget::setTransparent(QWidget *widget, int alpha)
{
    QPalette pal = widget->palette();
    pal.setBrush(QPalette::Base, QBrush(QColor(0xFF, 0xFF, 0xFF, alpha)));
    widget->setPalette(pal);
}

void OCRUtils::Widget::setComboBoxText(QComboBox *object, const QString &text)
{
    if(object->isEditable())
    {
        object->setEditText(text);
    }
    else
    {
        const int i = object->findText(text);
        if(i > -1)
        {
            object->setCurrentIndex(i);
        }
    }
}

void OCRUtils::Widget::widgetToRound(QWidget *w, int ratioX, int ratioY)
{
    w->setMask(getBitmapMask(w->rect(), ratioX, ratioY));
}

void OCRUtils::Widget::fusionPixmap(QPixmap &bg, const QPixmap &fg, const QPoint &pt)
{
    if(fg.isNull())
    {
        return;
    }

    QPainter painter(&bg);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.drawPixmap(pt.x(), pt.y(), fg);
    painter.end();
}

QPixmap OCRUtils::Widget::pixmapToRound(const QPixmap &src, const QSize &size, int ratioX, int ratioY)
{
    return pixmapToRound(src, QRect(QPoint(0, 0), size), ratioX, ratioY);
}

QPixmap OCRUtils::Widget::pixmapToRound(const QPixmap &src, const QRect &rect, int ratioX, int ratioY)
{
    if(src.isNull())
    {
        return QPixmap();
    }

    QPixmap image = src.scaled(rect.size());
    image.setMask(getBitmapMask(rect, ratioX, ratioY));
    return image;
}

QPixmap OCRUtils::Widget::pixmapToRound(const QPixmap &src, const QPixmap &mask, const QSize &size)
{
    if(src.isNull() || mask.isNull())
    {
        return QPixmap();
    }

    QPixmap image(mask);
    QPainter painter(&image);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.drawPixmap(0, 0, src.scaled(size));
    painter.end();

    return image;
}

QBitmap OCRUtils::Widget::getBitmapMask(const QRect &rect, int ratioX, int ratioY)
{
    QBitmap mask(rect.size());
    QPainter painter(&mask);
    painter.fillRect(rect, Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.drawRoundedRect(rect, ratioX, ratioY);
    return mask;
}

QByteArray OCRUtils::Widget::getPixmapData(const QPixmap &pix)
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

int OCRUtils::Widget::reRenderAlpha(int alpha, int value)
{
    return reRenderValue<int>(0xFF, alpha, value);
}

void OCRUtils::Widget::reRenderImage(int delta, const QImage *input, QImage *output)
{
    for(int w=0; w<input->width(); w++)
    {
        for(int h=0; h<input->height(); h++)
        {
            QRgb rgb = input->pixel(w, h);
            output->setPixel(w, h, qRgb(colorBurnTransform(qRed(rgb), delta),
                                        colorBurnTransform(qGreen(rgb), delta),
                                        colorBurnTransform(qBlue(rgb), delta)));
        }
    }
}

int OCRUtils::Widget::colorBurnTransform(int c, int delta)
{
    if(0 > delta || delta > 0xFF)
    {
        return c;
    }

    int result = (c - (int)(c*delta)/(0xFF - delta));
    if(result > 0xFF)
    {
        result = 0xFF;
    }
    else if(result < 0)
    {
        result = 0;
    }
    return result;
}

QString OCRUtils::Widget::getOpenFileDialog(QWidget *obj, const QString &title, const QString &filter)
{
    return QFileDialog::getOpenFileName(obj, title, QDir::currentPath(), filter);
}

QString OCRUtils::Widget::getOpenFileDialog(QWidget *obj, const QString &filter)
{
    return getOpenFileDialog(obj, QObject::tr("choose a filename to open under"), filter);
}

QString OCRUtils::Widget::getOpenFileDialog(QWidget *obj)
{
    return getOpenFileDialog(obj, "Images (*.png *.bmp *.jpg)");
}

QStringList OCRUtils::Widget::getOpenFilesDialog(QWidget *obj, const QString &title, const QString &filter)
{
    return QFileDialog::getOpenFileNames(obj, title, QDir::currentPath(), filter);
}

QStringList OCRUtils::Widget::getOpenFilesDialog(QWidget *obj, const QString &filter)
{
    return getOpenFilesDialog(obj, QObject::tr("choose a filename to open under"), filter);
}

QStringList OCRUtils::Widget::getOpenFilesDialog(QWidget *obj)
{
    return getOpenFilesDialog(obj, "Images (*.png *.bmp *.jpg)");
}

QString OCRUtils::Widget::getSaveFileDialog(QWidget *obj, const QString &title, const QString &filter)
{
    return QFileDialog::getSaveFileName(obj, title, QDir::currentPath(), filter);
}

QString OCRUtils::Widget::getSaveFileDialog(QWidget *obj, const QString &filter)
{
    return getSaveFileDialog(obj, QObject::tr("choose a filename to save under"), filter);
}

QString OCRUtils::Widget::getSaveFileDialog(QWidget *obj)
{
    return getSaveFileDialog(obj, "Images (*.png *.bmp *.jpg)");
}
