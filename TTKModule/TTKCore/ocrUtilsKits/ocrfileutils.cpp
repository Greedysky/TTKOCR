#include "ocrfileutils.h"

#include <QDirIterator>
#include <QFileDialog>

bool OCRUtils::File::removeRecursively(const QString &dir, bool self)
{
    QDir dr(dir);
    if(!dr.exists())
    {
        return true;
    }

    bool success = true;
    const QString &dirPath = dr.path();
    // not empty -- we must empty it first
    QDirIterator di(dirPath, QDir::AllEntries | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot);
    while(di.hasNext())
    {
        di.next();
        const QFileInfo &fin = di.fileInfo();
        const QString &filePath = di.filePath();

        bool ok = false;
        if(fin.isDir() && !fin.isSymLink())
        {
            ok = OCRUtils::File::removeRecursively(filePath, self); // recursive
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
                    ok = QFile::setPermissions(filePath, permissions | QFile::WriteUser) && QFile::remove(filePath);
                }
            }
        }

        if(!ok)
        {
            success = false;
        }
    }

    if(success && self)
    {
        success = dr.rmdir(dr.absolutePath());
    }
    return success;
}

QStringList OCRUtils::File::getOpenFileNames(QWidget *parent, const QString &filter)
{
    return QFileDialog::getOpenFileNames(parent, QObject::tr("choose a filename to open under"), QDir::currentPath(), filter);
}
