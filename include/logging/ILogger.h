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

#ifndef ILOGGER_H
#define ILOGGER_H

#include "logging/logging_global.h"

#include <QtCore/QObject>
#include <QtCore/QString>

/*!
 * @brief
 *   The ILogger class is just a facade for the specified application logging system.
 * @details
 *   It provides a well-known interface, used at least by the BootloaderBase and
 *   derived loaders during loading sequence. There are two predefined simple loggers: TextLogger
 *   and NullLogger, and the TextLogger instance created by the BootloaderBase during the loading
 *   sequence, so you can access pointer to ILogger instance through the IServiceLocator:
 * @code
 *   IServiceLocator *locator = getLocator();
 *   ILogger *loggerFacade = locator.locate<ILogger>();
 * @endcode
 *   To instantiate your own logger facade to the application logging system you have to override
 *   BootloaderBase::_createLogger() method in your own bootloader, that returns pointer to the ILogger.
 */
class LOGGING_API ILogger : public QObject
{
    Q_OBJECT
public:
    /*!
     * @details
     *   Defines values for the categories used by the ILogger. These categories might be usefull
     *   for the futher logging exploration.
     */
    enum Category
    {
        Debug = 0,
        Info,
        Warning,
        Error
    };

    /*!
     * @details
     *   Defines values for the priorities used by ILogger. These priorities might be usefull
     *   for the futher logging exploration.
     */
    enum Priority
    {
        None = 0,
        Low,
        Medium,
        High
    };

public:
    ILogger(){}
    virtual ~ILogger(){}

    /*!
     * @details
     *   Write a new log entry with the specified category and priority.
     */
    virtual void log(const QString &message, Category categoryy = Debug, Priority priority = Low) = 0;

private:
    Q_DISABLE_COPY(ILogger)
};

#endif // ILOGGER_H
