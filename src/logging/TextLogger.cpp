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

//------------------------------------------------------------------------------
TextLogger::TextLogger(QTextStream &output)
    : LoggerFacade("Root")
    , m_outputStream(output)
{
}

//------------------------------------------------------------------------------
TextLogger::TextLogger(QTextStream &output, const QString &name)
    : LoggerFacade(name)
    , m_outputStream(output)
{
}

//------------------------------------------------------------------------------
LoggerFacade *TextLogger::getLogger(const QString &name)
{
    return new TextLogger(m_outputStream, name);
}

//------------------------------------------------------------------------------
void TextLogger::d(const QString &message)
{
#ifdef QT_DEBUG
    log(message, "Debug");
#else
    Q_UNUSED(message)
#endif
}

//------------------------------------------------------------------------------
void TextLogger::e(const QString &message)
{
    log(message, "Error");
}

//------------------------------------------------------------------------------
void TextLogger::f(const QString &message)
{
    log(message, "Fatal");
}

//------------------------------------------------------------------------------
void TextLogger::i(const QString &message)
{
    log(message, "Info");
}

//------------------------------------------------------------------------------
void TextLogger::t(const QString &message)
{
    log(message, "Trace");
}

//------------------------------------------------------------------------------
void TextLogger::w(const QString &message)
{
    log(message, "Warning");
}

//------------------------------------------------------------------------------
void TextLogger::log(const QString &message, const QString &category)
{
    static const QString messagePattern = "[%1][%2] %3: %4";
    static const QString dateFormat = "dd MMM yyyy, hh:mm:ss.zzz";

    QString formatedMessage = messagePattern
            .arg(QDateTime::currentDateTime().toString(dateFormat))
            .arg(name())
            .arg(category)
            .arg(message);

    m_outputStream << formatedMessage << endl;
}

//------------------------------------------------------------------------------
