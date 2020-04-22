#ifndef OCRRUNTIMEMANAGER_H
#define OCRRUNTIMEMANAGER_H

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

#include "ocrglobaldefine.h"

/*! @brief The class of the app run time needed.
 * @author Greedysky <greedysky@163.com>
 */
class OCR_CORE_EXPORT OCRRunTimeManager
{
    TTK_DECLARE_MODULE(OCRRunTimeManager)
public:
    /*!
     * Object contsructor.
     */
    OCRRunTimeManager();

    /*!
     * Run.
     */
    void run() const;

    /*!
     * Get translator path.
     */
    QString translator() const;

};

#endif // OCRRUNTIMEMANAGER_H
