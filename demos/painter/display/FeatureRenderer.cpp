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

#include "FeatureRenderer.h"

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

#include <stdlib.h>

//------------------------------------------------------------------------------
FeatureRenderer::FeatureRenderer()
    //: mp_scene(0)
    : m_pen(QColor(rand() % 255, rand() % 255, rand() % 255))
    , m_brush(QColor(rand() % 255, rand() % 255, rand() % 255))
{
    m_pen.setCosmetic(true);
}

//------------------------------------------------------------------------------
FeatureRenderer::~FeatureRenderer()
{
    //mp_scene = 0;
}

/*
//------------------------------------------------------------------------------
QList<QAbstractGraphicsShapeItem *> *FeatureRenderer::drawPoint(const AbstractGeometry *pointGeometry)
{
    if (mp_scene == 0)
        return 0;

    const Point *point = static_cast<const Point *>(pointGeometry);
    QGraphicsItem *item = mp_scene->addEllipse(point->value().x(), point->value().y(), 5, 5, QPen(), QBrush(QColor(255, 0, 0)));
    QAbstractGraphicsShapeItem *abstractItem = static_cast<QAbstractGraphicsShapeItem *>(item);

    QList<QAbstractGraphicsShapeItem *> *list = new QList<QAbstractGraphicsShapeItem *>();
    list->push_back(abstractItem);

    return list;
}

//------------------------------------------------------------------------------
QList<QAbstractGraphicsShapeItem *> *FeatureRenderer::drawPolygon(const AbstractGeometry *polygonGeometry)
{
    if (mp_scene == 0)
        return 0;

    QList<QAbstractGraphicsShapeItem *> *list = new QList<QAbstractGraphicsShapeItem *>();

    const Polygon *polygon = static_cast<const Polygon *>(polygonGeometry);
    const RingList &rings = polygon->value();
    foreach(const Ring *ring, rings) {
        const SegmentList &segments = ring->value();
        foreach(const Segment *segment, segments) {
            QGraphicsPolygonItem *item = mp_scene->addPolygon(segment->value(), QPen(), QBrush(QColor(rand() % 255, rand() % 255, rand() % 255)));
            list->push_back(item);
        }
    }

    return list;
}

//------------------------------------------------------------------------------
QList<QAbstractGraphicsShapeItem *> *FeatureRenderer::drawPolyline(const AbstractGeometry *polylineGeometry)
{
    if (mp_scene == 0)
        return 0;

    QList<QAbstractGraphicsShapeItem *> *list = new QList<QAbstractGraphicsShapeItem *>();

    const Polyline *polyline = static_cast<const Polyline *>(polylineGeometry);
    const RingList &rings = polyline->value();
    foreach(const Ring *ring, rings) {
        const SegmentList &segments = ring->value();
        foreach(const Segment *segment, segments) {
            const QPolygonF &poly = segment->value();
            QPainterPath path(poly[0]);
            for (int i = 1; i < poly.size(); ++i)
                path.lineTo(poly[i]);

            QGraphicsPathItem *item = mp_scene->addPath(path, QPen(QColor(rand() % 255, rand() % 255, rand() % 255)), QBrush());
            list->push_back(item);
        }
    }

    return list;
}

//------------------------------------------------------------------------------
void FeatureRenderer::setScene(QGraphicsScene *scene)
{
    mp_scene = scene;
}

//------------------------------------------------------------------------------
*/
