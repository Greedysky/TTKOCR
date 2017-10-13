#ifndef OCRLOCKEDFILE_H
#define OCRLOCKEDFILE_H

#include <QFile>
#ifdef Q_OS_WIN
#include <QVector>
#endif
#include "ocrrunglobaldefine.h"

namespace OCRLockedPrivate {
  /*! @brief The class of the ocr local file.
   * @author Greedysky <greedysky@163.com>
   */
    class OCR_RUN_EXPORT OCRLockedFile : public QFile
    {
    public:
        enum LockMode
        {
            NoLock = 0,
            ReadLock,
            WriteLock
        };

        OCRLockedFile();
       /*!
         * Object contsructor.
        */
        explicit OCRLockedFile(const QString &name);
        /*!
         * Object contsructor.
        */
        ~OCRLockedFile();

        bool open(OpenMode mode);
        /*!
         * Open current locked file.
        */
        
        bool lock(LockMode mode, bool block = true);
        /*!
         * Lock current file.
        */
        bool unlock();
        /*!
         * Unlock current file.
        */
        bool isLocked() const;
        /*!
         * Get current lock status.
        */
        LockMode lockMode() const;
        /*!
         * Get current lock file mode.
        */
        
    private:
    #ifdef Q_OS_WIN
        Qt::HANDLE wmutex;
        Qt::HANDLE rmutex;
        QVector<Qt::HANDLE> rmutexes;
        QString mutexname;

        Qt::HANDLE getMutexHandle(int idx, bool doCreate);
        bool waitMutex(Qt::HANDLE mutex, bool doBlock);

    #endif
        LockMode m_lock_mode;
    };
}
#endif //OCRLOCKEDFILE_H
