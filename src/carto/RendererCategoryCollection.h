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

#pragma once

#include <carto/IRendererCategoryCollection.h>

class CARTO_API RendererCategoryCollection : public IRendererCategoryCollection
{
    Q_OBJECT
public:
    RendererCategoryCollection();

    void addCategory(IRendererCategory* category);
    IRendererCategory* findByValue(const QVariant& value);
    const IRendererCategory* findByValue(const QVariant& value) const;

    IRendererCategoryCollection* clone(ILegendGroup& clonedGroup) const;

    IRendererCategoryVector::const_iterator begin() const override;
    IRendererCategoryVector::const_iterator end() const override;

    void reset(ILegendGroup& newLegend) override;

private:
    RendererCategoryCollection(const RendererCategoryCollection& other);
    RendererCategoryCollection& operator=(const RendererCategoryCollection& other);

private:
    struct CategoryPredicate
    {
        const QVariant m_value;
        CategoryPredicate(const QVariant &value);
        bool operator()(const IRendererCategoryUPtr& category);
    };

private:
    std::vector<IRendererCategoryUPtr> m_categories;
};

typedef std::unique_ptr<RendererCategoryCollection> RendererCategoryCollectionUPtr;
