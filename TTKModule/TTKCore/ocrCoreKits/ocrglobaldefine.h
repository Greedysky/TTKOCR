#ifndef OCRGLOBALDEFINE_H
#define OCRGLOBALDEFINE_H

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

#include <QtCore/qglobal.h>

//////////////////////////////////////
#ifdef OCR_LIBRARY
#  define OCR_NETWORK
#  define OCR_CORE
#  define OCR_WIDGET
#  define OCR_GUI
#  define OCR_UTILS
#endif

//////////////////////////////////////
///exoprt
///
///
#define OCR_EXPORT

#ifdef OCR_NETWORK
#  ifdef OCR_EXPORT
#    define OCR_NETWORK_EXPORT Q_DECL_EXPORT
#  else
#    define OCR_NETWORK_IMPORT Q_DECL_IMPORT
#  endif
#endif

#ifdef OCR_CORE
#  ifdef OCR_EXPORT
#    define OCR_CORE_EXPORT Q_DECL_EXPORT
#  else
#    define OCR_CORE_IMPORT Q_DECL_IMPORT
#  endif
#endif

#ifdef OCR_WIDGET
#  ifdef OCR_EXPORT
#    define OCR_WIDGET_EXPORT Q_DECL_EXPORT
#  else
#    define OCR_WIDGET_IMPORT Q_DECL_IMPORT
#  endif
#endif

#ifdef OCR_GUI
#  ifdef OCR_EXPORT
#    define OCR_GUI_EXPORT Q_DECL_EXPORT
#  else
#    define OCR_GUI_IMPORT Q_DECL_IMPORT
#  endif
#endif

#ifdef OCR_UTILS
#  ifdef OCR_EXPORT
#    define OCR_UTILS_EXPORT Q_DECL_EXPORT
#  else
#    define OCR_UTILS_IMPORT Q_DECL_IMPORT
#  endif
#endif

//////////////////////////////////////
///load logger
#include "ocrlogger.h"

#endif // OCRGLOBALDEFINE_H
