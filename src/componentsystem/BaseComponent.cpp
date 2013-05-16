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

#include "BaseComponent.h"
#include "ComponentDefinition.h"

#include <logging/LoggerFacade.h>
#include <utils/TypeObjectsMap.h>

#include <QtCore/QSettings>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("BaseComponent");
}

//------------------------------------------------------------------------------
BaseComponent::BaseComponent(const QString &name, QObject *parent)
    : m_definition(new ComponentDefinition(name, true))
    , m_isStarted(false)
    , m_availability(IComponent::Enabled)
    , m_typeObjectsMap(new TypeObjectsMap<void *>())
{
    setParent(parent);
    setObjectName(m_definition->componentName());
    loadAvailability();
    m_definition->setComponent(this);
}

//------------------------------------------------------------------------------
BaseComponent::BaseComponent(ComponentDefinition *definition, QObject *parent)
    : m_definition(definition)
    , m_isStarted(false)
    , m_availability(IComponent::Enabled)
    , m_typeObjectsMap(new TypeObjectsMap<void *>())
{
    setParent(parent);
    setObjectName(m_definition->componentName());
    loadAvailability();
    m_definition->setComponent(this);
}

//------------------------------------------------------------------------------
void *BaseComponent::getExtension(const QString &byTypeId) const
{
    return m_typeObjectsMap->getInstance(byTypeId);
}

//------------------------------------------------------------------------------
BaseComponent::~BaseComponent()
{
    saveAvailability();

    delete m_typeObjectsMap;
    m_typeObjectsMap = nullptr;

    delete m_definition;
    m_definition = nullptr;
}

//------------------------------------------------------------------------------
IComponent::Availability BaseComponent::availability() const
{
    return m_availability;
}

//------------------------------------------------------------------------------
const ComponentDefinition *BaseComponent::definition() const
{
    return m_definition;
}

//------------------------------------------------------------------------------
const QString &BaseComponent::name() const
{
    return m_definition->componentName();
}

//------------------------------------------------------------------------------
bool BaseComponent::started() const
{
    return m_isStarted;
}

//------------------------------------------------------------------------------
void BaseComponent::shutdown()
{
    if (!m_isStarted) {
        Log.w(QString("Component \"%1\" is being shut down, but it was not started up.").arg(name()));
        return;
    }

    m_isStarted = false;
    onShutdown();
}

//------------------------------------------------------------------------------
bool BaseComponent::startup(QObject *initData)
{
    if (m_isStarted) {
        Log.w(QString("Component \"%1\" is being started up, but it was not shut down.").arg(name()));
        return true;
    }

    m_isStarted = onStartup(initData);
    return m_isStarted;
}

//------------------------------------------------------------------------------
void BaseComponent::onShutdown()
{
    // nothing to do in the base implementation
}

//------------------------------------------------------------------------------
bool BaseComponent::onStartup(QObject *)
{
    // nothing to do in the base implementation
    return true;
}

//------------------------------------------------------------------------------
void BaseComponent::addParent(const QString &parent)
{
    m_definition->addParent(parent);
}

//------------------------------------------------------------------------------
void BaseComponent::loadAvailability()
{
    QSettings settings;
    QVariant value = settings.value(QString("components_availability/%1").arg(name()));
    if (value.isValid())
        setAvailability(static_cast<Availability>(value.toInt()));
}

//------------------------------------------------------------------------------
void BaseComponent::saveAvailability()
{
    QSettings settings;
    settings.setValue(QString("components_availability/%1").arg(name()), static_cast<int>(availability()));
    settings.sync();
}

//------------------------------------------------------------------------------
void BaseComponent::setAvailability(IComponent::Availability newMode)
{
    if (m_availability == newMode)
        return;

    m_availability = newMode;
    onAvailabilityChanged(newMode);
}

//------------------------------------------------------------------------------
void BaseComponent::setDescription(const QString &description)
{
    m_definition->setDescription(description);
}

//------------------------------------------------------------------------------
void BaseComponent::setProductName(const QString &productName)
{
    m_definition->setProductName(productName);
}

//------------------------------------------------------------------------------
void BaseComponent::setProvider(const QString &provider)
{
    m_definition->setProvider(provider);
}

//------------------------------------------------------------------------------
void BaseComponent::onAvailabilityChanged(Availability newMode)
{
    emit availabilityChanged(newMode);
}

//------------------------------------------------------------------------------
void BaseComponent::registerExtensionInstance(void *instance, const QString &forTypeId)
{
    m_typeObjectsMap->registerInstance(instance, forTypeId);
}

//------------------------------------------------------------------------------
