#ifndef OCRABSTRACTMOVEDIALOG_H
#define OCRABSTRACTMOVEDIALOG_H

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

#include "ocrwidgetrenderer.h"
#include "ttkabstractmovedialog.h"

/*! @brief The class of the moving dialog base.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT OCRAbstractMoveDialog : public TTKAbstractMoveDialog, protected OCRWidgetRenderer
{
    Q_OBJECT
    TTK_DECLARE_MODULE(OCRAbstractMoveDialog)
public:
    /*!
     * Object constructor.
     */
    explicit OCRAbstractMoveDialog(QWidget *parent = nullptr);
    explicit OCRAbstractMoveDialog(bool transparent, QWidget *parent = nullptr);
    /*!
     * Object destructor.
     */
    ~OCRAbstractMoveDialog();

public Q_SLOTS:
    /*!
     * Background image changed.
     */
    void backgroundChanged();
    /*!
     * Override exec function.
     */
    virtual int exec();
    /*!
     * Override show function.
     */
    void show();

};

#endif // OCRABSTRACTMOVEDIALOG_H
