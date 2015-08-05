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

#include <carto/FeatureLayer.h>
#include <carto/FeatureLayerDrawingTask.h>
#include <carto/ILayerVisitor.h>
#include <carto/SimpleRenderer.h>

#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>

#include <geodatabase/Feature.h>
#include <geodatabase/IFeatureClass.h>
#include <geodatabase/SpatialFilter.h>
#include <geometry/Polygon.h>
#include <carousel/logging/LoggerFacade.h>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("FeatureLayer");
}

FeatureLayer::FeatureLayer(QObject *parent)
    : AbstractLayer(parent)
    , m_featureClass(nullptr)
    , m_featureRenderer(nullptr)
{
}

FeatureLayer::~FeatureLayer()
{
    delete m_featureClass;
    m_featureClass = nullptr;
}

LayerType FeatureLayer::type() const
{
    return LayerType::FeatureLayer;
}

Geometry::Type FeatureLayer::shapeType() const
{
    return m_featureClass->shapeType();
}

IFeatureRenderer *FeatureLayer::renderer()
{
    return m_featureRenderer.get();
}

const IFeatureRenderer *FeatureLayer::renderer() const
{
    return m_featureRenderer.get();
}

void FeatureLayer::setRenderer(IFeatureRenderer *newRenderer)
{
    Q_ASSERT(newRenderer != nullptr);

    m_featureRenderer.reset(newRenderer);
    emit rendererChanged(m_featureRenderer.get());
}

void FeatureLayer::draw(IDisplay *display)
{
    if (m_featureClass == nullptr)
        return;

    SpatialFilter filter;
    Polygon extent(display->transformation()->visibleBounds());
    filter.setGeometry(&extent);

    IFeatureCollection features = m_featureClass->search(filter);

    // TODO: race condition, if renderer is changed during drawing
    FeatureLayerDrawingTask* task = new FeatureLayerDrawingTask(std::move(features), m_featureRenderer.get());
    display->postDrawingTask(IDrawingTaskPtr(task));
}

QRectF FeatureLayer::extent() const
{
    if (m_featureClass == nullptr)
    {
        return QRect();
    }

    return m_featureClass->extent();
}

IFeatureClass *FeatureLayer::featureClass()
{
    return m_featureClass;
}

const IFeatureClass *FeatureLayer::featureClass() const
{
    return m_featureClass;
}

void FeatureLayer::setFeatureClass(IFeatureClass *featureClass)
{
    delete m_featureClass;
    m_featureClass = featureClass;

    setName(featureClass->name());

    if (m_featureRenderer == nullptr)
    {
        SimpleRenderer* defaultRenderer = new SimpleRenderer(m_featureClass->shapeType());
        m_featureRenderer.reset(defaultRenderer);
    }
}

void FeatureLayer::accept(ILayerVisitor &visitor)
{
    visitor.visit(*this);
}

void FeatureLayer::show()
{
}

void FeatureLayer::hide()
{
}

