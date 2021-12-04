#ifndef OCRAPPLICATIONOBJECT_H
#define OCRAPPLICATIONOBJECT_H

/***************************************************************************
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2022 Greedysky Studio

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
#include "ttkglobaldefine.h"

class QPropertyAnimation;

/*! @brief The class of the app object widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT OCRApplicationObject : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(OCRApplicationObject)
public:
    /*!
     * Object contsructor.
     */
    explicit OCRApplicationObject(QObject *parent = nullptr);
    ~OCRApplicationObject();

    /*!
     * Get class object instance.
     */
    static OCRApplicationObject *instance();

public Q_SLOTS:
    /*!
     * Window close animation.
     */
    void windowCloseAnimation();
    /*!
     * Show about us widget.
     */
    void appAboutUs();

private:
    /*!
     * Something temp clean up.
     */
    void cleanUp();

    QPropertyAnimation *m_animation;

    static OCRApplicationObject *m_instance;
};

#endif // OCRAPPLICATIONOBJECT_H
