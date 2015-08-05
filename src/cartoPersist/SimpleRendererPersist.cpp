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

#include "cartoPersist/SimpleRendererPersist.h"
#include "cartoPersist/LegendGroupPersist.h"
#include <carto/SimpleRenderer.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

SimpleRendererPersist::SimpleRendererPersist()
    : IFeatureRendererPersist()
    , m_renderer(nullptr)
{

}

SimpleRendererPersist::SimpleRendererPersist(const SimpleRenderer &renderer)
    : IFeatureRendererPersist()
    , m_renderer(&renderer)
{
}

void SimpleRendererPersist::save(QJsonObject &obj)
{
    LegendGroupPersist legendGroupPersist;
    QJsonObject jsonLegend;
    legendGroupPersist.save(jsonLegend, *m_renderer->legend());
    obj.insert("legendGroup", jsonLegend);
}

IFeatureRendererUPtr SimpleRendererPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "SimpleRendererPersist: empty object";
        return nullptr;
    }

    SimpleRendererUPtr renderer(new SimpleRenderer());
    const QJsonObject jsonLegend = obj.value("legendGroup").toObject();
    LegendGroupPersist legendGroupPersist;
    ILegendGroupUPtr legend = legendGroupPersist.load(jsonLegend, error);
    if (legend == nullptr)
    {
        return nullptr;
    }

    renderer->resetLegend(std::move(legend));
    return std::move(renderer);
}

