/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#ifndef ILOGGERENGINE_H
#define ILOGGERENGINE_H

#include <carousel/carousel_global.h>
#include <QtCore/QString>

class CAROUSEL_API ILoggerEngine
{
public:
    /*!
     * @details
     * @constructor{ILoggerEngine}.
     */
    ILoggerEngine(){}
    virtual ~ILoggerEngine(){}

    /*!
     * @details
     *   Sends a @a debug log message.
     *   Default implementation does nothing.
     */
    virtual void d(const QString &message) = 0;

    /*!
     * @details
     *   Sends an @a error log message.
     *   Default implementation does nothing.
     */
    virtual void e(const QString &message) = 0;

    /*!
     * @details
     *   Sends a @a fatal log message.
     *   Default implementation does nothing.
     */
    virtual void f(const QString &message) = 0;

    /*!
     * @details
     *   Sends an @a info log message.
     *   Default implementation does nothing.
     */
    virtual void i(const QString &message) = 0;

    /*!
     * @details
     *   Sends a @a trace log message.
     *   Default implementation does nothing.
     */
    virtual void t(const QString &message) = 0;

    /*!
     * @details
     *   Sends a @a warning log message.
     *   Default implementation does nothing.
     */
    virtual void w(const QString &message) = 0;
};

#endif // ILOGGERENGINE_H
