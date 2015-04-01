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

#include <geometry/IGeometry.h>

#include <carousel/logging/LoggerFacade.h>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("FeatureClass");
}

FeatureClass::FeatureClass(Geometry::Type shapeType, const QRectF &extent, QString source)
    : m_type(shapeType)
    , m_features()
    , m_extent(extent)
    , m_source(source)
{
}

FeatureClass::~FeatureClass()
{
    for (IFeature *feature : m_features)
        delete feature;
}

QRectF FeatureClass::extent() const
{
    return m_extent;
}

Geometry::Type FeatureClass::shapeType() const
{
    return m_type;
}

IFeature *FeatureClass::createFeature()
{
    Feature *newFeature = new Feature(m_type);
    m_features.push_back(newFeature);

    return newFeature;
}

const IFeature *FeatureClass::featureById(const int id) const
{
    // in shape files, feature id start from 1, in DB the same
    const int vectorId = id - 1;
    if (vectorId < m_features.size())
    {
        const IFeature *feature = m_features[vectorId];
        Q_ASSERT(feature->id() == id);
        return feature;
    }
    return nullptr;
}

const IFeature *FeatureClass::featureByIndex(const int index) const
{
    if (index < m_features.size())
    {
        return m_features[index];
    }
    return nullptr;
}

IFeatureCollection FeatureClass::search(const ISpatialFilter &filter) const
{
    // TODO: dispatch to filter
    const IGeometry *geometry = filter.geometry();
    const QRectF &extent = geometry->extent();
    IFeatureCollection toReturn;
    for(int i = 0, end = m_features.size(); i != end; ++i) {
        IFeature *feature = m_features[i];
        if (extent.intersects(feature->geometry()->extent()))
            toReturn.push_back(feature);
    }

    return toReturn;
}

const QString &FeatureClass::source() const
{
    return m_source;
}

int FeatureClass::featuresCount() const
{
    return m_features.size();
}


