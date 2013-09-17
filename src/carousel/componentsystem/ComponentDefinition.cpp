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
#include "Version.h"
#include "ParentDefinition.h"
#include "ParentDefinitions.h"

//------------------------------------------------------------------------------
static const char *DEFAULT_PROVIDER = "Unknown";

//------------------------------------------------------------------------------
ComponentDefinition::ComponentDefinition()
    : m_component(nullptr)
    , m_componentName("Undefined_ProxyComponent")
    , m_componentShortName("")
    , m_description("")
    , m_productName("")
    , m_provider(ComponentDefinition::defaultProvider())
    , m_componentLocation("")
    , m_definitionLocation("")
    , m_arguments()
    , m_version(new Version())
    , m_parents()
    , m_isBuiltIn(false)
{
}

//------------------------------------------------------------------------------
ComponentDefinition::ComponentDefinition(const QString &componentName, bool isBuiltIn)
    : m_component(nullptr)
    , m_componentName(componentName)
    , m_componentShortName("")
    , m_description("")
    , m_productName("")
    , m_provider(ComponentDefinition::defaultProvider())
    , m_componentLocation("")
    , m_definitionLocation("")
    , m_arguments()
    , m_version(new Version())
    , m_parents()
    , m_isBuiltIn(isBuiltIn)
{
}

//------------------------------------------------------------------------------
ComponentDefinition::~ComponentDefinition()
{
    delete m_version;
    m_version = nullptr;

    m_component = nullptr;

    m_description = "";
    m_productName = "";
    m_componentShortName = "";
    m_componentLocation = "";
    m_definitionLocation = "";
}

//------------------------------------------------------------------------------
QString ComponentDefinition::defaultProvider()
{
    return DEFAULT_PROVIDER;
}

//------------------------------------------------------------------------------
void ComponentDefinition::addParent(ParentDefinition *parent)
{
    m_parents.append(parent);
}

//------------------------------------------------------------------------------
IComponent *ComponentDefinition::component() const
{
    return m_component;
}

//------------------------------------------------------------------------------
const QString &ComponentDefinition::componentLocation() const
{
    return m_componentLocation;
}

//------------------------------------------------------------------------------
const QString &ComponentDefinition::shortComponentName() const
{
    return m_componentShortName;
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
bool ComponentDefinition::isCompatible(const IComponent *parent) const
{
    return isCompatible(parent->name(), parent->definition()->version());
}

//------------------------------------------------------------------------------
bool ComponentDefinition::isCompatible(const QString &name, const Version *version) const
{
    // Always compatible with unknown parents
    if (!m_parents.contains(name))
        return true;

    const Version *myParentVersion = m_parents[name];
    return myParentVersion->isEqual(version);
}

//------------------------------------------------------------------------------
bool ComponentDefinition::isCompatible(const ParentDefinitions &parents) const
{
    for (const ParentDefinition *parent : parents) {
        if (!isCompatible(parent->name(), parent->version()))
            return false;
    }

    return true;
}

//------------------------------------------------------------------------------
const ParentDefinitions &ComponentDefinition::parents() const
{
    return m_parents;
}

//------------------------------------------------------------------------------
const QString &ComponentDefinition::productName() const
{
    return m_productName;
}

//------------------------------------------------------------------------------
const QString &ComponentDefinition::provider() const
{
    return m_provider;
}

//------------------------------------------------------------------------------
const QStringList &ComponentDefinition::arguments() const
{
    return m_arguments;
}

//------------------------------------------------------------------------------
const Version *ComponentDefinition::version() const
{
    return m_version;
}

//------------------------------------------------------------------------------
void ComponentDefinition::setComponent(IComponent *component)
{
    m_component = component;
}

//------------------------------------------------------------------------------
void ComponentDefinition::setComponentName(const QString &name)
{
    m_componentName = name;
}

//------------------------------------------------------------------------------
void ComponentDefinition::setShortComponentName(const QString &name)
{
    m_componentShortName = name;
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
void ComponentDefinition::setProvider(const QString &provider)
{
    m_provider = provider;
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
void ComponentDefinition::setArguments(const QStringList &arguments)
{
    m_arguments = arguments;
}

//------------------------------------------------------------------------------
void ComponentDefinition::setVersion(int major_version, int minor_version, int build_version, int revision_version)
{
    m_version->setVersion(major_version, minor_version, build_version, revision_version);
}

//------------------------------------------------------------------------------
void ComponentDefinition::setVersion(Version *version)
{
    if (version == nullptr)
        return;

    delete m_version;
    m_version = version;
}

//------------------------------------------------------------------------------
