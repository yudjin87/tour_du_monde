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

#include "Ring.h"
#include "Segment.h"

#include <QtWidgets/QGraphicsItemGroup>

//------------------------------------------------------------------------------
Ring::Ring()
    :m_segments()
{
}

//------------------------------------------------------------------------------
Ring::Ring(const QRectF &extent)
    : AbstractGeometry(extent)
    , m_segments()
{
}

//------------------------------------------------------------------------------
Ring::Ring(std::initializer_list<QPointF> points)
    : AbstractGeometry()
    , m_segments()
{
    m_segments.append(new Segment(points));
}

//------------------------------------------------------------------------------
Ring::~Ring()
{
    clearData();
}

//------------------------------------------------------------------------------
SegmentList &Ring::segments()
{
    return m_segments;
}

//------------------------------------------------------------------------------
const SegmentList &Ring::segments() const
{
    return m_segments;
}

//------------------------------------------------------------------------------
GeometryType Ring::type() const
{
    return GeometryRing;
}

//------------------------------------------------------------------------------
QGraphicsItem *Ring::toGraphics() const
{
//    QGraphicsItemGroup* group = new QGraphicsItemGroup();
//    foreach(Segment *segment, m_segments)
//        segment->toGraphics()->setGroup(group);

//    return group;

    throw "Not implemented!";
}

//------------------------------------------------------------------------------
void Ring::clearData()
{
    foreach(Segment *segment, m_segments)
        delete segment;

    m_segments.clear();
}

//------------------------------------------------------------------------------
