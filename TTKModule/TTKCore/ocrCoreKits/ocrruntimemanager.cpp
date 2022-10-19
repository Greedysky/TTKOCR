#include "ocrruntimemanager.h"
#include "ocrcodecutils.h"
#include "ocrobject.h"

#include <QFont>
#include <QApplication>

namespace OCRObject
{
static QString languageCore(int index)
{
    QString lan(LANGUAGE_DIR_FULL);
    switch(index)
    {
        case 0: return lan.append("cn.ln");
        case 1: return lan.append("tc.ln");
        case 2: return lan.append("en.ln");
        default: return QString();
    }
}
}


OCRRunTimeManager::OCRRunTimeManager()
{

}

void OCRRunTimeManager::run() const
{
    TTK_LOGGER_INFO("OCRApplication Begin");

#if !TTK_QT_VERSION_CHECK(5,0,0)
    OCRUtils::Codec::setLocalCodec();
#endif

    TTK_LOGGER_INFO("Load Translation");
    ///////////////////////////////////////////////////////
    QFont font;
#ifdef Q_OS_UNIX
    font.setPixelSize(13);
#endif
    qApp->setFont(font);
    ///////////////////////////////////////////////////////
    TTK_LOGGER_INFO("End load translation");
}

QString OCRRunTimeManager::translator() const
{
    return OCRObject::languageCore(0);
}
