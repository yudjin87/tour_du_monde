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

#include "FeatureClass.h"
#include "Feature.h"
#include "ISpatialFilter.h"

#include <geometry/AbstractGeometry.h>

//------------------------------------------------------------------------------
FeatureClass::FeatureClass(GeometryType shapeType, const QRectF &extent, QString source)
    : m_type(shapeType)
    , m_features()
    , m_extent(extent)
    , m_source(source)
{
}

//------------------------------------------------------------------------------
FeatureClass::~FeatureClass()
{
    foreach(IFeature *feature, m_features)
        delete feature;
}

//------------------------------------------------------------------------------
QRectF FeatureClass::extent() const
{
    return m_extent;
}

//------------------------------------------------------------------------------
GeometryType FeatureClass::shapeType() const
{
    return m_type;
}

//------------------------------------------------------------------------------
IFeature *FeatureClass::createFeature()
{
    Feature *newFeature = new Feature(m_type);
    m_features.push_back(newFeature);

    return newFeature;
}

//------------------------------------------------------------------------------
const IFeatureClass::FeatureList &FeatureClass::features() const
{
    return m_features;
}

//------------------------------------------------------------------------------
IFeatureClass::FeatureList FeatureClass::search(const ISpatialFilter &filter) const
{
    const AbstractGeometry *geometry = filter.geometry();
    const QRectF &extent = geometry->extent();
    FeatureList toReturn;
    for(int i = 0, end = m_features.size(); i != end; ++i) {
        IFeature *feature = m_features[i];
        if (extent.intersects(feature->geometry()->extent()))
            toReturn.push_back(feature);
    }

    return toReturn;
}

//------------------------------------------------------------------------------
const QString &FeatureClass::source() const
{
    return m_source;
}

//------------------------------------------------------------------------------

