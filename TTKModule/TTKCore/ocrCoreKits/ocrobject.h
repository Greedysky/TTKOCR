#ifndef OCROBJECT_H
#define OCROBJECT_H

/* =================================================
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2017 Greedysky Studio

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
///////////////////////////////////////

#define APPDATA_DIR             "AppData/"
#define DOWNLOADS_DIR           "Downloads/"

#define LANGUAGE_DIR            "MLanguage/"
#define TEMPORARY_DIR           "temporary"

///////////////////////////////////////
#define APPDATA_DIR_FULL        OCRObject::getAppDir() + QString("../") + APPDATA_DIR
#define DOWNLOADS_DIR_FULL      OCRObject::getAppDir() + QString("../") + DOWNLOADS_DIR

#define TEMPORARY_DIR_FULL      DOWNLOADS_DIR_FULL + TEMPORARY_DIR

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
