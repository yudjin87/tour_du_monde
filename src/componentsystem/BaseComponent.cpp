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

#include <utils/TypeObjectsMap.h>

#include <QtCore/QSettings>

//------------------------------------------------------------------------------
BaseComponent::BaseComponent(const QString &i_name, QObject *parent)
    : mp_definition(new ComponentDefinition(i_name, true))
    , m_isStarted(false)
    , m_availability(IComponent::Enabled)
    , mp_typeObjectsMap(new TypeObjectsMap<void *>())
{
    setParent(parent);
    setObjectName(mp_definition->componentName());
    loadAvailability();
    mp_definition->setComponent(this);
}

//------------------------------------------------------------------------------
BaseComponent::BaseComponent(ComponentDefinition *definition, QObject *parent)
    : mp_definition(definition)
    , m_isStarted(false)
    , m_availability(IComponent::Enabled)
    , mp_typeObjectsMap(new TypeObjectsMap<void *>())
{
    setParent(parent);
    setObjectName(mp_definition->componentName());
    loadAvailability();
    mp_definition->setComponent(this);
}

//------------------------------------------------------------------------------
void *BaseComponent::getExtension(const QString &i_byTypeId) const
{
    return mp_typeObjectsMap->getInstance(i_byTypeId);
}

//------------------------------------------------------------------------------
BaseComponent::~BaseComponent()
{
    delete mp_typeObjectsMap;
    mp_typeObjectsMap = nullptr;

    delete mp_definition;
    mp_definition = nullptr;
}

//------------------------------------------------------------------------------
IComponent::Availability BaseComponent::availability() const
{
    return m_availability;
}

//------------------------------------------------------------------------------
const ComponentDefinition *BaseComponent::definition() const
{
    return mp_definition;
}

//------------------------------------------------------------------------------
const QString &BaseComponent::name() const
{
    return mp_definition->componentName();
}

//------------------------------------------------------------------------------
bool BaseComponent::started() const
{
    return m_isStarted;
}

//------------------------------------------------------------------------------
void BaseComponent::shutdown()
{
    if (!m_isStarted)
        return;

    m_isStarted = false;
    _onShutdown();
}

//------------------------------------------------------------------------------
bool BaseComponent::startup(QObject *ip_initData)
{
    if (m_isStarted)
        return true;

    m_isStarted = _onStartup(ip_initData);
    return m_isStarted;
}

//------------------------------------------------------------------------------
void BaseComponent::_onShutdown()
{
    // nothing to do in the base implementation
}

//------------------------------------------------------------------------------
bool BaseComponent::_onStartup(QObject *)
{
    // nothing to do in the base implementation
    return true;
}

//------------------------------------------------------------------------------
void BaseComponent::addParent(const QString &parent)
{
    mp_definition->addParent(parent);
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
    mp_definition->setDescription(description);
}

//------------------------------------------------------------------------------
void BaseComponent::setProductName(const QString &productName)
{
    mp_definition->setProductName(productName);
}

//------------------------------------------------------------------------------
void BaseComponent::onAvailabilityChanged(Availability i_newMode)
{
    emit availabilityChanged(i_newMode);
}

//------------------------------------------------------------------------------
void BaseComponent::registerExtensionInstance(void *ip_instance, const QString &i_forTypeId)
{
    mp_typeObjectsMap->registerInstance(ip_instance, i_forTypeId);
}

//------------------------------------------------------------------------------
