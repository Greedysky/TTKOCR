#ifndef OCRGIFLABELWIDGET_H
#define OCRGIFLABELWIDGET_H

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

#include <QLabel>
#include "ttkglobaldefine.h"

class QTimer;

/*! @brief The class of the float gif label widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT OCRGifLabelWidget : public QLabel
{
    Q_OBJECT
public:
    enum class Module
    {
        CicleBlue             /*!< gif cicle blue*/
    };

    /*!
     * Object contsructor.
     */
    explicit OCRGifLabelWidget(QWidget *parent = nullptr);
    /*!
     * Object contsructor.
     */
    explicit OCRGifLabelWidget(Module type, QWidget *parent = nullptr);
    ~OCRGifLabelWidget();

    /*!
     * Set the gif type.
     */
    void setType(Module type);
    /*!
     * Get the gif type.
     */
    Module type() const;

    /*!
     * Set the gif interval.
     */
    void setInterval(int value);

    /*!
     * Get the gif interval.
     */
    int interval() const;
    /*!
     * Set the gif infinited mode.
     */
    void setInfinited(bool s);
    /*!
     * Get the gif infinited mode.
     */
    bool infinited() const;

    /*!
     * Start the gif.
     */
    void start();
    /*!
     * Stop the gif.
     */
    void stop();
    /*!
     * Get current running state.
     */
    inline bool isRunning() const { return m_isRunning; }

public Q_SLOTS:
    /*!
     * Change the current gif index.
     */
    void timeout();

private:
    /*!
     * Infinited mode check.
     */
    bool infinitedModeCheck();

    int m_index;
    Module m_type;
    QTimer *m_timer;
    bool m_isRunning, m_infinited;

};

#endif // OCRGIFLABELWIDGET_H
