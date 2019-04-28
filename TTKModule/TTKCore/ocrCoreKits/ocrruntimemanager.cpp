#include "ocrruntimemanager.h"
#include "ocrcoreutils.h"
#include "ocrcodecutils.h"

#include <QFont>
#include <QApplication>

OCRRunTimeManager::OCRRunTimeManager()
{

}

QString OCRRunTimeManager::getClassName()
{
    return "OCRRunTimeManager";
}

void OCRRunTimeManager::run() const
{
    M_LOGGER_INFO("OCRApplication Begin");

#ifndef TTK_GREATER_NEW
    OCRUtils::Codec::setLocalCodec();
#endif

    M_LOGGER_INFO("Load Translation");
    ///////////////////////////////////////////////////////
    QFont font;
#ifdef Q_OS_UNIX
    font.setPixelSize(13);
#endif
    qApp->setFont(font);
    ///////////////////////////////////////////////////////
    M_LOGGER_INFO("End load translation");
}

QString OCRRunTimeManager::translator() const
{
    return OCRUtils::Core::getLanguageName(0);
}
