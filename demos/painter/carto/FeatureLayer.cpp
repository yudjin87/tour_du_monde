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
#include <display/SimpleMarkerSymbol.h>
#include <display/SimpleLineSymbol.h>

#include <geodatabase/Feature.h>
#include <geodatabase/IFeatureClass.h>
#include <geodatabase/SpatialFilter.h>
#include <geometry/Polygon.h>

//------------------------------------------------------------------------------
FeatureLayer::FeatureLayer()
    : mp_featureClass(nullptr)
    , mp_featureRenderer(new FeatureRenderer())
    , m_symbol(nullptr)
{
}

//------------------------------------------------------------------------------
FeatureLayer::~FeatureLayer()
{
    delete mp_featureClass;
    mp_featureClass = nullptr;

    delete mp_featureRenderer;
    mp_featureRenderer = nullptr;

    delete m_symbol;
    m_symbol = nullptr;
}

//------------------------------------------------------------------------------
void FeatureLayer::draw(IDisplay *display)
{
    if (mp_featureClass == nullptr)
        return;

    SpatialFilter filter;
    Polygon extent(display->visibleExtent());
    filter.setGeometry(&extent);

    FeatureList features = mp_featureClass->search(filter);
    qDebug(QString("draw %1 features").arg(features.size()).toLatin1());
    mp_featureRenderer->draw(features, display);
}

//------------------------------------------------------------------------------
QRectF FeatureLayer::extent() const
{
    return mp_featureClass->extent();
}

//------------------------------------------------------------------------------
IFeatureClass *FeatureLayer::featureClass()
{
    return mp_featureClass;
}

//------------------------------------------------------------------------------
const IFeatureClass *FeatureLayer::featureClass() const
{
    return mp_featureClass;
}

//------------------------------------------------------------------------------
void FeatureLayer::setFeatureClass(IFeatureClass *featureClass)
{
    delete mp_featureClass;
    mp_featureClass = featureClass;

    delete m_symbol;

    switch (mp_featureClass->shapeType())
    {
    case GeometryPoint:
        m_symbol = new SimpleMarkerSymbol();
        break;

    case GeometryPolyline:
        m_symbol = new SimpleLineSymbol();
        break;

//    case GeometryPolygon:
//        foreach(Feature *feature, mp_featureClass->getFeatures())
//            mp_featureRenderer->drawPolygon(feature->geometry());
//        break;

    default:
        break;
    }

    mp_featureRenderer->setSymbol(m_symbol);
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
