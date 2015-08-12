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

#include "styles/FeatureLayerStyle.h"

FeatureLayerStyle::FeatureLayerStyle()
    : IFeatureLayerStyle()
    , m_layerName()
    , m_name()
    , m_renderer()
{
}

FeatureLayerStyle::FeatureLayerStyle(const FeatureLayerStyle &other)
    : IFeatureLayerStyle()
    , m_layerName(other.m_layerName)
    , m_name(other.m_name)
    , m_renderer(other.m_renderer == nullptr ? nullptr : other.m_renderer->clone())
{
}

FeatureLayerStyle &FeatureLayerStyle::operator=(const FeatureLayerStyle &other)
{
    if (this == &other)
    {
        return *this;
    }

    m_layerName = other.m_layerName;
    m_name = other.m_name;
    m_renderer.reset(other.m_renderer == nullptr ? nullptr : other.m_renderer->clone());

    return *this;
}

IFeatureLayerStyle *FeatureLayerStyle::clone() const
{
    return new FeatureLayerStyle(*this);
}

QString FeatureLayerStyle::layerName() const
{
    return m_layerName;
}

void FeatureLayerStyle::setLayerName(const QString &layerName)
{
    if (m_layerName == layerName)
    {
        return;
    }

    m_layerName = layerName;
    emit layerNameChanged(layerName);
}

const IFeatureRenderer *FeatureLayerStyle::renderer() const
{
    return m_renderer.get();
}

void FeatureLayerStyle::setRenderer(const IFeatureRenderer *renderer)
{
    m_renderer.reset(renderer->clone());
    emit rendererChanged(m_renderer.get());
}

QString FeatureLayerStyle::name() const
{
    return m_name;
}

void FeatureLayerStyle::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}
