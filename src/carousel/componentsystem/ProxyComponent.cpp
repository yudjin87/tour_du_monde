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

#include "componentsystem/ProxyComponent.h"
#include "componentsystem/ComponentDefinition.h"
#include "componentsystem/ComponentLoader.h"

#include "logging/LoggerFacade.h"

#include <QtCore/QFileInfo>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ProxyComponent");
}

ProxyComponent::ProxyComponent(ComponentDefinition *definition, QObject *parent)
    : BaseComponent(definition, parent)
    , m_loader(new ComponentLoader())
    , m_component(nullptr)
    , m_initialized(false)
{
    setState(IComponent::Invalid);
}

ProxyComponent::ProxyComponent(ComponentDefinition *definition, IComponentLoader *loader, QObject *parent)
    : BaseComponent(definition, parent)
    , m_loader(loader)
    , m_component(nullptr)
    , m_initialized(false)
{
    setState(IComponent::Invalid);
}

void *ProxyComponent::getExtension(const QString &byTypeId) const
{
    if (m_component == nullptr) {
        Log.w("Cannot get extension, because component still has not been loaded.");
        return nullptr;
    }

    return m_component->getExtension(byTypeId);
}

ProxyComponent::~ProxyComponent()
{
    delete m_loader;
    m_loader = nullptr;
}

IComponent::Availability ProxyComponent::availability() const
{
    return (m_component == nullptr)
            ? BaseComponent::availability()
            : m_component->availability();
}

IComponent::State ProxyComponent::state() const
{
    return (m_component == nullptr)
            ? BaseComponent::state()
            : m_component->state();
}

bool ProxyComponent::initialize(QString *error)
{
    if (m_initialized)
        return true;

    if (m_loader == nullptr) {
        Log.w("Cannot initialize with null loader.");
        return false;
    }

    if (definition()->componentName().trimmed().isEmpty()) {
        if (error != nullptr)
            *error = "Cannot initialize with empty component name.";

        Log.w("Cannot initialize with empty component name.");
        return false;
    }

    setObjectName(definition()->componentName());

    const QString &libraryPath = definition()->componentLocation();

    // Library file should exist and should be readable
    QFileInfo checkFile(libraryPath);
    if (!checkFile.isReadable()) {
        QString em = QString("Cannot initialize because component library file \"%1\" does not exist or it is not readable.").arg(libraryPath);
        Log.w(em);
        if (error != nullptr)
            *error = em;

        return false;
    }

    loadAvailability();

    m_loader->setFileName(libraryPath);
    m_initialized = true;

    return true;
}

void ProxyComponent::setAvailability(IComponent::Availability newMode)
{
    BaseComponent::setAvailability(newMode);
    if (m_component != nullptr)
        m_component->setAvailability(newMode);
}

void ProxyComponent::setState(IComponent::State newState)
{
    BaseComponent::setState(newState);
    if (m_component != nullptr)
        m_component->setState(newState);
}

IComponent *ProxyComponent::loadedComponent() const
{
    return m_component;
}

void ProxyComponent::onShutdown(IServiceLocator *serviceLocator)
{
    m_component->shutdown(serviceLocator);
    bool result = m_loader->deleteInstance();
    Q_UNUSED(result)
    Q_ASSERT(result);

    m_component = nullptr;
}

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
        setError(m_loader->errorString());
        return false;
    }

    m_component = m_loader->instance();

    if (m_component == nullptr) {
        Log.w("Cannot start up null instance.");
        setError(m_loader->errorString());
        return false;
    }

    m_component->setState(BaseComponent::state());
    m_component->setAvailability(BaseComponent::availability());

    Log.d("Start up loaded component.");
    return m_component->startup(serviceLocator);
}

