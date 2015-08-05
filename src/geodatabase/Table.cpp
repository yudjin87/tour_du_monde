/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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
#include "geodatabase/Fields.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QVariant>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("Table");
}

Table::Table(IFeatureWorkspace &workspace, const QString &tableName, const QSqlDatabase &database)
    : ITable()
    , m_tableName(tableName)
    , m_workspace(workspace)
    , m_db(database)
    , m_fields(nullptr)
    , m_records()
{
}

Table::~Table()
{
    delete m_fields;
    m_fields = nullptr;
}

const IFields *Table::fields() const
{    
    if (m_fields == nullptr)
    {
        const QSqlRecord fields = m_db.record(m_tableName);
        if (fields.count() == 0)
        {
            Log.e(QString("Can't read metadata from the table \"%1\". This could happen due to very long path to .dbf file").arg(m_tableName));
        }
        const_cast<IFieldsEdit*>(m_fields) = new Fields(fields);
    }

    return m_fields;
}

IRecord *Table::getRecord(const int index) const
{
    if (index < m_records.size())
    {
        return m_records[index].get();
    }

    if (!m_records.empty())
    {
        return nullptr;
    }

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

//    if (!query.seek(index))
//    {
//        Log.e(query.lastError().text());
//        return nullptr;
//    }

    while (query.next())
    {
        m_records.emplace_back(new Record(-1, query.record())); // TODO: index should not be passed at all
    }

    if (index < m_records.size())
    {
        return m_records[index].get();
    }

    return nullptr;
}

std::vector<IRecordUPtr> Table::execute(const QString &sqlQuery) const
{
    QSqlQuery query(m_db);
    query.prepare(QString(sqlQuery).arg(m_tableName));
    if (!query.exec())
    {
        Log.e(query.lastError().text());
        return std::vector<IRecordUPtr>();
    }

    std::vector<IRecordUPtr> result;
    while (query.next())
    {
        result.emplace_back(new Record(-1, query.record())); // TODO: index should not be passed at all
    }

    return result;
}

