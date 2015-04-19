/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include "cartoUI/FeatureRendererWidgetCreator.h"
#include "cartoUI/SimpleRendererWidget.h"
//#include "cartoUI/CategorizedRendererWidget.h"
#include <carto/SimpleRenderer.h>

FeatureRendererWidgetCreator::FeatureRendererWidgetCreator()
    : IFeatureRendererVisitor()
    , m_rendererWidget(nullptr)
    , m_parent(nullptr)
{
}

FeatureRendererWidgetCreator::~FeatureRendererWidgetCreator()
{
    Q_ASSERT(m_rendererWidget == nullptr);
}

FeatureRendererWidget *FeatureRendererWidgetCreator::createWidget(IFeatureRenderer *renderer, QWidget *parent)
{
    m_parent = parent;
    renderer->accept(*this);
    FeatureRendererWidget *tmp = m_rendererWidget;
    m_rendererWidget = nullptr;
    m_parent = nullptr;
    return tmp;
}

void FeatureRendererWidgetCreator::visit(SimpleRenderer &renderer)
{
    m_rendererWidget = new SimpleRendererWidget(&renderer, m_parent);
}

void FeatureRendererWidgetCreator::visit(CategorizedRenderer &renderer)
{
    //m_rendererWidget = new CategorizedRendererWidget(&renderer, m_parent);
}
