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

#include "LayersTreeModel.h"

#include <carto/Map.h>
#include <carto/AbstractLayer.h>
#include <display/FeatureRenderer.h>

#include <QtGui/QPixmap>

//------------------------------------------------------------------------------
LayersTreeModel::LayersTreeModel(Map *map, QObject *parent)
    : QAbstractListModel(parent)
    , m_map(map)
{
    connect(map, SIGNAL(layerAdded(AbstractLayer*)), this, SLOT(onLayerAdded(AbstractLayer*)));
}

//------------------------------------------------------------------------------
int LayersTreeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_map->layers().size();
}

//------------------------------------------------------------------------------
QVariant LayersTreeModel::data(const QModelIndex &index, int role) const
{
    const AbstractLayer *layer = m_map->layers().at(index.row());

    switch (role) {
    case Qt::DisplayRole:
        return layer->name();

    case Qt::DecorationRole:
        //FeatureRenderer *renderer = layer->renderer();
        QPixmap pixmap(10, 10);
        //pixmap.fill(renderer->brush().color());
        pixmap.fill(Qt::red);
        return pixmap;
    }
    return QVariant();
}

//------------------------------------------------------------------------------
void LayersTreeModel::onLayerAdded(AbstractLayer *layer)
{
    Q_UNUSED(layer);
    beginInsertRows(QModelIndex(), 0, m_map->layers().size());
    endInsertRows();
}

//------------------------------------------------------------------------------
