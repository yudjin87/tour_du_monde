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

#include "FeatureLayer.h"

#include <display/FeatureRenderer.h>
#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <display/SimpleFillSymbol.h>
#include <display/SimpleMarkerSymbol.h>
#include <display/SimpleLineSymbol.h>

#include <geodatabase/Feature.h>
#include <geodatabase/IFeatureClass.h>
#include <geodatabase/SpatialFilter.h>
#include <geometry/Polygon.h>

//------------------------------------------------------------------------------
FeatureLayer::FeatureLayer(QObject *parent)
    : AbstractLayer(parent)
    , m_featureClass(nullptr)
    , m_featureRenderer(new FeatureRenderer())
    , m_symbol(nullptr)
{
}

//------------------------------------------------------------------------------
FeatureLayer::~FeatureLayer()
{
    delete m_featureClass;
    m_featureClass = nullptr;

    delete m_featureRenderer;
    m_featureRenderer = nullptr;

    delete m_symbol;
    m_symbol = nullptr;
}

//------------------------------------------------------------------------------
GeometryType FeatureLayer::shapeType() const
{
    return m_featureClass->shapeType();
}

//------------------------------------------------------------------------------
FeatureRenderer *FeatureLayer::renderer() const
{
    return m_featureRenderer;
}

//------------------------------------------------------------------------------
void FeatureLayer::draw(IDisplay *display)
{
    if (m_featureClass == nullptr)
        return;

    SpatialFilter filter;
    Polygon extent(display->transformation()->visibleBounds());
    filter.setGeometry(&extent);

    FeatureList features = m_featureClass->search(filter);
    //qDebug(QString("draw %1 features").arg(features.size()).toLatin1());
    m_featureRenderer->draw(features, display);
}

//------------------------------------------------------------------------------
QRectF FeatureLayer::extent() const
{
    return m_featureClass->extent();
}

//------------------------------------------------------------------------------
IFeatureClass *FeatureLayer::featureClass()
{
    return m_featureClass;
}

//------------------------------------------------------------------------------
const IFeatureClass *FeatureLayer::featureClass() const
{
    return m_featureClass;
}

//------------------------------------------------------------------------------
void FeatureLayer::setFeatureClass(IFeatureClass *featureClass)
{
    delete m_featureClass;
    m_featureClass = featureClass;

    delete m_symbol;

    switch (m_featureClass->shapeType())
    {
    case GeometryPoint:
        m_symbol = new SimpleMarkerSymbol();
        break;

    case GeometryPolyline:
        m_symbol = new SimpleLineSymbol();
        break;

    case GeometryPolygon:
        m_symbol = new SimpleFillSymbol();
        break;

    default:
        break;
    }

    m_featureRenderer->setSymbol(m_symbol);
}

//------------------------------------------------------------------------------
void FeatureLayer::show()
{
}

//------------------------------------------------------------------------------
void FeatureLayer::hide()
{
}

//------------------------------------------------------------------------------
