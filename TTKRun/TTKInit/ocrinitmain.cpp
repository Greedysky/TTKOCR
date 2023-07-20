#include <QCoreApplication>
#include "ocrconfigobject.h"

#ifdef _MSC_VER
#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCoreApplication::setOrganizationName(APP_NAME);
    QCoreApplication::setOrganizationDomain(APP_COME_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

    OCRConfigObject object;
    object.initialize();
    TTK_INFO_STREAM("Parameter Init success");
    return 0;
}
