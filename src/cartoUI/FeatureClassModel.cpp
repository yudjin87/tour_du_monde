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

#include "cartoUI/FeatureClassModel.h"
#include <geodatabase/IFeatureClass.h>
#include <geodatabase/ITable.h>
#include <geodatabase/IFields.h>
#include <geodatabase/IField.h>
#include <geodatabase/IRecord.h>

FeatureClassModel::FeatureClassModel(IFeatureClass &featureClass, QObject *parent)
    : QAbstractTableModel(parent)
    , m_featureClass(featureClass)
{
}

FeatureClassModel::~FeatureClassModel()
{
}

int FeatureClassModel::rowCount(const QModelIndex &) const
{
    return m_featureClass.featuresCount();
}

int FeatureClassModel::columnCount(const QModelIndex &) const
{
    const ITable* table = m_featureClass.table();
    const IFields* fields = table->fields();
    return fields->fieldCount();
}

QVariant FeatureClassModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    const ITable* table = m_featureClass.table();
    const IRecord* rec = table->getRecord(index.row());
    if (rec == nullptr)
    {
        return QVariant();
    }
    QVariant data = rec->value(index.column());
    return data;
}

QVariant FeatureClassModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QAbstractTableModel::headerData(section, orientation, role);
    }

    if (orientation == Qt::Vertical)
    {
        return section;
    }

    const ITable* table = m_featureClass.table();
    const IFields* fields = table->fields();
    return fields->field(section)->name();
}

