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

#include "cartoUI/RendererCategoryCollectionModel.h"
#include "cartoUI/RendererCategoryItem.h"
#include <carto/IRendererCategory.h>

RendererCategoryCollectionModel::RendererCategoryCollectionModel(const IRendererCategoryCollection &categories, const Geometry::Type geometry, QObject *parent)
    : QStandardItemModel(parent)
    , m_categories(categories)
    , m_geometry(geometry)
{
    setHorizontalHeaderLabels({"Symbol", "Value", "Legend"});

    for (const IRendererCategoryUPtr& category : categories)
    {
        onCategoryAdded(category.get());
    }

    connect(&m_categories, &IRendererCategoryCollection::categoryAdded, this, &RendererCategoryCollectionModel::onCategoryAdded);
}

IRendererCategory *RendererCategoryCollectionModel::category(const QModelIndex &index)
{
    if (!index.isValid())
    {
        return nullptr;
    }

    QStandardItem* standardItem = item(index.row(), 0);
    RendererCategoryItem* rendererItem = static_cast<RendererCategoryItem*>(standardItem);
    return &(rendererItem->category());
}

void RendererCategoryCollectionModel::onCategoryAdded(IRendererCategory *category)
{
    QList<QStandardItem *> rowData;
    rowData << new RendererCategoryItem(*category, m_geometry);
    rowData << new QStandardItem(category->value().toString());
    rowData << new QStandardItem("Label: " + category->label());
    appendRow(rowData);
}

