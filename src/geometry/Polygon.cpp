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

#include "geometry/Polygon.h"
#include "geometry/Ring.h"

Polygon::Polygon()
    : Polycurve()
    , m_rings()
{
}

Polygon::Polygon(int size)
    : Polycurve(size)
    , m_rings(size)
{

}

Polygon::Polygon(const QRectF &extent)
    : Polycurve(extent)
    , m_rings()
{
}

Polygon::Polygon(std::initializer_list<QPointF> points)
    : Polycurve()
    , m_rings()
{
    m_rings.push_back(new Ring(points));
}

Polygon::~Polygon()
{
    for (Ring *ring : m_rings)
    {
        delete ring;
    }

    m_rings.clear();
}

RingList &Polygon::rings()
{
    return m_rings;
}

const RingList &Polygon::rings() const
{
    return m_rings;
}

Geometry::Type Polygon::type() const
{
    return Geometry::Type::Polygon;
}

