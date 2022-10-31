#include "ocrabstractmovewidget.h"
#include "ocrbackgroundmanager.h"

OCRAbstractMoveWidget::OCRAbstractMoveWidget(QWidget *parent)
    : OCRAbstractMoveWidget(true, parent)
{

}

OCRAbstractMoveWidget::OCRAbstractMoveWidget(bool transparent, QWidget *parent)
    : TTKAbstractMoveWidget(transparent, parent),
      OCRWidgetRenderer()
{
    G_BACKGROUND_PTR->addObserver(this);
}

OCRAbstractMoveWidget::~OCRAbstractMoveWidget()
{
    G_BACKGROUND_PTR->removeObserver(this);
}

void OCRAbstractMoveWidget::backgroundChanged()
{
    setBackgroundPixmap(size());
}

void OCRAbstractMoveWidget::show()
{
    setBackgroundPixmap(size());
    QWidget::show();
}
