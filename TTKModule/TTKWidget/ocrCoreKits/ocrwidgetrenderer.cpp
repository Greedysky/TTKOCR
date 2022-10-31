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

    m_background->setPixmap(QPixmap(G_BACKGROUND_PTR->background()).scaled(size));
}
