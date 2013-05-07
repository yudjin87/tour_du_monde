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

#include "ProxyComponent.h"

#include "ComponentDefinition.h"
#include "ComponentLoader.h"

#include <QtCore/QFileInfo>

//------------------------------------------------------------------------------
ProxyComponent::ProxyComponent(ComponentDefinition *definition, QObject *parent)
    : BaseComponent(definition, parent)
    , m_loader(new ComponentLoader())
    , m_component(nullptr)
    , m_initialized(false)
{
}

//------------------------------------------------------------------------------
ProxyComponent::ProxyComponent(ComponentDefinition *definition, IComponentLoader *loader, QObject *parent)
    : BaseComponent(definition, parent)
    , m_loader(loader)
    , m_component(nullptr)
    , m_initialized(false)
{
}

//------------------------------------------------------------------------------
void *ProxyComponent::getExtension(const QString &byTypeId) const
{
    if (m_component == nullptr)
        return nullptr;

    return m_component->getExtension(byTypeId);
}

//------------------------------------------------------------------------------
ProxyComponent::~ProxyComponent()
{
    delete m_loader;
    m_loader = nullptr;
}

//------------------------------------------------------------------------------
bool ProxyComponent::initialize()
{
    if (m_initialized)
        return true;

    if (m_loader == nullptr)
        return false;

    if (definition()->componentName().trimmed().isEmpty())
        return false;

    setObjectName(definition()->componentName());

    const QString &libraryPath = definition()->componentLocation();

    // Library file should exist and should be readable
    QFileInfo checkFile(libraryPath);
    if (!checkFile.isReadable())
        return false;

    loadAvailability();

    m_loader->setFileName(libraryPath);
    m_initialized = true;

    return true;
}

//------------------------------------------------------------------------------
IComponent *ProxyComponent::loadedComponent() const
{
    return m_component;
}

//------------------------------------------------------------------------------
void ProxyComponent::_onShutdown()
{
    m_component->shutdown();
    bool result = m_loader->deleteInstance();
    Q_UNUSED(result)
    Q_ASSERT(result);

    m_component = nullptr;
}

//------------------------------------------------------------------------------
bool ProxyComponent::_onStartup(QObject *initData)
{
    if (!m_initialized)
        return false;

    if (m_loader == nullptr)
        return false;

    if (!m_loader->load())
        return false;

    m_component = m_loader->instance();

    if (m_component == nullptr)
        return false;

    return m_component->startup(initData);
}

//------------------------------------------------------------------------------
