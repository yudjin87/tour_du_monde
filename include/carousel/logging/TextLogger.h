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

#ifndef TEXTLOGGER_H
#define TEXTLOGGER_H

#include <carousel/logging/ILoggerEngine.h>
#include <carousel/logging/ILoggerEngineCreator.h>

#include <QtCore/QTextStream>

/*!
 * @brief
 *   The TextLogger class provides the simple logging for the carousel engine.
 * @details
 *   Writes output to the QTextStream specified in the constructor with following pattern:
 * @code
 *   [%1][%2] %3: %4
 * @endcode
 *   where first parameter is @a datetime, second logger name, third - @a category and
 *   fourth - @a message.
 *   For example:
 * @code
 *   QTextStream out(stdout);
 *   TextLogger logger(out);
 *   logger.d("Hello, carousel!");
 * @endcode
 *   will printed to the console
 * @code
 *   [18 Jul,  18:04:34.056][Debug] Root: Hello, carousel!
 * @endcode
 *
 *   If you does't override BootloaderBase::createLoggerEngine() method to instantiate your own
 *   logger facade over the better logging engine (e.g., log4cplus), the default logger will
 *   be created with the std::cout stream for output during the loading sequence:
 * @code
 *   LoggerFacade *BootloaderBase::createLoggerEngine()
 *   {
 *      static QTextStream text(stdout);
 *      return new TextLogger(text);
 *   }
 * @endcode
 *
 * @note This class is not thread-safe.
 */
class LOGGING_API TextLogger : public ILoggerEngine, public ILoggerEngineCreator
{
public:
    /*!
     * @details
     * @constructor{TextLogger} with the specified output stream for the logging.
     *
     *   Sets logger name to @a Root.
     */
    TextLogger(QTextStream &output);

    /*!
     * @details
     * @constructor{TextLogger} with the specified name and output stream for the logging.
     *
     *   The name will append in the log message.
     */
    TextLogger(QTextStream &output, const QString &name);

    /*!
     * @details
     *   Creates and returns a new instance of the TextLogger with specified name.
     */
    ILoggerEngine *getLogger(const QString &name) override;

    /*!
     * @details
     *   Sends a @a debug log message to the output stream.
     *   Debug logs are stripped at runtime in release configuration.
     */
    void d(const QString &message) override;

    /*!
     * @details
     *   Sends an @a error log message to the output stream.
     */
    void e(const QString &message) override;

    /*!
     * @details
     *   Sends a @a fatal log message to the output stream.
     */
    void f(const QString &message) override;

    /*!
     * @details
     *   Sends an @a info log message to the output stream.
     */
    void i(const QString &message) override;

    /*!
     * @details
     *   Sends a @a trace log message to the output stream.
     */
    void t(const QString &message) override;

    /*!
     * @details
     *   Sends a @a warning log message to the output stream.
     */
    void w(const QString &message) override;

protected:
    virtual void log(const QString &message, const QString &category);

    /*!
     * @details
     *   The name which will append in the log message to the output stream.
     */
    const QString &name() const;

protected:
    /*!
     * @details
     *   The specified output stream for the logging.
     */
    QTextStream &m_outputStream;

private:
    QString m_name;
};

#endif // TEXTLOGGER_H
