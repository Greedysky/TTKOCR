#ifndef OCROBJECT_H
#define OCROBJECT_H

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

#include <QDir>
#include <QCoreApplication>
#include "ttkglobal.h"

#define DOT                     "."
//
#define DOWNLOAD_DIR            "Downloads/"
#define LANGUAGE_DIR            "MLanguage/"


#define DIR_PREFIX              "dir"

#define JPG_FILE_PREFIX         "jpg"
#define EXE_FILE_PREFIX         "exe"
#define COM_FILE_PREFIX         "com"

#define JPG_FILE                TTK_STRCAT(DOT, JPG_FILE_PREFIX)
#define EXE_FILE                TTK_STRCAT(DOT, EXE_FILE_PREFIX)
#define COM_FILE                TTK_STRCAT(DOT, COM_FILE_PREFIX)


#define APP_NAME                "TTKOCR"
#define APP_DOT_NAME            TTK_STRCAT(APP_NAME, DOT)
#define APP_COME_NAME           TTK_STRCAT(APP_NAME, COM_FILE)
#define APP_EXE_NAME            TTK_STRCAT(APP_NAME, EXE_FILE)


#define DOWNLOAD_DIR_FULL       OCRObject::getAppDir() + QString("../") + DOWNLOAD_DIR
#define LANGUAGE_DIR_FULL       OCRObject::getAppDir() + LANGUAGE_DIR


#define WINDOW_WIDTH_MIN        850
#define WINDOW_HEIGHT_MIN       550
//
#define DEFAULT_INDEX_LEVEL0    -1
#define DEFAULT_INDEX_LEVEL1    -999
#define DEFAULT_INDEX_LEVEL2    -888
#define DEFAULT_INDEX_LEVEL3    -777
#define DEFAULT_INDEX_LEVEL4    -666
#define DEFAULT_INDEX_LEVEL5    -555
//
#define STRING_NULL             "-"
#define URL_NULL                "null"


/*! @brief The namespace of the application object.
 * @author Greedysky <greedysky@163.com>
 */
namespace OCRObject
{
    /*!
     * Get application dir.
     */
    static QString getAppDir()
    {
        return QCoreApplication::applicationDirPath() + "/";
    }
}

#endif // OCROBJECT_H
