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

#include "ComponentDefinition.h"
#include "IComponent.h"

#include <QtCore/QSettings>

//------------------------------------------------------------------------------
ComponentDefinition::ComponentDefinition()
    : mp_component(nullptr)
    , m_availability(ComponentDefinition::Enabled)
    , m_componentName("Undefined_ProxyComponent")
    , m_description("")
    , m_productName("")
    , m_definitionLocation("")
    , m_componentLocation("")
    , m_parents()
{
}

//------------------------------------------------------------------------------
ComponentDefinition::ComponentDefinition(const QString &componentName)
    : mp_component(nullptr)
    , m_availability(ComponentDefinition::Enabled)
    , m_componentName(componentName)
    , m_description("")
    , m_productName("")
    , m_definitionLocation("")
    , m_componentLocation("")
    , m_parents()
{    
    loadAvailability();
}

//------------------------------------------------------------------------------
ComponentDefinition::~ComponentDefinition()
{
    mp_component = nullptr;
    m_parents.clear();
    m_description = "";
    m_productName = "";
    m_componentLocation = "";
    m_definitionLocation = "";
}

//------------------------------------------------------------------------------
void ComponentDefinition::addParent(const QString &parent)
{
    m_parents.append(parent);
}

//------------------------------------------------------------------------------
ComponentDefinition::Availability ComponentDefinition::availability() const
{
    return m_availability;
}

//------------------------------------------------------------------------------
IComponent *ComponentDefinition::component() const
{
    return mp_component;
}

//------------------------------------------------------------------------------
const QString &ComponentDefinition::componentLocation() const
{
    return m_componentLocation;
}

//------------------------------------------------------------------------------
const QString &ComponentDefinition::componentName() const
{
    return m_componentName;
}

//------------------------------------------------------------------------------
const QString &ComponentDefinition::definitionLocation() const
{
    return m_definitionLocation;
}

//------------------------------------------------------------------------------
const QString &ComponentDefinition::description() const
{
    return m_description;
}

//------------------------------------------------------------------------------
const QStringList &ComponentDefinition::parents() const
{
    return m_parents;
}

//------------------------------------------------------------------------------
const QString &ComponentDefinition::productName() const
{
    return m_productName;
}

//------------------------------------------------------------------------------
void ComponentDefinition::setAvailability(ComponentDefinition::Availability i_newMode)
{
    m_availability = i_newMode;
    onAvailabilityChanged(i_newMode);
}

//------------------------------------------------------------------------------
void ComponentDefinition::setComponent(IComponent *component)
{
    mp_component = component;
    QObject::setParent(component);
}

//------------------------------------------------------------------------------
void ComponentDefinition::setComponentName(const QString &name)
{
    m_componentName = name;
}

//------------------------------------------------------------------------------
void ComponentDefinition::setDescription(const QString &description)
{
    m_description = description;
}

//------------------------------------------------------------------------------
void ComponentDefinition::setProductName(const QString &productName)
{
    m_productName = productName;
}

//------------------------------------------------------------------------------
void ComponentDefinition::setComponentLocation(const QString &componentLocation)
{
    m_componentLocation = componentLocation;
}

//------------------------------------------------------------------------------
void ComponentDefinition::setDefinitionLocation(const QString &definitionLocation)
{
    m_definitionLocation = definitionLocation;
}

//------------------------------------------------------------------------------
void ComponentDefinition::onAvailabilityChanged(ComponentDefinition::Availability i_newMode)
{
    emit availabilityChanged(i_newMode);
}

//------------------------------------------------------------------------------
void ComponentDefinition::loadAvailability()
{
    QSettings settings;
    QVariant value = settings.value(QString("components_availability/%1").arg(componentName()));
    if (value.isValid())
        setAvailability(static_cast<ComponentDefinition::Availability>(value.toInt()));
}

//------------------------------------------------------------------------------
