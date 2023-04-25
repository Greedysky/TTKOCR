#ifndef OCRUIOBJECT_H
#define OCRUIOBJECT_H

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

#include "ttkglobal.h"

/*! @brief The namespace of the application ui object.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    namespace UI
    {
		///PushButton
        static const QString PushButtonStyle01 = " \
            QPushButton{ border:1px solid #AAAAAA; background:#FFFFFF; color:#777777;} \
            QPushButton::hover{ border:1px solid #555555; color:#444444;} \
            QPushButton::disabled{ color:#999999;}";

		///ScrollBar
        static const QString ScrollBarStyle01 = " \
            QScrollBar{ background:#FFFFFF; width:8px; padding-top:0px; padding-bottom:0px;} \
            QScrollBar::handle:vertical{ border-radius:4px; background:#CFCFCF; min-height: 30px;} \
            QScrollBar::handle:vertical::disabled{ background:#DBDBDB;} \
            QScrollBar::handle:vertical:hover{ background:#BBBBBB;} \
            QScrollBar::add-line, QScrollBar::sub-line{ background:none; border:none;} \
            QScrollBar::add-page, QScrollBar::sub-page{ background:none;}";

        static const QString ScrollBarStyle02 = " \
            QScrollBar{ background:#FFFFFF; height:8px; padding-left:0px; padding-right:0px;} \
            QScrollBar::handle:horizontal{ border-radius:4px; background:#CFCFCF; min-width: 30px;} \
            QScrollBar::handle:horizontal::disabled{ background:#DBDBDB;} \
            QScrollBar::handle:horizontal:hover{ background:#BBBBBB;} \
            QScrollBar::add-line, QScrollBar::sub-line{ background:none; border:none;} \
            QScrollBar::add-page, QScrollBar::sub-page{ background:none;}";

        static const QString ScrollBarStyle03 = ScrollBarStyle01 + " \
            QScrollBar{ background:transparent;}";

        static const QString ScrollBarStyle04 = ScrollBarStyle02 + " \
            QScrollBar{ background:transparent;}";

    }
}

#endif // OCRUIOBJECT_H
