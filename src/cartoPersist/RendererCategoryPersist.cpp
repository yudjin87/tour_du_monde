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

#include "cartoPersist/RendererCategoryPersist.h"
#include "cartoPersist/ISymbolPersist.h"
#include "cartoPersist/SymbolPersistCreator.h"
#include <carto/RendererCategory.h>
#include <carto/ILegendGroup.h>

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

RendererCategoryPersist::RendererCategoryPersist()
{
}

void RendererCategoryPersist::save(QJsonObject &obj, const IRendererCategory &category)
{
    obj.insert("value", category.value().toString());
    obj.insert("label", category.label());
}

IRendererCategoryUPtr RendererCategoryPersist::load(const QJsonObject &obj, ILegendGroup &legend, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "RendererCategoryPersist: empty object";
        return nullptr;
    }

    const QString value = obj.value("value").toString();
    const QString label = obj.value("label").toString();

    ILegendClass* categorySymbol = legend.getClass(label);
    if (categorySymbol == nullptr)
    {
        if (error) *error = QString("RendererCategoryPersist: No Legend class found for \"%1\" category").arg(label);
        return nullptr;
    }

    RendererCategoryUPtr category(new RendererCategory(value, categorySymbol));

    return std::move(category);
}
