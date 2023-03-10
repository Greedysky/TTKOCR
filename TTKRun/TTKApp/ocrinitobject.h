#ifndef OCRINITOBJECT_H
#define OCRINITOBJECT_H

/***************************************************************************
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2023 Greedysky Studio

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
 ***************************************************************************/

#include "ocrobject.h"
#include "ttkversion.h"
#include "ttkglobaldefine.h"

#define TTK_DOWNLOAD_DIR_FULL    TTK::applicationPath() + DOWNLOAD_DIR
#define TTK_LANGUAGE_DIR_FULL    TTK::applicationPath() + TTK_VERSION_STR + TTK_SEPARATOR + LANGUAGE_DIR

#ifdef Q_OS_WIN
#  define TTK_SERVICE_FULL       TTK::applicationPath() + TTK_VERSION_STR + TTK_SEPARATOR + "TTKService.exe"
#else
#  define TTK_OCR_FULL           TTK::applicationPath() + "TTKOCR.sh"
#  define TTK_ROUTINE_FULL       TTK::applicationPath() + "TTKRoutine.sh"
#  define TTK_SERVICE_FULL       TTK::applicationPath() + TTK_VERSION_STR + TTK_SEPARATOR + "TTKService.sh"
#  define TTK_ROUTINECOPY_FULL   TTK::applicationPath() + TTK_VERSION_STR + TTK_SEPARATOR + "TTKRoutineCopy.sh"
#endif


/*! @brief The class of the ocr init object.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT OCRInitObject : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit OCRInitObject(QObject *parent = nullptr);

    /*!
     * Check current setting file's validation.
     */
    void valid() const;

    /*!
     * Init all parameter.
     */
    void initialize() const;
    /*!
     * Check current dir is exist, no, just create it.
     */
    void directoryExist(const QString &name) const;
    /*!
     * Check related dir is exist.
     */
    void checkDirectoryExist() const;
    /*!
     * Check related file is exist.
     */
    void checkFileNeededExist() const;
    /*!
     * Copy file by overwrite.
     */
    void copyFileOverwrite(const QString &origin, const QString &des) const;
    /*!
     * Copy file.
     */
    void copyFile(const QString &origin, const QString &des) const;
    /*!
     * Copy linux shell file.
     */
    void copyLinuxShellFile(const QString &name, const QString &path) const;

};

#endif // OCRINITOBJECT_H
