#include "ocrapplication.h"
#include "ocrruntimemanager.h"
#include "ttkdumper.h"

#include <QTimer>
#include <QTranslator>
#include <QApplication>

#define TTK_DEBUG

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if !defined TTK_DEBUG && !defined Q_OS_UNIX
    if(argc <= 1 || QString(argv[1]) != APPNAME)
    {
        return -1;
    }
#endif
    ///////////////////////////////////////////////////////
    QCoreApplication::setOrganizationName(APPNAME);
    QCoreApplication::setOrganizationDomain(APPCOME);
    QCoreApplication::setApplicationName(APPNAME);

    TTKDumper dumper;
    dumper.run();

    OCRRunTimeManager manager;
    manager.run();

    QTranslator translator;
    translator.load(manager.translator());
    a.installTranslator(&translator);

    OCRApplication w;
    w.show();

    return a.exec();
}
