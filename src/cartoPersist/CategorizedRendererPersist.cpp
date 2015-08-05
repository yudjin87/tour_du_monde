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

#include "cartoPersist/CategorizedRendererPersist.h"
#include "cartoPersist/LegendGroupPersist.h"
#include "cartoPersist/RendererCategoryCollectionPersist.h"
#include <carto/CategorizedRenderer.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

CategorizedRendererPersist::CategorizedRendererPersist()
    : IFeatureRendererPersist()
    , m_renderer(nullptr)
{

}

CategorizedRendererPersist::CategorizedRendererPersist(const CategorizedRenderer &renderer)
    : IFeatureRendererPersist()
    , m_renderer(&renderer)
{
}

void CategorizedRendererPersist::save(QJsonObject &obj)
{
    obj.insert("categoryFieldIndex", m_renderer->categoryFieldIndex());

    LegendGroupPersist legend;
    QJsonObject jsonLegend;
    legend.save(jsonLegend, *m_renderer->legend());
    obj.insert("legendGroup", jsonLegend);

    RendererCategoryCollectionPersist categoriesPersist;
    QJsonObject jsonCategories;
    categoriesPersist.save(jsonCategories, m_renderer->categories());
    obj.insert("categoryCollection", jsonCategories);
}

IFeatureRendererUPtr CategorizedRendererPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "CategorizedRendererPersist: empty object";
        return nullptr;
    }

    const QJsonObject jsonLegend = obj.value("legendGroup").toObject();
    LegendGroupPersist legendGroupPersist;
    ILegendGroupUPtr legend = legendGroupPersist.load(jsonLegend, error);
    if (legend == nullptr)
    {
        return nullptr;
    }

    const QJsonObject jsonCategories = obj.value("categoryCollection").toObject();
    RendererCategoryCollectionPersist categoriesPersist;
    IRendererCategoryCollectionUPtr categories = categoriesPersist.load(jsonCategories, *legend, error);
    if (categories == nullptr)
    {
        return nullptr;
    }

    CategorizedRendererUPtr renderer(new CategorizedRenderer(std::move(legend), std::move(categories)));

    const QJsonValue index = obj.value("categoryFieldIndex");
    if (index.isUndefined())
    {
        if (error) *error = "CategorizedRendererPersist: empty categoryFieldIndex";
        return nullptr;
    }

    renderer->setCategoryFieldIndex(index.toInt());
    return std::move(renderer);
}

