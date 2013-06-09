/*
 * BEGIN_COMMON_COPYRIGHT_HEADER
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

/*
#include "FeatureLayerModel.h"

#include "GraphicsPoinItem.h"

#include <carto/FeatureLayer.h>
#include <display/FeatureRenderer.h>
#include <geodatabase/FeatureClass.h>
#include <geodatabase/IFeature.h>

#include <geometry/AbstractGeometry.h>
#include <geometry/Polygon.h>
#include <geometry/Polyline.h>
#include <geometry/Ring.h>
#include <geometry/Point.h>
#include <geometry/Segment.h>

#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QAbstractGraphicsShapeItem>
#include <QtWidgets/QGraphicsPathItem>
#include <QtWidgets/QGraphicsPolygonItem>

#include <QtCore/QtAlgorithms>

//------------------------------------------------------------------------------
FeatureLayerModel::FeatureLayerModel(const FeatureLayer *data)
    : mp_data(data)
    , m_points()
    , m_polygons()
    , m_polylines()
{
}

//------------------------------------------------------------------------------
FeatureLayerModel::~FeatureLayerModel()
{
    qDeleteAll(m_points);

    qDeleteAll(m_polygons);

    qDeleteAll(m_polylines);
}

//------------------------------------------------------------------------------
void FeatureLayerModel::draw(QGraphicsScene *scene)
{
    switch (mp_data->featureClass()->shapeType())
    {
    case GeometryPoint:
        foreach(IFeature *feature, mp_data->featureClass()->getFeatures())
            m_points.append(drawPoint(feature->geometry(), scene));
        break;

    case GeometryPolyline:
        foreach(IFeature *feature, mp_data->featureClass()->getFeatures())
            m_polylines.append(drawPolyline(feature->geometry(), scene));
        break;

    case GeometryPolygon:
        foreach(IFeature *feature, mp_data->featureClass()->getFeatures())
            m_polygons.append(drawPolygon(feature->geometry(), scene));
        break;

    default:
        break;
    }
}

//------------------------------------------------------------------------------
QList<QAbstractGraphicsShapeItem *> FeatureLayerModel::drawPoint(const AbstractGeometry *pointGeometry, QGraphicsScene *scene) const
{
    if (scene == 0)
        return QList<QAbstractGraphicsShapeItem *>();

    const Point *point = static_cast<const Point *>(pointGeometry);
    GraphicsPoinItem *item = new GraphicsPoinItem(point->point());
    item->setPen(mp_data->renderer()->pen());
    item->setBrush(mp_data->renderer()->brush());

    scene->addItem(item);

    QList<QAbstractGraphicsShapeItem *> list;
    list.push_back(item);

    return list;
}

//------------------------------------------------------------------------------
QList<QAbstractGraphicsShapeItem *> FeatureLayerModel::drawPolygon(const AbstractGeometry *polygonGeometry, QGraphicsScene *scene) const
{
    if (scene == 0)
        return QList<QAbstractGraphicsShapeItem *>();

    QList<QAbstractGraphicsShapeItem *> list;

    const Polygon *polygon = static_cast<const Polygon *>(polygonGeometry);
    const RingList &rings = polygon->rings();
    foreach(const Ring *ring, rings) {
        const SegmentList &segments = ring->segments();
        foreach(const Segment *segment, segments) {
            QGraphicsPolygonItem *item = scene->addPolygon(segment->curve(), mp_data->renderer()->pen(), mp_data->renderer()->brush());
            list.push_back(item);
        }
    }

    return list;
}

//------------------------------------------------------------------------------
QList<QAbstractGraphicsShapeItem *> FeatureLayerModel::drawPolyline(const AbstractGeometry *polylineGeometry, QGraphicsScene *scene) const
{
    if (scene == 0)
        return QList<QAbstractGraphicsShapeItem *>();

    QList<QAbstractGraphicsShapeItem *> list;

    const Polyline *polyline = static_cast<const Polyline *>(polylineGeometry);
    const RingList &rings = polyline->rings();
    foreach(const Ring *ring, rings) {
        const SegmentList &segments = ring->segments();
        foreach(const Segment *segment, segments) {
            const QPolygonF &poly = segment->curve();
            QPainterPath path(poly[0]);
            for (int i = 1; i < poly.size(); ++i)
                path.lineTo(poly[i]);

            QGraphicsPathItem *item = scene->addPath(path, mp_data->renderer()->pen());
            list.push_back(item);
        }
    }

    return list;
}

//------------------------------------------------------------------------------
*/
