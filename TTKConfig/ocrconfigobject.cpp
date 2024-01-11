#include "ocrconfigobject.h"

#include <QProcess>

OCRConfigObject::OCRConfigObject(QObject *parent)
    : QObject(parent)
{

}

void OCRConfigObject::valid() const
{
    checkDirectoryExist();
    checkFileNeededExist();
}

void OCRConfigObject::initialize() const
{
    valid();
}

void OCRConfigObject::reset() const
{

}

void OCRConfigObject::directoryExist(const QString &name) const
{
    QDir dir;
    if(!dir.exists(name))
    {
        dir.mkpath(name);
    }
}

void OCRConfigObject::checkDirectoryExist() const
{
    directoryExist(TTK_DOWNLOAD_DIR_FULL);
    directoryExist(TTK_LANGUAGE_DIR_FULL);
}

void OCRConfigObject::checkFileNeededExist() const
{
#ifdef Q_OS_UNIX
    if(!QFile::exists(MAIN_DIR_FULL + ".ttk_runtime"))
    {
        copyLinuxShellFile(":/data/TTKRoutine.sh", TTK_ROUTINE_FULL);
        copyLinuxShellFile(":/data/TTKOCR.sh", TTK_APP_MAIN_FULL);
        copyLinuxShellFile(":/data/TTKRoutineCopy.sh", TTK_ROUTINECOPY_FULL);
        copyLinuxShellFile(":/data/TTKInit.sh", TTK_INIT_FULL);
        copyLinuxShellFile(":/data/TTKService.sh", TTK_SERVICE_FULL);
    }
#endif
}

void OCRConfigObject::copyFileOverwrite(const QString &origin, const QString &des) const
{
    if(QFile::exists(des))
    {
        QFile::remove(des);
    }

    QFile::copy(origin, des);
    QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
}

void OCRConfigObject::copyFile(const QString &origin, const QString &des) const
{
    if(!QFile::exists(des))
    {
        QFile::copy(origin, des);
        QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
    }
}

#ifdef Q_OS_UNIX
void OCRConfigObject::copyLinuxShellFile(const QString &name, const QString &path) const
{
    copyFileOverwrite(name, path);
    QProcess::execute("chmod", {"+x", path});
}
#endif
