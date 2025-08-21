#ifndef OCRBACKGROUNDMANAGER_H
#define OCRBACKGROUNDMANAGER_H

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

#include <QColor>
#include "ttksingleton.h"

#define G_BACKGROUND_PTR (TTKSingleton<OCRBackgroundManager>::instance())

/*! @brief The class of the manager of dealing with artist pictures.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT OCRBackgroundManager : public QObject
{
    Q_OBJECT
    TTK_DECLARE_SINGLETON_CLASS(OCRBackgroundManager)
public:
    /*!
     * Add observer.
     */
    void addObserver(QObject *object);
    /*!
     * Remove observer.
     */
    void removeObserver(QObject *object);

    /*!
     * Set background picture by path.
     */
    void setBackgroundUrl(const QString &path) noexcept;
    /*!
     * Get background picture path.
     */
    QString backgroundUrl() const noexcept;

Q_SIGNALS:
    /*!
     * Background image changed.
     */
    void backgroundChanged();

private:
    /*!
     * Object constructor.
     */
    OCRBackgroundManager() = default;

    QColor m_skinColor;
    QObjectList m_observer;
    QString m_background;

};

#endif // OCRBACKGROUNDMANAGER_H
