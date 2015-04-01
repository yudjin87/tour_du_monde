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

#include "geodatabase/Feature.h"
#include "geodatabase/IRecord.h"
#include <geometry/IGeometry.h>

Feature::Feature(Geometry::Type type)
    : m_type(type)
    , m_id(-1)
    , m_geometry(nullptr)
{
}

Feature::~Feature()
{
    delete m_geometry;
    m_geometry = nullptr;
}

int Feature::id() const
{
    return m_id;
}

void Feature::setId(int id)
{
    m_id = id;
}

const QRectF &Feature::extent() const
{
    return m_geometry->extent();
}

IGeometry *Feature::geometry()
{
    return m_geometry;
}

const IGeometry *Feature::geometry() const
{
    return m_geometry;
}

void Feature::setGeometry(IGeometry *geometry)
{
    delete m_geometry;
    m_geometry = geometry;
}

Geometry::Type Feature::shapeType() const
{
    return m_type;
}

IRecord *Feature::record()
{
    return nullptr;
}

const IRecord *Feature::record() const
{
    return nullptr;
}
