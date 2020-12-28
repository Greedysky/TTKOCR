#ifndef OCRGLOBAL_H
#define OCRGLOBAL_H

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

#include "ttkglobal.h"

///
#ifndef OCR_NAMESPACE
#define OCR_NAMESPACE OCR
#endif //OCR_NAMESPACE

#if !TTK_QT_VERSION_CHECK(4,5,0)
#define OCR_NO_NAMESPACE_SUPPORT
#endif

#ifndef OCR_NO_NAMESPACE_SUPPORT
#define OCR_BEGIN_NAMESPACE namespace OCR_NAMESPACE {
#define OCR_END_NAMESPACE }
#define OCR_USE_NAMESPACE using namespace ::OCR_NAMESPACE;
#else
#define OCR_BEGIN_NAMESPACE
#define OCR_END_NAMESPACE
#define OCR_USE_NAMESPACE
#endif //OCR_NAMESPACE_SUPPORT

#endif // OCRGLOBAL_H
