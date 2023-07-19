#ifndef OCRCONFIGDEFINE_H
#define OCRCONFIGDEFINE_H

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
#include "ttkmoduleexport.h"

//
#define TTK_DOWNLOAD_DIR_FULL   DOWNLOAD_DIR_FULL
#define TTK_LANGUAGE_DIR_FULL   LANGUAGE_DIR_FULL

#ifdef Q_OS_WIN
#  define TTK_SERVICE_FULL      TTK::applicationPath() + SERVICE_EXE_NAME
#else
#  define TTK_ROUTINE_FULL      TTK::applicationPath() + TTK_PDIR + "TTKRoutine.sh"
#  define TTK_OCR_FULL          TTK::applicationPath() + TTK_PDIR + APP_SHL_NAME
#  define TTK_SERVICE_FULL      TTK::applicationPath() + SERVICE_SHL_NAME
#  define TTK_ROUTINECOPY_FULL  TTK::applicationPath() + "TTKRoutineCopy.sh"
#endif

#endif // OCRCONFIGDEFINE_H
