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

#pragma once
#include <carousel/carousel_global.h>

#include <QtCore/QString>

class ILoggerEngine;
class ILoggerEngineCreator;

/*!
 * @brief
 *   The LoggerFacade class is just a facade for the specified application logging engine.
 * @details
 *   This class provides a well-known interface and used at least by the carousel library and
 *   its components. It is strongly recomended to create your own logger facade over some better
 *   logging engine (e.g., log4cplus).
 *
 *   The order in terms of verbosity, from least to most is Fatal, Error, Warning, Info, Debug, Trace.
 *   Trace should never be compiled into an application except during development. Debug logs
 *   are compiled in but should be stripped at runtime (in your logging engine). Fatal, error,
 *   warning and info logs are always kept.
 *
 *   There is a predefined simple logger - TextLogger which is created by
 *   the BootloaderBase during the loading sequence by default, so you can access pointer
 *   to LoggerFacade instance through the loggerEngine():
 *
 * @code
 *   LoggerFacade Log = LoggerFacade::loggerEngine()->getLogger("MyLoggerName");
 * @endcode
 *
 *   To instantiate your own logger facade to the application logging engine you have to override
 *   BootloaderBase::createLoggerEngine() method in your own bootloader, that returns pointer to
 *   the LoggerFacade.
 */
class CAROUSEL_API LoggerFacade
{
public:
    /*!
     * @details
     * @constructor{LoggerFacade} using specified logger name.
     */
    LoggerFacade(const QString &name);
    ~LoggerFacade();

    /*!
     * @details
     *   Creates a logger using installed logger engine.
     *
     *   You should use it every time when you want to get a logger:
     * @code
     *   LoggerFacade Log = LoggerFacade::createLogger("MyLoggerName");
     * @endcode
     */
    static LoggerFacade createLogger(const QString &name);

    /*!
     * @details
     *   Gets an installed logger engine creator.
     *
     *   Usually you do not use it. Use LoggerFacade::createLogger() instead.
     */
    static ILoggerEngineCreator *loggerEngine();

    /*!
     * @details
     *   Installs a logger engine creator which will be used for engine creation at least
     *   by carousel libraries and its components.
     *
     *   Logger engine creator is installed by the BootloaderBase during the loading sequence.
     *   By default TextLogger is installed, but it is strongly recomended to use some
     *   robust logging engine (e.g. log4cplus). To do it you should override
     *   BootloaderBase::createLoggerEngine() method in your own bootloader and return pointer
     *   to the new logging engine facade.
     */
    static void installLoggerEngineCreator(ILoggerEngineCreator *loggerEngine);

    /*!
     * @details
     *   Sends a @a debug log message.
     *   Default implementation does nothing.
     */
    void d(const QString &message);

    /*!
     * @details
     *   Sends an @a error log message.
     *   Default implementation does nothing.
     */
    void e(const QString &message);

    /*!
     * @details
     *   Sends a @a fatal log message.
     *   Default implementation does nothing.
     */
    void f(const QString &message);

    /*!
     * @details
     *   Sends an @a info log message.
     *   Default implementation does nothing.
     */
    void i(const QString &message);

    /*!
     * @details
     *   Sends a @a trace log message.
     *   Default implementation does nothing.
     */
    void t(const QString &message);

    /*!
     * @details
     *   Sends a @a warning log message.
     *   Default implementation does nothing.
     */
    void w(const QString &message);

private:
    ILoggerEngine *logger();

private:
    ILoggerEngine *m_engine;
    QString m_name;
};

