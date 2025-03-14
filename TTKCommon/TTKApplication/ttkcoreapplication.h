#ifndef TTKCOREAPPLICATION_H
#define TTKCOREAPPLICATION_H

/***************************************************************************
 * This file is part of the TTK Library Module project
 * Copyright (C) 2015 - 2025 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QCoreApplication>
#include "ttkprivate.h"

class TTKCoreApplicationPrivate;

/*! @brief The class of the ttk core application.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT TTKCoreApplication : public QCoreApplication
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
    */
    TTKCoreApplication(int &argc, char **argv);
    TTKCoreApplication(const QString &id, int &argc, char **argv);

    /*!
     * Check the current server is running or not.
    */
    bool isRunning() const;
    /*!
     * Get current server id.
    */
    QString id() const noexcept;

Q_SIGNALS:
    /*!
     * Emit when the current message received.
    */
    void messageReceived(const QString &message);

public Q_SLOTS:
    /*!
     * Emit when the current message received.
    */
    bool sendMessage(const QString &message, int timeout = 5000);

private:
    /*!
     * Init the system parameter.
    */
    void initialize(const QString &id = {});

private:
    TTK_DECLARE_PRIVATE(TTKCoreApplication)

};

#endif // TTKCOREAPPLICATION_H
