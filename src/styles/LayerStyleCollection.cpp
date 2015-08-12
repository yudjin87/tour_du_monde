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

#include "styles/LayerStyleCollection.h"
#include <algorithm>

LayerStyleCollection::LayerStyleCollection()
    : ILayerStyleCollection()
    , m_styles()
{
}

LayerStyleCollection::LayerStyleCollection(const LayerStyleCollection &other)
    : ILayerStyleCollection()
    , m_styles()
{
    for (const IFeatureLayerStyleUPtr& style : other.m_styles)
    {
        m_styles.emplace_back(style->clone());
    }
}

LayerStyleCollection &LayerStyleCollection::operator=(const LayerStyleCollection &other)
{
    if (this == &other)
    {
        return *this;
    }

    m_styles.clear();

    for (const IFeatureLayerStyleUPtr& style : other.m_styles)
    {
        m_styles.emplace_back(style->clone());
    }

    emit collectionChanged();

    return *this;
}

ILayerStyleCollection *LayerStyleCollection::clone() const
{
    return new LayerStyleCollection(*this);
}

ILayerStyleCollection::ILayerStyleVector::const_iterator LayerStyleCollection::begin() const
{
    return m_styles.begin();
}

ILayerStyleCollection::ILayerStyleVector::const_iterator LayerStyleCollection::end() const
{
    return m_styles.end();
}

void LayerStyleCollection::add(IFeatureLayerStyleUPtr layerStyle)
{
    if (layerStyle == nullptr)
    {
        return;
    }

    m_styles.push_back(std::move(layerStyle));
    emit collectionChanged();
}

void LayerStyleCollection::add(IFeatureLayerStyle *layerStyle)
{
    add(IFeatureLayerStyleUPtr(layerStyle));
}

IFeatureLayerStyle *LayerStyleCollection::styleByName(const QString &name) const
{
    const auto byName = [name](const IFeatureLayerStyleUPtr& s) { return s->name() == name; };
    const auto it = std::find_if(std::begin(m_styles), std::end(m_styles), byName);
    if (it == std::end(m_styles))
    {
        return nullptr;
    }

    const IFeatureLayerStyleUPtr& style = *it;
    return style.get();
}

IFeatureLayerStyle *LayerStyleCollection::styleByLayerName(const QString &layerName) const
{
    const auto byLayerName = [layerName](const IFeatureLayerStyleUPtr& s) { return s->layerName() == layerName; };
    const auto it = std::find_if(std::begin(m_styles), std::end(m_styles), byLayerName);
    if (it == std::end(m_styles))
    {
        return nullptr;
    }

    const IFeatureLayerStyleUPtr& style = *it;
    return style.get();
}
