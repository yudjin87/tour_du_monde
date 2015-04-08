/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include "geodatabase/Table.h"
#include "geodatabase/Record.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QVariant>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("Table");
}

Table::Table(const QString &tableName, const QSqlDatabase &database)
    : ITable()
    , m_tableName(tableName)
    , m_db(database)
{
}

Table::~Table()
{
}

const IFields *Table::fields() const
{
    return nullptr;
}

const IRecord *Table::getRecord(const int index) const
{
    QSqlQuery query(m_db);
    query.prepare(QString("SELECT * FROM \"%1\"").arg(m_tableName));
    if (!query.exec())
    {
        Log.e(query.lastError().text());
        return nullptr;
    }

    if (query.size() == 0)
    {
        Log.i(QString("%1: no record at index %2 was found").arg(m_tableName).arg(index));
        return nullptr;
    }

    if (!query.seek(index - 1)) // TODO: indexes start from 0, IDs from 1. Check it and make common
    {
        Log.e(query.lastError().text());
        return nullptr;
    }

   // Q_ASSERT(query.size() == 1);

    Record* record = new Record(query.record()); // TODO!! take ownership!! memory leak!!
    return record;
}

