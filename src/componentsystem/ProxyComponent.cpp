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

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

//------------------------------------------------------------------------------
ProxyComponent::ProxyComponent(ComponentDefinition *definition, QObject *parent)
    : BaseComponent(definition, parent)
    , mp_loader(new ComponentLoader())
    , mp_component(nullptr)
    , m_initialized(false)
    , m_definitionLocation("")
{
}

//------------------------------------------------------------------------------
ProxyComponent::ProxyComponent(ComponentDefinition *definition, IComponentLoader *loader, QObject *parent)
    : BaseComponent(definition, parent)
    , mp_loader(loader)
    , mp_component(nullptr)
    , m_initialized(false)
    , m_definitionLocation("")
{
}

//------------------------------------------------------------------------------
void *ProxyComponent::getExtension(const QString &i_byTypeId) const
{
    if (mp_component == nullptr)
        return nullptr;

    return mp_component->getExtension(i_byTypeId);
}

//------------------------------------------------------------------------------
ProxyComponent::~ProxyComponent()
{
    delete mp_loader;
    mp_loader = nullptr;
}

//------------------------------------------------------------------------------
bool ProxyComponent::initialize()
{
    if (m_initialized)
        return true;

    if (mp_loader == nullptr)
        return false;

    if (definition()->componentName().trimmed().isEmpty())
        return false;

    setObjectName(definition()->componentName());

    // Get the absolute library file name, using definition's location
    // as a pivot for relative component path
    QFileInfo definitionFileName(m_definitionLocation);
    QDir definitionDirPath(definitionFileName.absoluteDir());
    QString libraryAbsolutePath = definitionDirPath.absoluteFilePath(definition()->componentLocation());
    QString cleanPath = QDir::cleanPath(libraryAbsolutePath);

    // Library file should exist and should be readable
    QFileInfo checkFile(cleanPath);
    if (!checkFile.isReadable())
        return false;

    definition()->loadAvailability();

    mp_loader->setFileName(cleanPath);
    m_initialized = true;

    return true;
}

//------------------------------------------------------------------------------
IComponent *ProxyComponent::loadedComponent() const
{
    return mp_component;
}

//------------------------------------------------------------------------------
void ProxyComponent::setDefinitionLocation(const QString &definitionLocation)
{
    m_definitionLocation = definitionLocation;
}

//------------------------------------------------------------------------------
void ProxyComponent::_onShutdown()
{
    mp_component->shutdown();
    bool result = mp_loader->deleteInstance();
    Q_ASSERT(result);

    mp_component = nullptr;
}

//------------------------------------------------------------------------------
bool ProxyComponent::_onStartup(QObject *ip_initData)
{
    if (!m_initialized)
        return false;

    if (mp_loader == nullptr)
        return false;

    if (!mp_loader->load())
        return false;

    mp_component = mp_loader->instance();

    if (mp_component == nullptr)
        return false;

    return mp_component->startup(ip_initData);
}

//------------------------------------------------------------------------------
