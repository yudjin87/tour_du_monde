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

#include "geometry/Ring.h"
#include "geometry/Segment.h"
#include "geometry/Point.h"

Ring::Ring()
    : Path()
    , m_segments()
{
}

Ring::Ring(int size)
    : Path(size)
    , m_segments(size)
{

}

Ring::Ring(const QRectF &extent)
    : Path(extent)
    , m_segments()
{
}

Ring::Ring(std::initializer_list<QPointF> points)
    : Path(points) // TODO: points ?
    , m_segments()
{
    //m_segments.push_back(new Segment(points));

    Q_ASSERT(2 < points.size() && "It's not a ring!");

    // TODO: don't close automatically
    const QPointF& first = *points.begin();
    const QPointF& last = *points.end();

    if (first != last)
    {
        this->points().push_back(new Point(first.x(), first.y())); // TODO: close() method
    }
}

Ring::~Ring()
{
    for (Segment *segment : m_segments)
    {
        delete segment;
    }

    m_segments.clear();
}

SegmentList &Ring::segments()
{
    return m_segments;
}

const SegmentList &Ring::segments() const
{
    return m_segments;
}

Geometry::Type Ring::type() const
{
    return Geometry::Type::Ring;
}
