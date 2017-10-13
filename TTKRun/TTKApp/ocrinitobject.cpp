#include "ocrinitobject.h"

#include <QProcess>

OCRInitObject::OCRInitObject(QObject *parent)
    : QObject(parent)
{

}

void OCRInitObject::checkValid()
{
    checkTheDirectoryExist();
    checkTheFileNeededExist();
}

void OCRInitObject::init()
{
    checkTheFileNeededExist();
}

void OCRInitObject::dirIsExist(const QString &name)
{
    QDir dir;
    if(!dir.exists(name))
    {
        dir.mkpath(name);
    }
}

void OCRInitObject::checkTheDirectoryExist()
{
    dirIsExist(S_APPDATA_DIR_FULL);
    dirIsExist(S_DOWNLOADS_DIR_FULL);

    dirIsExist(S_LANGUAGE_DIR_FULL);
}

void OCRInitObject::checkTheFileNeededExist()
{
#ifdef Q_OS_UNIX
    if(!QFile::exists(S_TTKDD_FULL))
    {
        QFile::copy(":/data/TTKLDD.sh", S_TTKDD_FULL);
        QFile::setPermissions(S_TTKDD_FULL, QFile::ReadOwner | QFile::WriteOwner);
        QProcess::execute("chmod", QStringList() << "+x" << S_TTKDD_FULL);
    }
    if(!QFile::exists(S_TTKSERVICE_FULL))
    {
        QFile::copy(":/data/TTKService.sh", S_TTKSERVICE_FULL);
        QFile::setPermissions(S_TTKSERVICE_FULL, QFile::ReadOwner | QFile::WriteOwner);
        QProcess::execute("chmod", QStringList() << "+x" << S_TTKSERVICE_FULL);
    }
#endif

}

void OCRInitObject::copyFileOverwrite(const QString &origin, const QString &des)
{
    if(QFile::exists(des))
    {
        QFile::remove(des);
    }
    QFile::copy(origin, des);
    QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
}

void OCRInitObject::copyFile(const QString &origin, const QString &des)
{
    if(!QFile::exists(des))
    {
        QFile::copy(origin, des);
        QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
    }
}
