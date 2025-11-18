#include "ocrconfigmodule.h"

#include <QProcess>

OCRConfigModule::OCRConfigModule(QObject *parent)
    : QObject(parent)
{

}

void OCRConfigModule::execute() const
{
    checkDirectoryExist();
    checkFileNeededExist();
}

void OCRConfigModule::initialize() const
{
    execute();
}

void OCRConfigModule::directoryExist(const QString &name) const
{
    QDir dir;
    if(!dir.exists(name))
    {
        dir.mkpath(name);
    }
}

void OCRConfigModule::checkDirectoryExist() const
{
    directoryExist(TTK_LANGUAGE_DIR_FULL);
}

void OCRConfigModule::checkFileNeededExist() const
{
#ifdef Q_OS_UNIX
    if(!QFile::exists(MAIN_DIR_FULL + "ttk_runtime"))
    {
        copyLinuxShellFile(":/data/TTKRoutine.sh", TTK_ROUTINE_FULL);
        copyLinuxShellFile(":/data/TTKOCR.sh", TTK_APP_MAIN_FULL);
        copyLinuxShellFile(":/data/TTKRoutineCopy.sh", TTK_ROUTINECOPY_FULL);
        copyLinuxShellFile(":/data/TTKInit.sh", TTK_INIT_FULL);
        copyLinuxShellFile(":/data/TTKService.sh", TTK_SERVICE_FULL);
    }
#endif
}

void OCRConfigModule::copyFileOverwrite(const QString &origin, const QString &des) const
{
    if(QFile::exists(des))
    {
        QFile::remove(des);
    }

    QFile::copy(origin, des);
    QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
}

void OCRConfigModule::copyFile(const QString &origin, const QString &des) const
{
    if(!QFile::exists(des))
    {
        QFile::copy(origin, des);
        QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
    }
}

#ifdef Q_OS_UNIX
void OCRConfigModule::copyLinuxShellFile(const QString &name, const QString &path) const
{
    copyFileOverwrite(name, path);
    QProcess::execute("chmod", {"+x", path});
}
#endif
