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

#include "prototypes/ComponentDefinitionPrototype.h"

#include <QtScript/QScriptEngine>

ComponentDefinitionPrototype::ComponentDefinitionPrototype(QObject *parent)
    : QObject(parent)
{

}

IComponent *ComponentDefinitionPrototype::component() const
{
    return thisDef()->component();
}

const Version *ComponentDefinitionPrototype::version() const
{
    return thisDef()->version();
}

bool ComponentDefinitionPrototype::isBuiltIn() const
{
    return thisDef()->isBuiltIn();
}

const QString &ComponentDefinitionPrototype::componentLocation() const
{
    return thisDef()->componentLocation();
}

const QString &ComponentDefinitionPrototype::shortComponentName() const
{
    return thisDef()->shortComponentName();
}

const QString &ComponentDefinitionPrototype::componentName() const
{
    return thisDef()->componentName();
}

const QString &ComponentDefinitionPrototype::definitionLocation() const
{
    return thisDef()->definitionLocation();
}

const QString &ComponentDefinitionPrototype::description() const
{
    return thisDef()->description();
}

const QString &ComponentDefinitionPrototype::productName() const
{
    return thisDef()->productName();
}

const QString &ComponentDefinitionPrototype::provider() const
{
    return thisDef()->provider();
}

const QString &ComponentDefinitionPrototype::error() const
{
    return thisDef()->error();
}

const ParentDefinitions &ComponentDefinitionPrototype::parents() const
{
    return thisDef()->parents();
}

bool ComponentDefinitionPrototype::isCompatible(const IComponent *parent) const
{
    return thisDef()->isCompatible(parent);
}

bool ComponentDefinitionPrototype::isCompatible(const QString &name, const Version *version) const
{
    return thisDef()->isCompatible(name, version);
}

bool ComponentDefinitionPrototype::isCompatible(const ParentDefinitions &parents) const
{
    return thisDef()->isCompatible(parents);
}

QString ComponentDefinitionPrototype::toString() const
{
    static QString pattern = "ComponentDefinition(\"%1\")";
    return pattern.arg(shortComponentName());
}

ComponentDefinition *ComponentDefinitionPrototype::thisDef()
{
    ComponentDefinition *def = qscriptvalue_cast<ComponentDefinition *>(thisObject());
    if (def == nullptr)
        return nullptr; // TODO: throw script error: TypeError}

    return def;
}

const ComponentDefinition *ComponentDefinitionPrototype::thisDef() const
{
    const ComponentDefinition *cdef = qscriptvalue_cast<const ComponentDefinition *>(thisObject());
    if (cdef == nullptr)
        return nullptr; // TODO: throw script error: TypeError}

    return cdef;
}

