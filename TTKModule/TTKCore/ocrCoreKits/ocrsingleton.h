#ifndef OCRSINGLETON_H
#define OCRSINGLETON_H

/* =================================================
 * This file is part of the TTK OCR project
 * Copyright (C) 2015 - 2017 Greedysky Studio

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

#include <QMutex>
#include <QObject>
#include <QScopedPointer>
#include "ocrglobaldefine.h"

template <typename T>
/*! @brief The class of the singleton base.
 * @author Greedysky <greedysky@163.com>
 */
class OCR_CORE_EXPORT OCRSingleton
{
public:
    /*!
     * Get object instance ptr.
     */
    static T* createInstance();
    /*!
     * Get class object name.
     */
    static QString getClassName();

private:
    /*!
     * Object contsructor.
     */
    OCRSingleton(){}

    ~OCRSingleton(){}

    static QMutex m_mutex;
    static QScopedPointer<T> m_instance;
    Q_DISABLE_COPY(OCRSingleton)

};

    ////////////////////////////////////////////////////////////////
    ///                                                           //
    ///              Singleton Implementation                     //
    ///                                                           //
    ////////////////////////////////////////////////////////////////

template<typename T> QMutex OCRSingleton<T>::m_mutex;
template<typename T> QScopedPointer<T> OCRSingleton<T>::m_instance;

template<typename T>
T* OCRSingleton<T>::createInstance()
{
    if(m_instance.isNull())
    {
        m_mutex.lock();
        if(m_instance.isNull())
        {
            m_instance.reset(new T());
        }
        m_mutex.unlock();
    }
    return m_instance.data();
}

template<typename T>
QString OCRSingleton<T>::getClassName()
{
    return "OCRSingleton";
}

    ////////////////////////////////////////////////////////////////
    ///                                                           //
    ///              Singleton Macro                              //
    ///                                                           //
    ////////////////////////////////////////////////////////////////

////Class that will implement the singleton mode,
////must use the macro in it's delare file
#define DECLARE_SINGLETON_CLASS( Class )             \
    friend class OCRSingleton<Class>;              \
    friend struct QScopedPointerDeleter<Class>;

#endif // OCRSINGLETON

