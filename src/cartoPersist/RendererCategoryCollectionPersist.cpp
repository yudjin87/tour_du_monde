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

#include "cartoPersist/RendererCategoryCollectionPersist.h"
#include "cartoPersist/RendererCategoryPersist.h"
#include <carto/RendererCategoryCollection.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

RendererCategoryCollectionPersist::RendererCategoryCollectionPersist()
{
}


void RendererCategoryCollectionPersist::save(QJsonObject &obj, const IRendererCategoryCollection &categories)
{
    QJsonArray jsonCategories;
    for (const IRendererCategoryUPtr& category : categories)
    {
        QJsonObject jsonCategoryClass;
        RendererCategoryPersist rendererCategoryPersist;
        rendererCategoryPersist.save(jsonCategoryClass, *category);
        jsonCategories.append(jsonCategoryClass);
    }
    obj.insert("categories", jsonCategories);
}

IRendererCategoryCollectionUPtr RendererCategoryCollectionPersist::load(const QJsonObject &obj, ILegendGroup &legend, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "RendererCategoryCollectionPersist: empty object";
        return nullptr;
    }

    RendererCategoryCollectionUPtr categories(new RendererCategoryCollection());

    const QJsonArray jsonRendererCategories = obj.value("categories").toArray();
    for (const QJsonValue value : jsonRendererCategories)
    {
        const QJsonObject jsonRendererCategoryClass = value.toObject();
        RendererCategoryPersist rendererCategoryPersist;
        IRendererCategoryUPtr category = rendererCategoryPersist.load(jsonRendererCategoryClass, legend, error);
        if (category == nullptr)
        {
            return nullptr;
        }

        categories->addCategory(category.release());
    }

    return std::move(categories);
}

