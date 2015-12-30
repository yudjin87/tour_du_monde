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

#include "carto/layers/LayerCollection.h"

LayerCollection::LayerCollection()
    : ILayerCollection()
    , m_layers()
{
}

ILayerCollection::ILayerVector::const_iterator LayerCollection::begin() const
{
    return m_layers.begin();
}

ILayerCollection::ILayerVector::const_iterator LayerCollection::end() const
{
    return m_layers.end();
}

size_t LayerCollection::layerCount() const
{
    return m_layers.size();
}

void LayerCollection::addLayer(AbstractLayerUPtr layer)
{
    m_layers.push_back(std::move(layer));
}

bool LayerCollection::isEmpty() const
{
    return m_layers.empty();
}

