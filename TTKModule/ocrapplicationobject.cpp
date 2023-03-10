#include "ocrapplicationobject.h"
#include "ocrapplication.h"
#include "ocrbackgroundmanager.h"
#include "ocrfileutils.h"
#include "ttknumberdefine.h"

#include <QTimer>
#include <QPropertyAnimation>

OCRApplicationObject *OCRApplicationObject::m_instance = nullptr;

OCRApplicationObject::OCRApplicationObject(QObject *parent)
    : QObject(parent)
{
    m_instance = this;
    m_animation = new QPropertyAnimation(OCRApplication::instance(), "windowOpacity", this);

    G_BACKGROUND_PTR->setBackground(":/image/lb_background");
}

OCRApplicationObject::~OCRApplicationObject()
{
    cleanUp();
    Q_CLEANUP_RESOURCE(TTKOCR);
    delete m_animation;
}

OCRApplicationObject *OCRApplicationObject::instance()
{
    return m_instance;
}

void OCRApplicationObject::windowCloseAnimation()
{
    m_animation->stop();
    m_animation->setDuration(MT_S2MS / 2);
    m_animation->setStartValue(1.0f);
    m_animation->setEndValue(0.0f);
    m_animation->start();

    QTimer::singleShot(MT_S2MS, qApp, SLOT(quit()));
}

void OCRApplicationObject::cleanUp()
{
    TTK::File::removeRecursively(DIR_PREFIX);
    TTK::File::removeRecursively(DOWNLOAD_DIR_FULL);
}
