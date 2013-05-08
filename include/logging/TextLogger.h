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

#include "logging/ILogger.h"

#include <QtCore/QMap>
#include <QtCore/QTextStream>

/*!
 * @brief
 *   The TextLogger class provides the simple logging for the carousel system.
 * @details
 *   Writes output to the QTextStream specified in the constructor with following pattern:
 * @code
 *   [%1] %2: %3. Priority: %4.
 * @endcode
 *   where first parameter is @a datetime, second - @a category, third - @a message, and
 *   fourth - @a priority.
 *   For example:
 * @code
 *   QTextStream out(stdout);
 *   TextLogger logger(out);
 *   logger.log("Hello, carousel!", ILogger::Info, ILogger::Low);
 * @endcode
 *   will printed to the console
 * @code
 *   [18 Jul 2012,  18:04:34] Info: Hello, carousel!. Priority: Low.
 * @endcode
 *
 *   If you does't override BootloaderBase::createLogger() method to instantiate your own
 *   logger facade over the better logging system (e.g., log4cplus), the default logger will
 *   be created with the std::cout stream for output during the loading sequence:
 * @code
 *   ILogger *BootloaderBase::createLogger()
 *   {
 *      static QTextStream text(stdout);
 *      return new TextLogger(text);
 *   }
 * @endcode
 *
 * @note This class is not thread-safe.
 */
class LOGGING_API TextLogger : public ILogger
{
    Q_OBJECT
public:
    /*!
     * @details
     *   Initializes a new instance of the TextLogger class with the specified output
     *   stream for the logging.
     */
    TextLogger(QTextStream &output);

public:
    /*!
     * @details
     *   Write a new log entry with the specified category and priority to the
     *   specified in constructor output stream.
     */
    void log(const QString &message, Category categoryy = Debug, Priority priority = Low);

protected:
    /*!
     *   The categories dictionary containing string representation of the logging categories.
     */
    typedef QMap<ILogger::Category, QString> Categories;
    /*!
     *   The priorities dictionary containing string representation of the logging priorities.
     */
    typedef QMap<ILogger::Priority, QString> Priorities;

private:
    static Categories fillCategories();
    static Priorities fillPriorities();

protected:
    /*!
     * @details
     *   The categories dictionary containing string representation of the logging categories.
     */
    static const Categories categories;

    /*!
     * @details
     *   The priorities dictionary containing string representation of the logging priorities.
     */
    static const Priorities priorities;

    /*!
     * @details
     *   The specified output stream for the logging.
     */
    QTextStream &m_outputStream;

};

#endif // TEXTLOGGER_H
