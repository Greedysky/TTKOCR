#include "ocrabstractmovedialog.h"
#include "ocrbackgroundmanager.h"

OCRAbstractMoveDialog::OCRAbstractMoveDialog(QWidget *parent)
    : OCRAbstractMoveDialog(true, parent)
{

}

OCRAbstractMoveDialog::OCRAbstractMoveDialog(bool transparent, QWidget *parent)
    : TTKAbstractMoveDialog(transparent, parent),
      OCRWidgetRenderer()
{
    G_BACKGROUND_PTR->addObserver(this);
}

OCRAbstractMoveDialog::~OCRAbstractMoveDialog()
{
    G_BACKGROUND_PTR->removeObserver(this);
}

void OCRAbstractMoveDialog::backgroundChanged()
{
    setBackgroundPixmap(size());
}

int OCRAbstractMoveDialog::exec()
{
    setBackgroundPixmap(size());
    return QDialog::exec();
}

void OCRAbstractMoveDialog::show()
{
    setBackgroundPixmap(size());
    QDialog::show();
}
