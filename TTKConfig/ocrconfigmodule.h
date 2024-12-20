#ifndef OCRCONFIGMODULE_H
#define OCRCONFIGMODULE_H

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
#include "ocrconfigdefine.h"

/*! @brief The class of the initialize module.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT OCRConfigModule : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit OCRConfigModule(QObject *parent = nullptr);

    /*!
     * Check current setting file's validation.
     */
    void valid() const;
    /*!
     * Init parameters.
     */
    void initialize() const;
    /*!
     * Reset config parameters.
     */
    void reset() const;

private:
    /*!
     * Check current dir is exist, no, just create it.
     */
    void directoryExist(const QString &name) const;
    /*!
     * Check related dir is exist.
     */
    void checkDirectoryExist() const;
    /*!
     * Check related file is exist.
     */
    void checkFileNeededExist() const;
    /*!
     * Copy file by overwrite.
     */
    void copyFileOverwrite(const QString &origin, const QString &des) const;
    /*!
     * Copy file.
     */
    void copyFile(const QString &origin, const QString &des) const;
#ifdef Q_OS_UNIX
    /*!
     * Copy linux shell file.
     */
    void copyLinuxShellFile(const QString &name, const QString &path) const;
#endif

};

#endif // OCRCONFIGMODULE_H
