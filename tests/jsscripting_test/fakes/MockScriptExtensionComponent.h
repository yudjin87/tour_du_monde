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

#ifndef MOCKSCRIPTEXTENSIONCOMPONENT_H
#define MOCKSCRIPTEXTENSIONCOMPONENT_H

#include <carousel/componentsystem/BaseComponent.h>
#include <components/jsscripting/IScriptExtension.h>

class FakeScriptExtension;

//------------------------------------------------------------------------------
class MockNoScriptExtensionComponent : public BaseComponent
{
public:
    MockNoScriptExtensionComponent();
};

//------------------------------------------------------------------------------
class MockScriptExtensionComponent : public BaseComponent
{
public:
    MockScriptExtensionComponent();
    MockScriptExtensionComponent(const QString &name);
    ~MockScriptExtensionComponent();

public:
    FakeScriptExtension *m_extension;
};

//------------------------------------------------------------------------------
class FakeScriptExtension : public IScriptExtension
{
public:
    FakeScriptExtension()
        : m_configureCalled(false)
    {
    }

    void configureEngine(QScriptEngine *)
    {
        m_configureCalled = true;
    }

public:
    bool m_configureCalled;
};


#endif // MOCKSCRIPTEXTENSIONCOMPONENT_H