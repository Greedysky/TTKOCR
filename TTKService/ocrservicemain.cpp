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
    TTK::initialize(TTK::Attribute::All);

    TTKApplication app(argc, argv);
    TTKInitialization ttk(cleanupCache);

    // parse command line args
    QStringList args;
    for(int i = 0; i < argc; ++i)
    {
        const QString &arg = QString::fromLocal8Bit(argv[i]);
        if(ttk.argumentValid(arg))
        {
            args << arg;
        }
    }

    ttk.execute(args);

    if(app.isRunning())
    {
        TTK_INFO_STREAM("One app has already run");
        return EXIT_FAILURE;
    }

    OCRConfigModule config;
    config.execute();

    OCRRunTimeManager manager;
    manager.execute();

    ttk.generateFont();
    ttk.codecForLocale();

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
