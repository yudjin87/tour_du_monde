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

//------------------------------------------------------------------------------
ComponentDefinition::ComponentDefinition()
    : mp_component(nullptr)
    , m_componentName("Undefined_ProxyComponent")
    , m_description("")
    , m_productName("")
    , m_componentLocation("")
    , m_definitionLocation("")
    , m_parents()
    , m_isBuiltIn(false)
{
}

//------------------------------------------------------------------------------
ComponentDefinition::ComponentDefinition(const QString &componentName, bool isBuiltIn)
    : mp_component(nullptr)
    , m_componentName(componentName)
    , m_description("")
    , m_productName("")
    , m_componentLocation("")
    , m_definitionLocation("")
    , m_parents()
    , m_isBuiltIn(isBuiltIn)
{
}

//------------------------------------------------------------------------------
ComponentDefinition::ComponentDefinition(const ComponentDefinition &other)
    : mp_component(other.mp_component)
    , m_componentName(other.m_componentName)
    , m_description(other.m_description)
    , m_productName(other.m_productName)
    , m_componentLocation(other.m_componentLocation)
    , m_definitionLocation(other.m_definitionLocation)
    , m_parents(other.m_parents)
    , m_isBuiltIn(other.m_isBuiltIn)
{
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
ComponentDefinition &ComponentDefinition::operator =(const ComponentDefinition &other)
{
    if (this == &other)
        return *this;

    mp_component = other.mp_component;
    m_componentName = other.m_componentName;
    m_description = other.m_description;
    m_productName = other.m_productName;
    m_componentLocation = other.m_componentLocation;
    m_definitionLocation = other.m_definitionLocation;
    m_parents = other.m_parents;
    m_isBuiltIn = other.m_isBuiltIn;

    return *this;
}

//------------------------------------------------------------------------------
void ComponentDefinition::addParent(const QString &parent)
{
    m_parents.append(parent);
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
bool ComponentDefinition::isBuiltIn() const
{
    return m_isBuiltIn;
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
void ComponentDefinition::setComponent(IComponent *component)
{
    mp_component = component;
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
