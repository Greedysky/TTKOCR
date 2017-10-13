#include "ocrlockedfile.h"

OCRLockedFile::OCRLockedFile()
    : QFile()
{
#ifdef Q_OS_WIN
    wmutex = 0;
    rmutex = 0;
#endif
    m_lock_mode = NoLock;
}

OCRLockedFile::OCRLockedFile(const QString &name)
    : QFile(name)
{
#ifdef Q_OS_WIN
    wmutex = 0;
    rmutex = 0;
#endif
    m_lock_mode = NoLock;
}

bool OCRLockedFile::open(OpenMode mode)
{
    if (mode & QIODevice::Truncate) {
        qWarning("OCRLockedFile::open(): Truncate mode not allowed.");
        return false;
    }
    return QFile::open(mode);
}

bool OCRLockedFile::isLocked() const
{
    return m_lock_mode != NoLock;
}

OCRLockedFile::LockMode OCRLockedFile::lockMode() const
{
    return m_lock_mode;
}
