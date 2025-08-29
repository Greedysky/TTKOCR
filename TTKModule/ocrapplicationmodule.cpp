#include "ocrapplicationmodule.h"
#include "ocrbackgroundmanager.h"

#include <QApplication>

OCRApplicationModule *OCRApplicationModule::m_instance = nullptr;

OCRApplicationModule::OCRApplicationModule(QObject *parent)
    : QObject(parent)
{
    m_instance = this;

    G_BACKGROUND_PTR->setBackgroundUrl(":/image/lb_background");
}

OCRApplicationModule::~OCRApplicationModule()
{
    Q_CLEANUP_RESOURCE(TTKModule);
}

OCRApplicationModule *OCRApplicationModule::instance()
{
    return m_instance;
}

void OCRApplicationModule::quit()
{
    qApp->exit();
}
