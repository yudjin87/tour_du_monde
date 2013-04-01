/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
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

#include "CompositeComponentProvider.h"
#include "ComponentProvider.h"

#include <QtCore/QtAlgorithms>

//------------------------------------------------------------------------------
CompositeComponentProvider::CompositeComponentProvider(QObject *parent /* = nullptr*/)
    : QObject(parent)
    , m_alreadyInit(false)
{
    m_providers.push_back(new ComponentProvider());
}

//------------------------------------------------------------------------------
CompositeComponentProvider::~CompositeComponentProvider()
{
    qDeleteAll(m_providers);
}

//------------------------------------------------------------------------------
bool CompositeComponentProvider::initialize()
{
    if (m_alreadyInit)
        return true;

    m_alreadyInit = true;
    foreach(IComponentProvider *p_provider, m_providers)
        m_alreadyInit &= p_provider->initialize();

    return m_alreadyInit;
}

//------------------------------------------------------------------------------
bool CompositeComponentProvider::isInitialized() const
{
    return m_alreadyInit;
}

//------------------------------------------------------------------------------
QList<IComponent *> CompositeComponentProvider::components() const
{
    QList<IComponent *> components_to_return;

    foreach(IComponentProvider *p_provider, m_providers)
        foreach(IComponent *p_component, p_provider->components())
            components_to_return.push_back(p_component);

    return components_to_return;
}

//------------------------------------------------------------------------------
CompositeComponentProvider &CompositeComponentProvider::addProvider(IComponentProvider *ip_provider)
{
    m_providers.push_back(ip_provider);
    return *this;
}

void CompositeComponentProvider::registerComponent(IComponent *ip_component)
{
    m_providers[0]->registerComponent(ip_component);
}

//------------------------------------------------------------------------------
