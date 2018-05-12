#include "ocrcoreutils.h"
#include "ocrversion.h"

#include <QDirIterator>

QString OCRUtils::Core::fileSuffix(const QString &name)
{
    return fileSuffix(name, ".");
}

QString OCRUtils::Core::fileSuffix(const QString &name, const QString &prefix)
{
    return name.right(name.length() - name.lastIndexOf(prefix) - 1);
}

quint64 OCRUtils::Core::dirSize(const QString &dirName)
{
    quint64 size = 0;
    if(QFileInfo(dirName).isDir())
    {
        QDir dir(dirName);
        QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs |  QDir::Hidden |
                                               QDir::NoSymLinks | QDir::NoDotAndDotDot);
        foreach(const QFileInfo &fileInfo, list)
        {
            if(fileInfo.isDir())
            {
                size += dirSize(fileInfo.absoluteFilePath());
            }
            else
            {
                size += fileInfo.size();
            }
        }
    }
    return size;
}

void OCRUtils::Core::checkCacheSize(quint64 cacheSize, bool disabled, const QString &path)
{
    if(disabled)
    {
        quint64 size = dirSize( path );
        if(size > cacheSize)
        {
            QFileInfoList fileList = QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
            foreach(const QFileInfo &fileInfo, fileList)
            {
                size -= fileInfo.size();
                QFile::remove(fileInfo.absoluteFilePath());
                if(size <= cacheSize)
                {
                    break;
                }
            }
        }
    }
}

QFileInfoList OCRUtils::Core::getFileListByDir(const QString &dpath, bool recursively)
{
    return getFileListByDir(dpath, QStringList(), recursively);
}

QFileInfoList OCRUtils::Core::getFileListByDir(const QString &dpath, const QStringList &filter, bool recursively)
{
    QDir dir(dpath);
    if(!dir.exists())
    {
        return QFileInfoList();
    }

    QFileInfoList fileList = dir.entryInfoList(filter, QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    if(recursively)
    {
        QFileInfoList folderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        foreach(const QFileInfo &fileInfo, folderList)
        {
            fileList.append( getFileListByDir(fileInfo.absoluteFilePath(), filter, recursively) );
        }
    }

    return fileList;
}

bool OCRUtils::Core::removeRecursively(const QString &dir)
{
    QDir dr(dir);
    if(!dr.exists())
    {
        return true;
    }

    bool success = true;
    const QString dirPath = dr.path();
    // not empty -- we must empty it first
    QDirIterator di(dirPath, QDir::AllEntries | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot);
    while(di.hasNext())
    {
        di.next();
        const QFileInfo &fi = di.fileInfo();
        const QString &filePath = di.filePath();
        bool ok;
        if(fi.isDir() && !fi.isSymLink())
        {
            ok = OCRUtils::Core::removeRecursively(filePath); // recursive
        }
        else
        {
            ok = QFile::remove(filePath);
            if(!ok)
            {
                // Read-only files prevent directory deletion on Windows, retry with Write permission.
                const QFile::Permissions permissions = QFile::permissions(filePath);
                if(!(permissions & QFile::WriteUser))
                {
                    ok = QFile::setPermissions(filePath, permissions | QFile::WriteUser)
                      && QFile::remove(filePath);
                }
            }
        }

        if(!ok)
        {
            success = false;
        }
    }

    if(success)
    {
        success = dr.rmdir(dr.absolutePath());
    }

    return success;
}

QString OCRUtils::Core::getLanguageName(int index)
{
    QString lan(LANGUAGE_DIR_FULL);
    switch(index)
    {
        case 0 : return lan.append("cn.ln");
        case 1 : return lan.append("cn_c.ln");
        case 2 : return lan.append("en.ln");
        default: return QString();
    }
}

bool OCRUtils::Core::appVersionCheck(const QStringList &ol, const QStringList &dl, int depth)
{
    if(depth >= ol.count())
    {
        return false;
    }

    if(dl[depth].toInt() >= ol[depth].toInt())
    {
        if(dl[depth].toInt() == ol[depth].toInt())
        {
            return appVersionCheck(ol, dl, depth + 1);
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool OCRUtils::Core::appVersionCheck(const QString &o, const QString &d)
{
    QStringList ol = o.split(".");
    QStringList dl = d.split(".");

    if(ol.isEmpty() || dl.isEmpty() || ol.count() != dl.count())
    {
        return false;
    }

    return appVersionCheck(ol, dl, 0);
}
