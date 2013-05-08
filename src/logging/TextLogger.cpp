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

#include "TextLogger.h"

#include <QtCore/QString>
#include <QtCore/QDate>

#include <assert.h>

//------------------------------------------------------------------------------
const TextLogger::Categories TextLogger::categories = fillCategories();
const TextLogger::Priorities TextLogger::priorities = fillPriorities();

//------------------------------------------------------------------------------
TextLogger::TextLogger(QTextStream &output)
    : m_outputStream(output)
{
}

//------------------------------------------------------------------------------
void TextLogger::log(const QString &message, ILogger::Category categoryy, ILogger::Priority priority)
{
    static const QString messagePattern = "[%1] %2: %3. Prioriry: %4.";
    static const QString dateFormat = "dd MMM yyyy,  hh:mm:ss";

    QString formatedMessage = messagePattern
            .arg(QDateTime::currentDateTime().toString(dateFormat))
            .arg(categories[categoryy])
            .arg(message)
            .arg(priorities[priority]);

    m_outputStream << formatedMessage << endl;
}

//------------------------------------------------------------------------------
TextLogger::Categories TextLogger::fillCategories()
{
    Categories categories;
    categories.insert(ILogger::Debug, "Debug");
    categories.insert(ILogger::Info, "Info");
    categories.insert(ILogger::Warning, "Warning");
    categories.insert(ILogger::Error, "Error");

    return categories;
}

//------------------------------------------------------------------------------
TextLogger::Priorities TextLogger::fillPriorities()
{
    Priorities priorities;
    priorities.insert(ILogger::None, "None");
    priorities.insert(ILogger::Low, "Low");
    priorities.insert(ILogger::Medium, "Medium");
    priorities.insert(ILogger::High, "High");

    return priorities;
}

//------------------------------------------------------------------------------
