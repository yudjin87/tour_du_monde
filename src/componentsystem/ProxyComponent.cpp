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

#include <logging/LoggerFacade.h>

#include <QtCore/QFileInfo>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ProxyComponent");
}

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
    if (m_component == nullptr) {
        Log.w("Cannot get extension, because component still has not been loaded.");
        return nullptr;
    }

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

    if (m_loader == nullptr) {
        Log.w("Cannot initialize with null loader.");
        return false;
    }

    if (definition()->componentName().trimmed().isEmpty()) {
        Log.w("Cannot initialize with empty component name.");
        return false;
    }

    setObjectName(definition()->componentName());

    const QString &libraryPath = definition()->componentLocation();

    // Library file should exist and should be readable
    QFileInfo checkFile(libraryPath);
    if (!checkFile.isReadable()) {
        Log.w(QString("Cannot initialize because component lirary file \"%1\" does not exist or it is not readable.")
              .arg(libraryPath));
        return false;
    }

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
void ProxyComponent::onShutdown()
{
    m_component->shutdown();
    bool result = m_loader->deleteInstance();
    Q_UNUSED(result)
    Q_ASSERT(result);

    m_component = nullptr;
}

//------------------------------------------------------------------------------
bool ProxyComponent::onStartup(IServiceLocator *serviceLocator)
{
    if (!m_initialized) {
        Log.w("Cannot start up without initialization.");
        return false;
    }

    if (m_loader == nullptr) {
        Log.w("Cannot start up with null loader.");
        return false;
    }

    if (!m_loader->load()) {
        Log.w("Cannot start up because loading failed.");
        return false;
    }

    m_component = m_loader->instance();

    if (m_component == nullptr)
        return false;

    Log.d("Start up loaded component.");
    return m_component->startup(serviceLocator);
}

//------------------------------------------------------------------------------
