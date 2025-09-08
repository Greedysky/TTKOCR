#include "ocrwidgetrenderer.h"
#include "ocrbackgroundmanager.h"

OCRWidgetRenderer::OCRWidgetRenderer()
    : m_background(nullptr)
{

}

void OCRWidgetRenderer::setBackgroundPixmap(const QSize &size)
{
    if(!m_background)
    {
        return;
    }

    QPixmap pix(G_BACKGROUND_PTR->backgroundUrl());
    if(pix.isNull())
    {
        TTK_ERROR_STREAM("Load current pixmap data error, path is" << G_BACKGROUND_PTR->backgroundUrl());
        return;
    }

    m_background->setPixmap(pix.scaled(size));
}
