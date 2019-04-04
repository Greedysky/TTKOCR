#ifndef OCRINITOBJECT_H
#define OCRINITOBJECT_H

/* =================================================
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2019 Greedysky Studio

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

#include <QDebug>
#include "ocrobject.h"
#include "ocrversion.h"
#include "ocrrunglobaldefine.h"

#define S_APPDATA_DIR_FULL        OCRObject::getAppDir() + APPDATA_DIR
#define S_DOWNLOADS_DIR_FULL      OCRObject::getAppDir() + DOWNLOADS_DIR

#define S_TEMPORARY_DIR_FULL      S_DOWNLOADS_DIR_FULL + TEMPORARY_DIR

#define S_LANGUAGE_DIR_FULL       OCRObject::getAppDir() + OCR_VERSION_STR + "/" + LANGUAGE_DIR

#ifdef Q_OS_WIN
#define S_TTKSERVICE_FULL         OCRObject::getAppDir() + OCR_VERSION_STR + "/TTKService.exe"
#else
#define S_TTKDD_FULL              OCRObject::getAppDir() + OCR_VERSION_STR + "/TTKLDD.sh"
#define S_TTKSERVICE_FULL         OCRObject::getAppDir() + OCR_VERSION_STR + "/TTKService.sh"
#define S_TTKOCR_FULL             OCRObject::getAppDir() + "TTKOCR.sh"
#define S_TTKROUTINE_FULL         OCRObject::getAppDir() + "TTKRoutine.sh"
#define S_TTKROUTINECOPY_FULL     OCRObject::getAppDir() + OCR_VERSION_STR + "/TTKRoutineCopy.sh"
#endif


/*! @brief The class of the ocr init object.
 * @author Greedysky <greedysky@163.com>
 */
class OCR_RUN_EXPORT OCRInitObject : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit OCRInitObject(QObject *parent = 0);

    /*!
     * Check current setting file's validation.
     */
    void checkValid();

    /*!
     * Init all parameter.
     */
    void init();
    /*!
     * Check current dir is exist, no, just create it.
     */
    void dirIsExist(const QString &name);
    /*!
     * Check the related dir is exist.
     */
    void checkTheDirectoryExist();
    /*!
     * Check the related file is exist.
     */
    void checkTheFileNeededExist();
    /*!
     * Copy file by overwrite.
     */
    void copyFileOverwrite(const QString &origin, const QString &des);
    /*!
     * Copy file.
     */
    void copyFile(const QString &origin, const QString &des);
    /*!
     * Copy linux shell file.
     */
    void copyLinuxShellFile(const QString &name, const QString &path);
};

#endif // OCRINITOBJECT_H
