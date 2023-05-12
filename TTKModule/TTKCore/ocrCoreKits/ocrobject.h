#ifndef OCROBJECT_H
#define OCROBJECT_H

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

#include <QDir>
#include <QCoreApplication>
#include "ttkglobal.h"

//
#define DIR_PREFIX              "dir"

#define JPG_FILE_SUFFIX         "jpg"
#define EXE_FILE_SUFFIX         "exe"
#define COM_FILE_SUFFIX         "com"


#define JPG_FILE                TTK_STRCAT(TTK_DOT, JPG_FILE_SUFFIX)
#define EXE_FILE                TTK_STRCAT(TTK_DOT, EXE_FILE_SUFFIX)
#define COM_FILE                TTK_STRCAT(TTK_DOT, COM_FILE_SUFFIX)


#define SERVICE_NAME            "TTKService"
#define APP_NAME                "TTKOCR"
#define APP_DOT_NAME            TTK_STRCAT(APP_NAME, TTK_DOT)
#define APP_COME_NAME           TTK_STRCAT(APP_NAME, COM_FILE)
#ifdef Q_OS_WIN
#  define APP_EXE_NAME          TTK_STRCAT(APP_NAME, EXE_FILE)
#  define SERVICE_EXE_NAME      TTK_STRCAT(SERVICE_NAME, EXE_FILE)
#else
#  define APP_EXE_NAME          APP_NAME
#  define SERVICE_EXE_NAME      SERVICE_NAME
#endif


#define DOWNLOAD_DIR            TTK_STRCAT("Downloads", TTK_SEPARATOR)
#define LANGUAGE_DIR            TTK_STRCAT("GLanguage", TTK_SEPARATOR)

#define DOWNLOAD_DIR_FULL       TTK::applicationPath() + TTK_PDIR + DOWNLOAD_DIR
#define LANGUAGE_DIR_FULL       TTK::applicationPath() + LANGUAGE_DIR


#define WINDOW_WIDTH_MIN        850
#define WINDOW_HEIGHT_MIN       550


/*! @brief The namespace of the application object.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    /*!
     * Get application work dir.
     */
    static QString applicationPath()
    {
        return QCoreApplication::applicationDirPath() + TTK_SEPARATOR;
    }
}

#endif // OCROBJECT_H
