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

#include "LoggerFacade.h"

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade *LoggerEngine = nullptr;
}

//------------------------------------------------------------------------------
LoggerFacade::LoggerFacade(const QString &name)
    : m_engine(nullptr)
    , m_name(name)
{
}

//------------------------------------------------------------------------------
LoggerFacade::LoggerFacade(LoggerFacade *engine)
    : m_engine(engine)
    , m_name("")
{
}

//------------------------------------------------------------------------------
LoggerFacade *LoggerFacade::logger()
{
    if (m_engine == nullptr)
        m_engine = LoggerFacade::loggerEngine()->getLogger(m_name);

    return m_engine;
}

//------------------------------------------------------------------------------
LoggerFacade::~LoggerFacade()
{
    // TODO: use move constructor
    delete m_engine;
    m_engine = nullptr;
}

//------------------------------------------------------------------------------
LoggerFacade LoggerFacade::createLogger(const QString &name)
{
    return LoggerFacade(name);
}

//------------------------------------------------------------------------------
LoggerFacade *LoggerFacade::loggerEngine()
{
    return LoggerEngine;
}

//------------------------------------------------------------------------------
void LoggerFacade::installLoggerEngine(LoggerFacade *loggerEngine)
{
    LoggerEngine = loggerEngine;
}

//------------------------------------------------------------------------------
LoggerFacade* LoggerFacade::getLogger(const QString &name)
{
    Q_UNUSED(name)
    return this;
}


//------------------------------------------------------------------------------
const QString &LoggerFacade::name() const
{
    return m_name;
}

//------------------------------------------------------------------------------
void LoggerFacade::d(const QString &message)
{
#ifdef QT_DEBUG
    logger()->d(message);
#else
    Q_UNUSED(message)
#endif
}

//------------------------------------------------------------------------------
void LoggerFacade::e(const QString &message)
{
    logger()->e(message);
}

//------------------------------------------------------------------------------
void LoggerFacade::f(const QString &message)
{
    logger()->f(message);
}

//------------------------------------------------------------------------------
void LoggerFacade::i(const QString &message)
{
    logger()->i(message);
}

//------------------------------------------------------------------------------
void LoggerFacade::t(const QString &message)
{
    logger()->t(message);
}

//------------------------------------------------------------------------------
void LoggerFacade::w(const QString &message)
{
    logger()->w(message);
}

//------------------------------------------------------------------------------