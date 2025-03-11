#include "ocrruntimemanager.h"
#include "ocrcodecutils.h"
#include "ocrobject.h"

#include <QFont>
#include <QApplication>

namespace TTK
{
    /*!
     * Generate core language resource.
     */
    static QString languageCore(int index);

}

QString TTK::languageCore(int index)
{
    QString lan(LANGUAGE_DIR_FULL);
    switch(index)
    {
        case 0: return lan.append("cn.ln");
        case 1: return lan.append("tc.ln");
        case 2: return lan.append("en.ln");
        default: return {};
    }
}


void OCRRunTimeManager::run() const
{
    TTK_INFO_STREAM("OCRApplication Run");

#if !TTK_QT_VERSION_CHECK(5,0,0)
    TTK::Codec::setLocalCodec();
#endif

#ifdef Q_OS_UNIX
    QFont font;
    font.setPixelSize(13);
    qApp->setFont(font);
#endif
}

QString OCRRunTimeManager::translator() const
{
    return TTK::languageCore(0);
}
