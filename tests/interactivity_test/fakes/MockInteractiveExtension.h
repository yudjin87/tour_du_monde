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

#ifndef MOCKINTERACTIVECOMPONENT_H
#define MOCKINTERACTIVECOMPONENT_H

#include <componentsystem/BaseComponent.h>
#include <interactivity/IInteractiveExtension.h>

class ICatalogs;
class IInteractiveExtension;
class FakeInteractiveExtension;

//------------------------------------------------------------------------------
class MockInteractiveExtension : public BaseComponent
{
public:
    MockInteractiveExtension();
    MockInteractiveExtension(const QString &i_name);
    ~MockInteractiveExtension();

public:
    FakeInteractiveExtension *mp_interactiveExtension;
};

//------------------------------------------------------------------------------
typedef void(*configuredFunc)(ICatalogs &);
//------------------------------------------------------------------------------
class FakeInteractiveExtension : public IInteractiveExtension
{
public:
    FakeInteractiveExtension()
        : m_configureCalled(false)
        , mp_func(nullptr)
    {
    }

    void configureGui(ICatalogs &i_inCatalogs, AbstractApplication &)
    {
        m_configureCalled = true;

        if (mp_func != nullptr)
            mp_func(i_inCatalogs);
    }

    void setCunfigureFunc(configuredFunc func)
    {
        mp_func = func;
    }

public:
    bool m_configureCalled;
    configuredFunc mp_func;
};

#endif // MOCKINTERACTIVECOMPONENT_H
