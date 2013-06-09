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

#ifndef LOGGERFACADE_H
#define LOGGERFACADE_H

#include <carousel/logging/logging_global.h>

#include <QtCore/QObject>
#include <QtCore/QString>

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
class LOGGING_API LoggerFacade
{
public:
    /*!
     * @details
     * @constructor{LoggerFacade} using specified logger name.
     */
    LoggerFacade(const QString &name);
    virtual ~LoggerFacade();

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
     *   Gets an installed logger engine.
     *
     *   Usually you do not use it. Use LoggerFacade::createLogger() instead.
     */
    static LoggerFacade* loggerEngine();

    /*!
     * @details
     *   Installs a logger engine which will be used at least by carousel libraries and its
     *   components.
     *
     *   Logger engine is installed by the BootloaderBase during the loading sequence.
     *   By default TextLogger is installed, but it is strongly recomended to use some
     *   robust logging engine (e.g. log4cplus). To do it you should override
     *   BootloaderBase::createLoggerEngine() method in your own bootloader and return pointer
     *   to the new logging engine facade.
     */
    static void installLoggerEngine(LoggerFacade *loggerEngine);

    /*!
     * @details
     *   Retrieves a logger with name @a name.
     *
     *   Depends on installed logging engine it can return named logger if it already exists,
     *   or create a new instance, otherwise.
     *
     *   Default implementation just returns already created instance regardless of the @a name.
     */
    virtual LoggerFacade *getLogger(const QString &name);

    /*!
     * @details
     *   Sends a @a debug log message.
     *   Default implementation does nothing.
     */
    virtual void d(const QString &message);

    /*!
     * @details
     *   Sends an @a error log message.
     *   Default implementation does nothing.
     */
    virtual void e(const QString &message);

    /*!
     * @details
     *   Sends a @a fatal log message.
     *   Default implementation does nothing.
     */
    virtual void f(const QString &message);

    /*!
     * @details
     *   Sends an @a info log message.
     *   Default implementation does nothing.
     */
    virtual void i(const QString &message);

    /*!
     * @details
     *   Sends a @a trace log message.
     *   Default implementation does nothing.
     */
    virtual void t(const QString &message);

    /*!
     * @details
     *   Sends a @a warning log message.
     *   Default implementation does nothing.
     */
    virtual void w(const QString &message);

    /*!
     * @details
     *   The name which will append in the log message to the output stream.
     */
    const QString &name() const;

protected:
    /*!
     * @details
     * @constructor{LoggerFacade} using specified logger engine and empty name.
     */
    LoggerFacade(LoggerFacade *engine);

private:
    LoggerFacade *logger();

private:
    LoggerFacade *m_engine;
    QString m_name;
};

#endif // LOGGERFACADE_H
