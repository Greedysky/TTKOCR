#ifndef ORCFUNCTIONLISTUIOBJECT_H
#define ORCFUNCTIONLISTUIOBJECT_H

/***************************************************************************
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2025 Greedysky Studio

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

#include <QObject>

/*! @brief The namespace of the function list style.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    namespace UI
    {
        static constexpr const char *FuncClose = " \
            QToolButton{ border:none; \
            background-image:url(:/image/btn_close_normal); } \
            QToolButton:hover{ background-image:url(:/image/btn_close_hover); }";

        static constexpr const char *FuncMin= " \
            QToolButton{ border:none; \
            background-image:url(:/image/btn_min_normal); } \
            QToolButton:hover{ background-image:url(:/image/btn_min_hover); }";

    }
}

#endif // ORCFUNCTIONLISTUIOBJECT_H
