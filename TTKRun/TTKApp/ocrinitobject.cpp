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
    copyLinuxShellFile(":/data/TTKOCR.sh", S_TTKOCR_FULL);
    copyLinuxShellFile(":/data/TTKService.sh", S_TTKSERVICE_FULL);
    copyLinuxShellFile(":/data/TTKRoutine.sh", S_TTKROUTINE_FULL);
    copyLinuxShellFile(":/data/TTKRoutineCopy.sh", S_TTKROUTINECOPY_FULL);
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

void OCRInitObject::copyLinuxShellFile(const QString &name, const QString &path)
{
    copyFileOverwrite(name, path);
    QProcess::execute("chmod", QStringList() << "+x" << path);
}
