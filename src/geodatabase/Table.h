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

#pragma once
#include <geodatabase/ITable.h>
#include <geodatabase/IFieldsEdit.h>
#include <geodatabase/IFeatureWorkspace.h>

#include <QtSql/QSqlDatabase>

class Table : public ITable
{
    Q_OBJECT
public:
    Table(IFeatureWorkspace &workspace, const QString& tableName, const QSqlDatabase& database);
    ~Table();

    const IFields* fields() const override;
    IRecord* getRecord(const int index) const override;

    std::vector<IRecordUPtr> execute(const QString& sqlQuery) const override;

private:
    const QString m_tableName;
    IFeatureWorkspace& m_workspace;
    QSqlDatabase m_db;
    IFieldsEdit* m_fields;
    mutable std::vector<IRecordUPtr> m_records;
};
