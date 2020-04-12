#ifndef OCRRUNGLOBALDEFINE_H
#define OCRRUNGLOBALDEFINE_H

/* =================================================
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2020 Greedysky Studio

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
#include "ttkprivate.h"

//////////////////////////////////////
///exoprt
///
///
#define OCR_EXPORT

#ifdef OCR_EXPORT
#  define OCR_RUN_EXPORT Q_DECL_EXPORT
#else
#  define OCR_RUN_EXPORT Q_DECL_IMPORT
#endif

#endif // OCRRUNGLOBALDEFINE_H
