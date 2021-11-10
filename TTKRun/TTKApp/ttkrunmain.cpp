#include "ttkrunapplication.h"
#include "ttkrunobject.h"
#include "ocrobject.h"

int main(int argc, char *argv[])
{
    TTKRunApplication app(argc, argv);

    QCoreApplication::setOrganizationName(APP_NAME);
    QCoreApplication::setOrganizationDomain(APP_COME_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

    if(app.isRunning())
    {
        TTK_LOGGER_INFO("One app has already run!");
        return -1;
    }

    OCRRunObject object;
    object.valid();
    object.run(argc, argv);

    return app.exec();
}
