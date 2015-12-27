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

#include "geometry/GeometryBase.h"
#include <climits>

GeometryBase::GeometryBase()
    : IGeometry()
    , m_extent()
{
}

GeometryBase::GeometryBase(const QRectF &extent)
    : IGeometry()
    , m_extent()
{
    setExtent(extent);
}

GeometryBase::~GeometryBase()
{
}

const QRectF &GeometryBase::extent() const
{
    return m_extent;
}

void GeometryBase::setExtent(const QRectF &extent)
{
    m_extent = extent.normalized();

    // adjust extent. Otherwise, for horisontal or vertical linex W or H are 0, and filters fail to find them
    if (std::abs(m_extent.width()) < std::numeric_limits<double>::min())
    {
        m_extent.setWidth(0.000001);
    }

    if (std::abs(m_extent.height()) < std::numeric_limits<float>::min())
    {
        m_extent.setHeight(0.000001);
    }
}

