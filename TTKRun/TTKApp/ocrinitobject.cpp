#include "ocrinitobject.h"

#include <QProcess>

OCRInitObject::OCRInitObject(QObject *parent)
    : QObject(parent)
{

}

void OCRInitObject::valid() const
{
    checkDirectoryExist();
    checkFileNeededExist();
}

void OCRInitObject::init() const
{
    checkFileNeededExist();
}

void OCRInitObject::directoryExist(const QString &name) const
{
    QDir dir;
    if(!dir.exists(name))
    {
        dir.mkpath(name);
    }
}

void OCRInitObject::checkDirectoryExist() const
{
    directoryExist(TTK_DOWNLOAD_DIR_FULL);
    directoryExist(TTK_LANGUAGE_DIR_FULL);
}

void OCRInitObject::checkFileNeededExist() const
{
#ifdef Q_OS_UNIX
    copyLinuxShellFile(":/data/TTKOCR.sh", TTK_OCR_FULL);
    copyLinuxShellFile(":/data/TTKService.sh", TTK_SERVICE_FULL);
    copyLinuxShellFile(":/data/TTKRoutine.sh", TTK_ROUTINE_FULL);
    copyLinuxShellFile(":/data/TTKRoutineCopy.sh", TTK_ROUTINECOPY_FULL);
#endif
}

void OCRInitObject::copyFileOverwrite(const QString &origin, const QString &des) const
{
    if(QFile::exists(des))
    {
        QFile::remove(des);
    }

    QFile::copy(origin, des);
    QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
}

void OCRInitObject::copyFile(const QString &origin, const QString &des) const
{
    if(!QFile::exists(des))
    {
        QFile::copy(origin, des);
        QFile::setPermissions(des, QFile::ReadOwner | QFile::WriteOwner);
    }
}

void OCRInitObject::copyLinuxShellFile(const QString &name, const QString &path) const
{
    copyFileOverwrite(name, path);
    QProcess::execute("chmod", {"+x", path});
}
