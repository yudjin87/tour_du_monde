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

#include "MockComponentConfigurationDelegate.h"

//------------------------------------------------------------------------------
MockComponentConfigurationDelegate::MockComponentConfigurationDelegate()
    : m_configureCalled(false)
    , m_deconfigureCalled(false)
    , m_configureCalls(0)
    , m_deconfigureCalls(0)
    , m_wasDestructorCalled(nullptr)
{
}

//------------------------------------------------------------------------------
MockComponentConfigurationDelegate::~MockComponentConfigurationDelegate()
{
    if (m_wasDestructorCalled != nullptr)
        *m_wasDestructorCalled = true;

    m_configureCalls = -1;
    m_deconfigureCalls = -1;
}

//------------------------------------------------------------------------------
void MockComponentConfigurationDelegate::configure(IComponent * /*component*/, ICatalogs &/*catalogs*/, AbstractApplication &/*i_application*/)
{
    m_configureCalled = true;
    ++m_configureCalls;
}

//------------------------------------------------------------------------------
void MockComponentConfigurationDelegate::deconfigure(IComponent * /*component*/, ICatalogs &/*catalogs*/)
{
    m_deconfigureCalled = true;
    ++m_deconfigureCalls;
}

//------------------------------------------------------------------------------
void MockComponentConfigurationDelegate::setDeleteFlag(bool &i_wasDestructorCalled)
{
    m_wasDestructorCalled = &i_wasDestructorCalled;
}

//------------------------------------------------------------------------------
const ConfigurationChanges *MockComponentConfigurationDelegate::changesByComponent(IComponent * /*component*/) const
{
    return nullptr;
}

//------------------------------------------------------------------------------
