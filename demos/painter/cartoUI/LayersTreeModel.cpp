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

#include <carto/IMap.h>
#include <carto/FeatureLayer.h>
#include <display/FeatureRenderer.h>
#include <display/ISymbol.h>
#include <geometry/Point.h>
#include <geometry/Polygon.h>
#include <geometry/Polyline.h>

#include <QtGui/QPainter>

//------------------------------------------------------------------------------
QMap<GeometryType, AbstractGeometry *> fillThumbnails();
static const QMap<GeometryType, AbstractGeometry *> thumbnails = fillThumbnails();

//------------------------------------------------------------------------------
LayersTreeModel::LayersTreeModel(IMap *map, QObject *parent)
    : QAbstractListModel(parent)
    , m_map(map)
{
    connect(map, SIGNAL(layerAdded(AbstractLayer*)), this, SLOT(onLayerAdded(AbstractLayer*)));
    connect(map, SIGNAL(refreshed()), this, SLOT(onMapRefreshed()));
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
    const FeatureLayer *layer = static_cast<FeatureLayer *>(m_map->layers().at(index.row()));

    switch (role) {
    case Qt::DisplayRole:
        return layer->name();

    case Qt::DecorationRole:
        FeatureRenderer *renderer = layer->renderer();
        return drawThumbnail(renderer->symbol(), layer->shapeType());
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
void LayersTreeModel::onMapRefreshed()
{
    emit dataChanged(QModelIndex(), QModelIndex());
}

//------------------------------------------------------------------------------
QPixmap LayersTreeModel::drawThumbnail(ISymbol *forSymbol, GeometryType type)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    forSymbol->setupPainter(&painter);

    AbstractGeometry *geometry = thumbnails[type];

    forSymbol->draw(geometry);
    forSymbol->resetPainter();

    return pixmap;
}

//------------------------------------------------------------------------------
QMap<GeometryType, AbstractGeometry *> fillThumbnails()
{
    QMap<GeometryType, AbstractGeometry *> map;
    map.insert(GeometryPoint, new Point(8, 8));

#ifdef Q_COMPILER_INITIALIZER_LISTS
    map.insert(GeometryPolyline, new Polyline({QPointF(2, 8), QPointF(14, 8)}));
    map.insert(GeometryPolygon, new Polygon({QPointF(2, 2), QPointF(14, 2), QPointF(14, 14), QPointF(2, 14)}));
#else
    QVector<QPointF> polyline; polyline.append(QPointF(2, 8)); polyline.append(QPointF(14, 8));
    map.insert(GeometryPolyline, new Polyline(polyline));

    QVector<QPointF> polygone; polygone.append(QPointF( 2,  2)); polygone.append(QPointF(14,  2));
                               polygone.append(QPointF(14, 14)); polygone.append(QPointF( 2, 14));
    map.insert(GeometryPolygon, new Polygon(polygone));
#endif // #ifdef Q_COMPILER_INITIALIZER_LISTS

    return map;
}

//------------------------------------------------------------------------------
