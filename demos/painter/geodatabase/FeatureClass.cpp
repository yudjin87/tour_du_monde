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

//------------------------------------------------------------------------------
FeatureClass::FeatureClass(GeometryType shapeType, const QRectF &extent)
    : m_type(shapeType)
    , m_features()
    , m_extent(extent)
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
IFeature &FeatureClass::createFeature()
{
    Feature *newFeature = new Feature(m_type);
    m_features.push_back(newFeature);

    return *newFeature;
}

//------------------------------------------------------------------------------
const FeatureList &FeatureClass::features() const
{
    return m_features;
}

//------------------------------------------------------------------------------

