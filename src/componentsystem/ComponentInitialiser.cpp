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

#include "ComponentInitialiser.h"

#include "IComponent.h"
#include "ComponentDefinition.h"

#include <logging/ILogger.h>

//------------------------------------------------------------------------------
ComponentInitialiser::ComponentInitialiser(ILogger &log, QObject *parent)
    : m_log(log)
{
    QObject::setParent(parent);
}

//------------------------------------------------------------------------------
ComponentInitialiser::~ComponentInitialiser()
{
}

//------------------------------------------------------------------------------
void ComponentInitialiser::shutdownComponent(IComponent *component)
{
    component->shutdown();
}

//------------------------------------------------------------------------------
bool ComponentInitialiser::startupComponent(IComponent *component, QObject *ip_initializationData)
{
    m_log.log("Ensure before startup that component is availabled", ILogger::Info);

    ComponentDefinition *definition = component->definition();
    if (definition->availability() != ComponentDefinition::Enabled) {
        m_log.log(QString("Can not startup unavailable component: '%1'").arg(component->name()), ILogger::Info);
        return false;
    }

    return component->startup(ip_initializationData);
}

//------------------------------------------------------------------------------
