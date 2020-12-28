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
#include "ocrglobal.h"

#define DOT                     "."

///////////////////////////////////////
#define APPNAME                 "TTKOCR"
#define APPDOT                  "TTKOCR."
#define APPCOME                 "TTKOCR.com"
#define APPEXE                  "TTKOCR.exe"
///////////////////////////////////////

#define APPDATA_DIR             "AppData/"
#define DOWNLOADS_DIR           "Downloads/"

#define SHOTS_DIR               "Shots/"
#define LANGUAGE_DIR            "MLanguage/"
#define TEMPORARY_DIR           "temporary"

#define TTS_FILE_PREFIX         "ttks"
#define SKN_FILE_PREFIX         "skn"
#define JPG_FILE_PREFIX         "jpg"
#define BMP_FILE_PREFIX         "bmp"
#define PNG_FILE_PREFIX         "png"
#define CFG_FILE_PREFIX         "ttk"
#define LST_FILE_PREFIX         "lis"
#define EXE_FILE_PREFIX         "exe"
#define XML_FILE_PREFIX         "xml"

#define TTS_FILE                TTK_STRCAT(DOT, TTS_FILE_PREFIX)
#define SKN_FILE                TTK_STRCAT(DOT, SKN_FILE_PREFIX)
#define JPG_FILE                TTK_STRCAT(DOT, JPG_FILE_PREFIX)
#define BMP_FILE                TTK_STRCAT(DOT, BMP_FILE_PREFIX)
#define PNG_FILE                TTK_STRCAT(DOT, PNG_FILE_PREFIX)
#define CFG_FILE                TTK_STRCAT(DOT, CFG_FILE_PREFIX)
#define LST_FILE                TTK_STRCAT(DOT, LST_FILE_PREFIX)
#define EXE_FILE                TTK_STRCAT(DOT, EXE_FILE_PREFIX)
#define XML_FILE                TTK_STRCAT(DOT, XML_FILE_PREFIX)

///////////////////////////////////////
#define APPDATA_DIR_FULL        OCRObject::getAppDir() + QString("../") + APPDATA_DIR
#define DOWNLOADS_DIR_FULL      OCRObject::getAppDir() + QString("../") + DOWNLOADS_DIR

#define TEMPORARY_DIR_FULL      DOWNLOADS_DIR_FULL + TEMPORARY_DIR
#define SHOTS_DIR_FULL          DOWNLOADS_DIR_FULL + SHOTS_DIR

#define LANGUAGE_DIR_FULL       OCRObject::getAppDir() + LANGUAGE_DIR

///////////////////////////////////////
#define WINDOW_WIDTH_MIN        850
#define WINDOW_HEIGHT_MIN       550
///////////////////////////////////////
#define DEFAULT_INDEX_LEVEL0    -1
#define DEFAULT_INDEX_LEVEL1    -999
#define DEFAULT_INDEX_LEVEL2    -888
#define DEFAULT_INDEX_LEVEL3    -777
#define DEFAULT_INDEX_LEVEL4    -666
#define DEFAULT_INDEX_LEVEL5    -555
///////////////////////////////////////
#define STRING_SPLITER          "*|||*"
///////////////////////////////////////

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
