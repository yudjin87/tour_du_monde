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

#include "MockComponentInitialiser.h"

#include <logging/NullLogger.h>

//------------------------------------------------------------------------------
static NullLogger stubLogger;

//------------------------------------------------------------------------------
MockComponentInitialiser::MockComponentInitialiser()
    : ComponentInitialiser(stubLogger)
    , mp_shutdownComponent(nullptr)
    , mp_startupComponent(nullptr)
    , mp_initializationData(nullptr)
{
}

//------------------------------------------------------------------------------
MockComponentInitialiser::~MockComponentInitialiser()
{
}

//------------------------------------------------------------------------------
void MockComponentInitialiser::shutdownComponent(IComponent * component)
{
    m_shutdownComponents.push_back(component);
    mp_shutdownComponent = component;
}

//------------------------------------------------------------------------------
bool MockComponentInitialiser::startupComponent(IComponent *component, QObject *ip_initializationData)
{
    m_startupComponents.push_back(component);
    mp_startupComponent = component;
    mp_initializationData = ip_initializationData;

    return ComponentInitialiser::startupComponent(component, ip_initializationData);
}

//------------------------------------------------------------------------------
