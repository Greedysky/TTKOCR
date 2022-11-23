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
    TTK_INFO_STREAM("OCRApplication Begin");

    OCRUtils::Codec::setLocalCodec();

    TTK_INFO_STREAM("Load Translation");
    ///////////////////////////////////////////////////////
    QFont font;
#ifdef Q_OS_UNIX
    font.setPixelSize(13);
#endif
    qApp->setFont(font);
    ///////////////////////////////////////////////////////
    TTK_INFO_STREAM("End load translation");
}

QString OCRRunTimeManager::translator() const
{
    return OCRObject::languageCore(0);
}
