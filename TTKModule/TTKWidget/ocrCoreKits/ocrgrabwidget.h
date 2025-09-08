#ifndef OCRGRABWIDGET_H
#define OCRGRABWIDGET_H

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

#include <QWidget>
#include "ttkmoduleexport.h"

/*! @brief The class of the grab area widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT OCRGrabWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit OCRGrabWidget(QWidget *parent = nullptr);

Q_SIGNALS:
    /*!
     * Pixmap data Changed.
     */
    void pixmapChanged(const QPixmap &pix);

private:
    /*!
     * Override the widget event.
     */
    virtual void paintEvent(QPaintEvent *event) override final;
    virtual void mouseMoveEvent(QMouseEvent *event) override final;
    virtual void mousePressEvent(QMouseEvent *event) override final;
    virtual void mouseReleaseEvent(QMouseEvent *event) override final;
    virtual void keyPressEvent(QKeyEvent *event) override final;

    bool m_isDrawing;
    QWidget *m_parent;
    QPixmap m_originPixmap;
    QPoint m_startPoint, m_endPoint;

};

#endif // OCRGRABWIDGET_H
