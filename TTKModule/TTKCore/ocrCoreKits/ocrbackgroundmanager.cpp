#include "ocrbackgroundmanager.h"

OCRBackgroundManager::OCRBackgroundManager()
    : m_skinColor(Qt::white)
{

}

void OCRBackgroundManager::addObserver(QObject *object)
{
    m_observer << object;
    connect(this, SIGNAL(backgroundChanged()), object, SLOT(backgroundChanged()));
}

void OCRBackgroundManager::removeObserver(QObject *object)
{
    m_observer.removeAll(object);
    disconnect(this, SIGNAL(backgroundChanged()), object, SLOT(backgroundChanged()));
}

void OCRBackgroundManager::setBackgroundUrl(const QString &path)
{
    m_background = path;
}

QString OCRBackgroundManager::backgroundUrl() const
{
    return m_background;
}

void OCRBackgroundManager::setBackgroundColor(const QColor &color)
{
    m_skinColor = color;
}

QColor OCRBackgroundManager::backgroundColor() const
{
    return m_skinColor;
}
