#include "ttkrunapplication.h"
#include "ttkrunobject.h"
#include "ocrobject.h"

int main(int argc, char *argv[])
{
    TTKRunApplication app(argc, argv);

    QCoreApplication::setOrganizationName(APPNAME);
    QCoreApplication::setOrganizationDomain(APPCOME);
    QCoreApplication::setApplicationName(APPNAME);

    if(app.isRunning())
    {
        TTK_LOGGER_INFO("One app has already run!");
        return -1;
    }

    OCRRunObject object;
    object.checkValid();
    object.run(argc, argv);

    return app.exec();
}
