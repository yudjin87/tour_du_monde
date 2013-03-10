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
//------------------------------------------------------------------------------
BaseComponent::BaseComponent(const char *ip_name, QObject *parent)
    : mp_definition(nullptr)
    , m_isStarted(false)
    , m_name(ip_name)
    , mp_typeObjectsMap(new TypeObjectsMap<void *>())
{
    mp_definition = new ComponentDefinition(this);
    setParent(parent);
    setObjectName(m_name);
}

//------------------------------------------------------------------------------
BaseComponent::BaseComponent(const QString &i_name, QObject *parent)
    : mp_definition(nullptr)
    , m_isStarted(false)
    , m_name(i_name)
    , mp_typeObjectsMap(new TypeObjectsMap<void *>())
{
    mp_definition = new ComponentDefinition(this);
    setParent(parent);
    setObjectName(m_name);
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
IComponentDefinition *BaseComponent::definition() const
{
    return mp_definition;
}

//------------------------------------------------------------------------------
const QString &BaseComponent::name() const
{
    return m_name;
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
void BaseComponent::registerExtensionInstance(void *ip_instance, const QString &i_forTypeId)
{
    mp_typeObjectsMap->registerInstance(ip_instance, i_forTypeId);
}

//------------------------------------------------------------------------------
