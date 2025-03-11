#include "ocrbackgroundmanager.h"

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

void OCRBackgroundManager::setBackgroundUrl(const QString &path) noexcept
{
    m_background = path;
}

QString OCRBackgroundManager::backgroundUrl() const noexcept
{
    return m_background;
}
