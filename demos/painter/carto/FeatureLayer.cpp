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

#include <carto/FeatureLayer.h>
#include <carto/FeatureLayerDrawingTask.h>
#include <carto/ILayerVisitor.h>

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
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QFileInfo>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("FeatureLayer");
}

//------------------------------------------------------------------------------
FeatureLayer::FeatureLayer(QObject *parent)
    : AbstractLayer(parent)
    , m_featureClass(nullptr)
    , m_featureRenderer(new FeatureRenderer())
{
}

//------------------------------------------------------------------------------
FeatureLayer::~FeatureLayer()
{
    delete m_featureClass;
    m_featureClass = nullptr;

    delete m_featureRenderer;
    m_featureRenderer = nullptr;
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

    IFeatureClass::FeatureList features = m_featureClass->search(filter);

    FeatureLayerDrawingTask* task = new FeatureLayerDrawingTask(std::move(features), m_featureRenderer);
    display->postDrawingTask(IDrawingTaskPtr(task));
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

    QFileInfo fileName(featureClass->source());
    setName(fileName.baseName());

    ISymbol* defaultSymbol = nullptr;
    switch (m_featureClass->shapeType())
    {
    case GeometryPoint:
        defaultSymbol = new SimpleMarkerSymbol();
        break;

    case GeometryPolyline:
        defaultSymbol = new SimpleLineSymbol();
        break;

    case GeometryPolygon:
        defaultSymbol = new SimpleFillSymbol();
        break;

    default:
        break;
    }

    m_featureRenderer->setSymbol(defaultSymbol);
}

//------------------------------------------------------------------------------
void FeatureLayer::accept(ILayerVisitor &visitor)
{
    visitor.visit(*this);
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
