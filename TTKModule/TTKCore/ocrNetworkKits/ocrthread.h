#ifndef OCRTHREAD_H
#define OCRTHREAD_H

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

#include <QNetworkReply>
#include "ttkglobaldefine.h"

class QFile;

/*! @brief The class of the ocr thread item.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT OCRThreadItem : public QObject
{
    Q_OBJECT
public:
    explicit OCRThreadItem(QObject *parent = nullptr)
        : QObject(parent),
          m_index(-1),
          m_obj(nullptr)
    {

    }

    QString m_path;
    int m_index;
    QWidget *m_obj;

};

/*! @brief The class of the ocr thread.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT OCRThread : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(OCRThread)
public:
    /*!
     * Object contsructor.
     */
    explicit OCRThread(QObject *parent = nullptr);
    ~OCRThread();

    /*!
     * Start to query by thread item.
     */
    void start(OCRThreadItem *item);

Q_SIGNALS:
    /*!
     * Find finished.
     */
    void findFinish();

private Q_SLOTS:
    /*!
     * Network download finished.
     */
    void finishedSlot();
    /*!
     * Download reply error.
     */
    void errorSlot(QNetworkReply::NetworkError code);

private:
    QNetworkReply *m_reply;
    QNetworkAccessManager *m_manager;

};

#endif // OCRTHREAD_H
