#ifndef OCRSTRINGUTILS_H
#define OCRSTRINGUTILS_H

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

#include "ocrglobaldefine.h"

/*! @brief The class of the utils string object namespace.
 * @author Greedysky <greedysky@163.com>
 */
namespace OCRUtils
{
    namespace String
    {
        /*!
         * Remove given key in string, default is space.
         */
        OCR_UTILS_EXPORT QString removeStringBy(const QString &value, const QString &key = " ");
        /*!
         * Get split string value.
         */
        OCR_UTILS_EXPORT QStringList splitString(const QString &value, const QString &key = "-");

        /*!
         * Illegal characters check.
         */
        OCR_UTILS_EXPORT QStringList illegalCharacters();
        /*!
         * Illegal characters check.
         */
        OCR_UTILS_EXPORT bool illegalCharactersCheck(const QString &value);
        /*!
         * Illegal characters replaced.
         */
        OCR_UTILS_EXPORT QString illegalCharactersReplaced(const QString &value);

        /*!
         * Transform colors string to color list.
         */
        OCR_UTILS_EXPORT QList<QColor> readColorConfig(const QString &value);
        /*!
         * Transform color to color string.
         */
        OCR_UTILS_EXPORT QString writeColorConfig(const QColor &color);
        /*!
         * Transform color list to colors string.
         */
        OCR_UTILS_EXPORT QString writeColorConfig(const QList<QColor> &colors);

    }
}

#endif // OCRSTRINGUTILS_H
