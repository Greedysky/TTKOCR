#include "ttkapplication.h"
#include "ocrapplication.h"
#include "ocrruntimemanager.h"
#include "ocrconfigmodule.h"
#include "ocrfileutils.h"
#include "ttkinitialization.h"

#include <QTranslator>

static void cleanupCache()
{
    TTK::File::removeRecursively(DIR_PREFIX_FULL);
    TTK::File::removeRecursively(DOWNLOAD_DIR_FULL);
    TTK_INFO_STREAM("Application cache cleanup");
}


int main(int argc, char *argv[])
{
    TTK::loadApplicationScaleFactor();

    TTKApplication app(argc, argv);
    TTKInitialization ttk(cleanupCache);

    if(app.isRunning())
    {
        TTK_INFO_STREAM("One app has already run");
        return EXIT_FAILURE;
    }

    ttk.generateFont();
    ttk.codecForLocale();
    ttk.execute();

    OCRConfigModule config;
    config.valid();

    OCRRunTimeManager manager;
    manager.execute();

    QTranslator translator;
    if(!translator.load(manager.translator()))
    {
        TTK_ERROR_STREAM("Load translation error");
    }
    app.installTranslator(&translator);

    OCRApplication w;
    w.show();
    return app.exec();
}
