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

#include "cartoPersist/FeatureRendererPersistCreator.h"
#include "cartoPersist/SimpleRendererPersist.h"
#include "cartoPersist/CategorizedRendererPersist.h"


FeatureRendererPersistCreator::FeatureRendererPersistCreator()
    : IFeatureRendererVisitor()
    , m_persist()
{
}

IFeatureRendererPersistUPtr FeatureRendererPersistCreator::create(const IFeatureRenderer &forFeatureRenderer)
{
    const_cast<IFeatureRenderer&>(forFeatureRenderer).accept(*this);
    return std::move(m_persist);
}

IFeatureRendererPersistUPtr FeatureRendererPersistCreator::create(const RendererType type)
{
    switch (type)
    {
    case RendererType::Simple:
        return IFeatureRendererPersistUPtr(new SimpleRendererPersist());
    case RendererType::Categorized:
        return IFeatureRendererPersistUPtr(new CategorizedRendererPersist());
    }

    return nullptr;
}

void FeatureRendererPersistCreator::visit(SimpleRenderer &renderer)
{
    m_persist.reset(new SimpleRendererPersist(renderer));
}

void FeatureRendererPersistCreator::visit(CategorizedRenderer &renderer)
{
    m_persist.reset(new CategorizedRendererPersist(renderer));
}



