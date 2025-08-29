#ifndef OCRAPPLICATIONMODULE_H
#define OCRAPPLICATIONMODULE_H

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

#include "ttkmoduleexport.h"

/*! @brief The class of the app object module.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT OCRApplicationModule : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit OCRApplicationModule(QObject *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~OCRApplicationModule();

    /*!
     * Get class object instance.
     */
    static OCRApplicationModule *instance();

public Q_SLOTS:
    /*!
     * Application quit.
     */
    void quit();

private:
    static OCRApplicationModule *m_instance;

};

#endif // OCRAPPLICATIONMODULE_H
