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

#include "TestComponentDefinition.h"

//------------------------------------------------------------------------------
TestComponentDefinition::TestComponentDefinition()
    : m_setAvailabilityCalled(false)
    , m_productName("Test mock")
    , m_description("Configured mock for testing")
{
}

//------------------------------------------------------------------------------
const QString &TestComponentDefinition::productName() const
{
    return m_productName;
}

//------------------------------------------------------------------------------
const QString &TestComponentDefinition::description() const
{
    return m_description;
}

//------------------------------------------------------------------------------
IComponentDefinition::Availability TestComponentDefinition::availability() const
{
    return m_availability;
}

//------------------------------------------------------------------------------
void TestComponentDefinition::setAvailability(Availability i_new_mode)
{
    m_setAvailabilityCalled = true;
    m_availability = i_new_mode;

    emit availabilityChanged(m_availability);
}

//------------------------------------------------------------------------------
IComponent *TestComponentDefinition::component() const
{
    return nullptr;
}

const QStringList &TestComponentDefinition::parents() const
{
    return m_dependencies;
}

//------------------------------------------------------------------------------
