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
#include <geodatabase/Feature.h>
#include <geodatabase/IFeatureClass.h>


//------------------------------------------------------------------------------
FeatureLayer::FeatureLayer()
    : mp_featureClass(0)
    , mp_featureRenderer(new FeatureRenderer())
{
}

//------------------------------------------------------------------------------
FeatureLayer::~FeatureLayer()
{
    delete mp_featureClass;
    mp_featureClass = 0;

    delete mp_featureRenderer;
    mp_featureRenderer = 0;
}

//------------------------------------------------------------------------------
QRectF FeatureLayer::extent() const
{
    return mp_featureClass->extent();
}

//------------------------------------------------------------------------------
//void FeatureLayer::draw(QGraphicsScene *scene)
//{
//    mp_featureRenderer->setScene(scene);

//    switch (mp_featureClass->shapeType())
//    {
//    case GeometryType::PointType:
//        foreach(Feature *feature, mp_featureClass->getFeatures())
//            mp_featureRenderer->drawPoint(feature->geometry());
//        break;

//    case GeometryType::PolylineType:
//        foreach(Feature *feature, mp_featureClass->getFeatures())
//            mp_featureRenderer->drawPolyline(feature->geometry());
//        break;

//    case GeometryType::PolygonType:
//        foreach(Feature *feature, mp_featureClass->getFeatures())
//            mp_featureRenderer->drawPolygon(feature->geometry());
//        break;

//    default:
//        break;
//    }

//}

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
