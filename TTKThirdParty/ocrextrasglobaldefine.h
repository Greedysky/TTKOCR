#ifndef OCREXTRASGLOBALDEFINE_H
#define OCREXTRASGLOBALDEFINE_H

/* =================================================
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2018 Greedysky Studio

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

#include "ocrglobal.h"

//////////////////////////////////////
///exoprt
///
///
#define OCR_EXPORT

#ifdef OCR_EXPORT
#  define OCR_EXTRAS_EXPORT Q_DECL_EXPORT
#else
#  define OCR_EXTRAS_IMPORT Q_DECL_IMPORT
#endif

#endif // OCREXTRASGLOBALDEFINE_H
