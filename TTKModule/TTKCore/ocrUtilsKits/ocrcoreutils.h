#ifndef OCRCOREUTILS_H
#define OCRCOREUTILS_H

/* =================================================
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2021 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include "ocrobject.h"
#include "ttkglobaldefine.h"

/*! @brief The class of the utils core object namespace.
 * @author Greedysky <greedysky@163.com>
 */
namespace OCRUtils
{
    namespace Core
    {
        /*!
         * Get file suffix path.
         */
        TTK_MODULE_EXPORT QString fileSuffix(const QString &name);
        /*!
         * Get file suffix path.
         */
        TTK_MODULE_EXPORT QString fileSuffix(const QString &name, const QString &prefix);

        /*!
         * Get given dir size.
         */
        TTK_MODULE_EXPORT quint64 dirSize(const QString &dirName);
        /*!
         * Check given dir size is bigger than given size.
         */
        TTK_MODULE_EXPORT void checkCacheSize(quint64 cacheSize, bool disabled, const QString &path);
        /*!
         * Get all files in given dir.
         */
        TTK_MODULE_EXPORT QFileInfoList getFileListByDir(const QString &dpath, bool recursively);
        /*!
         * Get all files in given dir.
         */
        TTK_MODULE_EXPORT QFileInfoList getFileListByDir(const QString &dpath, const QStringList &filter, bool recursively);
        /*!
         * Dir remove recursively.
         */
        TTK_MODULE_EXPORT bool removeRecursively(const QString &dir);

        /*!
         * Get Language Name by given index.
         */
        TTK_MODULE_EXPORT QString getLanguageName(int index);

        /*!
         * App version check.
         */
        TTK_MODULE_EXPORT bool appVersionCheck(const QStringList &ol, const QStringList &dl, int depth);
        /*!
         * App version check.
         */
        TTK_MODULE_EXPORT bool appVersionCheck(const QString &o, const QString &d);

    }
}

#endif // OCRCOREUTILS_H
