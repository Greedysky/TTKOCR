#ifndef OCRAPPLICATION_H
#define OCRAPPLICATION_H

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

#include "ocrabstractmoveresizewidget.h"

class OCRThreadItem;
class OCRApplicationObject;

namespace Ui {
class OCRApplication;
}

/*! @brief The class of the app main widget.
 * @author Greedysky <greedysky@163.com>
 */
class OCR_GUI_EXPORT OCRApplication : public OCRAbstractMoveResizeWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(OCRApplication)
public:
    /*!
     * Object contsructor.
     */
    explicit OCRApplication(QWidget *parent = nullptr);

    virtual ~OCRApplication();

    /*!
     * Get class object instance.
     */
    static OCRApplication *instance();

public Q_SLOTS:
    /*!
     * Application window close.
     */
    void quitWindowClose();
    /*!
     * Open button clicked.
     */
    void openButtonClicked();
    /*!
     * Screenshot button clicked.
     */
    void screenshotButtonClicked();
    /*!
     * Start button clicked.
     */
    void startButtonClicked();
    /*!
     * Clear button clicked.
     */
    void clearButtonClicked();
    /*!
     * Find finished.
     */
    void findFinish();
    /*!
     * Pixmap data Changed.
     */
    void pixmapChanged(const QPixmap &pix);

private:
    /*!
     * Delete all items.
     */
    void deleteItems();
    /*!
     * Detect state changed.
     */
    void stateChanged(bool state);

    Ui::OCRApplication *m_ui;

    int m_count;
    OCRApplicationObject *m_applicationObject;
    QList<OCRThreadItem*> m_fileList;

    static OCRApplication *m_instance;
};

#endif // OCRAPPLICATION_H
