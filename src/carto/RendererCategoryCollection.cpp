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

#include "carto/RendererCategoryCollection.h"

#include <carousel/logging/LoggerFacade.h>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("RendererCategoryCollection");
}

RendererCategoryCollection::RendererCategoryCollection()
    : IRendererCategoryCollection()
    , m_categories()
{    
}

RendererCategoryCollection::RendererCategoryCollection(const RendererCategoryCollection &other)
    : IRendererCategoryCollection()
    , m_categories()
{
    for (const IRendererCategoryUPtr& category : other.m_categories)
    {
        m_categories.push_back(IRendererCategoryUPtr(category->clone()));
    }
}

RendererCategoryCollection &RendererCategoryCollection::operator=(const RendererCategoryCollection &other)
{
    if (this == &other)
    {
        return *this;
    }

    for (const IRendererCategoryUPtr& category : other.m_categories)
    {
        m_categories.push_back(IRendererCategoryUPtr(category->clone()));
    }

    return *this;
}

IRendererCategoryCollection *RendererCategoryCollection::clone(ILegendGroup &clonedGroup) const
{
    RendererCategoryCollection* cloned = new RendererCategoryCollection(*this);
    cloned->reset(clonedGroup);
    return cloned;
}

void RendererCategoryCollection::reset(ILegendGroup &newLegend)
{
    for (const IRendererCategoryUPtr& category : m_categories)
    {
        ILegendClass* clonedClass = newLegend.getClass(category->label());
        Q_ASSERT(clonedClass != nullptr);
        category->setLegendClass(clonedClass);
    }
}

IRendererCategoryCollection::IRendererCategoryVector::const_iterator RendererCategoryCollection::begin() const
{
    return m_categories.begin();
}

IRendererCategoryCollection::IRendererCategoryVector::const_iterator RendererCategoryCollection::end() const
{
    return m_categories.end();
}

void RendererCategoryCollection::addCategory(IRendererCategory *category)
{
    Q_ASSERT(category != nullptr);
    IRendererCategoryUPtr uptr(category);

    const IRendererCategory *existed = findByValue(category->value());
    if (existed != nullptr)
    {
        Log.i(QString("Category \"%1\" with value \"%2\" is already existed").arg(existed->label()).arg(existed->value().toString()));
        return;
    }

    m_categories.push_back(std::move(uptr));

    emit categoryAdded(category);
}

IRendererCategory *RendererCategoryCollection::findByValue(const QVariant &value)
{
    return const_cast<IRendererCategory *>(const_cast<const RendererCategoryCollection*>(this)->findByValue(value));
}

const IRendererCategory *RendererCategoryCollection::findByValue(const QVariant &value) const
{
    const auto it = std::find_if(m_categories.begin(), m_categories.end(), CategoryPredicate(value));
    if (it == std::end(m_categories))
    {
        return nullptr;
    }

    const IRendererCategoryUPtr& category = *it;
    return category.get();
}

RendererCategoryCollection::CategoryPredicate::CategoryPredicate(const QVariant &value)
    : m_value(value)
{
}

bool RendererCategoryCollection::CategoryPredicate::operator()(const IRendererCategoryUPtr& category)
{
    return category->value() == m_value;
}
