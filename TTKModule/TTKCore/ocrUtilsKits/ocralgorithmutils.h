#ifndef OCRALGORITHMUTILS_H
#define OCRALGORITHMUTILS_H

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

#include "ocrglobaldefine.h"

#define ALG_DOWNLOAD_KEY    "132;sdf15233"
#define ALG_URL_KEY         "65sdf33sdf12;sdf"
#define ALG_PLUS_KEY        "9d9;;dk,.132"
#define ALG_LOW_KEY         "2318"

/*! @brief The class of the utils algorithm object namespace.
 * @author Greedysky <greedysky@163.com>
 */
namespace OCRUtils
{
    namespace Algorithm
    {
        /*!
         * Get md5 algorithm.
         */
        OCR_UTILS_EXPORT QByteArray md5(const QByteArray &data);
        /*!
         * Get sha1 algorithm.
         */
        OCR_UTILS_EXPORT QByteArray sha1(const QByteArray &data);

        /*!
         * Get mdII(greedysky) algorithm.
         */
        OCR_UTILS_EXPORT QString mdII(const QString &data, bool encode);
        /*!
         * Get mdII(greedysky) algorithm.
         */
        OCR_UTILS_EXPORT QString mdII(const QString &data, const QString &key, bool encode);

    }
}

#endif // OCRALGORITHMUTILS_H
