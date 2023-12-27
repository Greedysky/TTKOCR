#ifndef OCROBJECT_H
#define OCROBJECT_H

/***************************************************************************
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2024 Greedysky Studio

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

#include "ttkqtglobal.h"
#include "ttkqtobject.h"

//
#define DIR_PREFIX              "dir"

#define JPG_FILE_SUFFIX         "jpg"

#define JPG_FILE                TTK_STR_CAT(TTK_DOT, JPG_FILE_SUFFIX)


#define DOWNLOAD_DIR            TTK_STR_CAT("Downloads", TTK_SEPARATOR)
#define LANGUAGE_DIR            TTK_STR_CAT("GLanguage", TTK_SEPARATOR)

#define MAIN_DIR_FULL           TTK::applicationPath() + TTK_PDIR
//
#define DOWNLOAD_DIR_FULL       MAIN_DIR_FULL + DOWNLOAD_DIR
#define LANGUAGE_DIR_FULL       TTK::applicationPath() + LANGUAGE_DIR


#define WINDOW_WIDTH_MIN        850
#define WINDOW_HEIGHT_MIN       550

#endif // OCROBJECT_H
