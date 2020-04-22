#include "ocrbackgroundmanager.h"

OCRBackgroundManager::OCRBackgroundManager()
{
    m_skinColor = QColor(Qt::white);
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

void OCRBackgroundManager::setMBackground(const QString &path)
{
    m_background = path;
}

QString OCRBackgroundManager::getMBackground() const
{
    return m_background;
}

void OCRBackgroundManager::setMBackgroundColor(const QColor &color)
{
    m_skinColor = color;
}

QColor OCRBackgroundManager::getMBackgroundColor() const
{
    return m_skinColor;
}

void OCRBackgroundManager::backgroundHasChanged()
{
    emit backgroundChanged();
}
