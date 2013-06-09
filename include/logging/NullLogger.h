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

#ifndef NULLLOGGER_H
#define NULLLOGGER_H

#include "logging/LoggerFacade.h"

/*!
 * @brief
 *   The NullLogger class is a stub for the carousel logging engine.
 * @details
 *   You might return this object in the overridden function BootloaderBase::createLogger()
 *   if you don't need any logging and/or you lack resources.
 */
class LOGGING_API NullLogger : public LoggerFacade
{
public:
    /*!
     * @details
     * @constructor{LoggerFacade} using "NullLogger" logger name.
     */
    NullLogger();

    /*!
     * @details
     *   Creates and returns a new instance of the TextLogger with specified name.
     */
    LoggerFacade *getLogger(const QString &name);

    /*!
     * @details
     *   Sends a @a debug log message to the output stream.
     *   Debug logs are stripped at runtime in release configuration.
     */
    void d(const QString &message);

    /*!
     * @details
     *   Sends an @a error log message to the output stream.
     */
    void e(const QString &message);

    /*!
     * @details
     *   Sends a @a fatal log message to the output stream.
     */
    void f(const QString &message);

    /*!
     * @details
     *   Sends an @a info log message to the output stream.
     */
    void i(const QString &message);

    /*!
     * @details
     *   Sends a @a trace log message to the output stream.
     */
    void t(const QString &message);

    /*!
     * @details
     *   Sends a @a warning log message to the output stream.
     */
    void w(const QString &message);
};

#endif // NULLLOGGER_H
