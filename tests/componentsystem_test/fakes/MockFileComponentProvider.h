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

#ifndef MOCKFILECOMPONENTPROVIDER_H
#define MOCKFILECOMPONENTPROVIDER_H

#include "FakeDefinitionParser.h"
#include "MockDefaultConstructor.h"

#include <carousel/componentsystem/FileComponentProvider.h>
#include <carousel/componentsystem/ProxyComponent.h>

class MockProxyComponent;

class MockFileComponentProvider : public FileComponentProvider
{
public:
    MockFileComponentProvider(FakeDefinitionParser *parser = nullptr);
    MockFileComponentProvider(const QString &path, FakeDefinitionParser *parser = nullptr);

    ~MockFileComponentProvider();

    IDefinitionParser *createParser();

    IComponent *loadComponent();

    bool initialize();

    ProxyComponent *createProxy(ComponentDefinition *definition);

    DefinitionConstuctor *createDefinitionConstuctor();

public:
    FakeDefinitionParser *parser;
    MockDefaultConstructor *constructor;
    int loadCalled;
    bool initializeCalled;
    bool initializeReturnValue;
    IComponent *loadResult;
};

class MockProxyComponent : public ProxyComponent
{
public:
    MockProxyComponent(QObject *parent = nullptr);
    MockProxyComponent(ComponentDefinition *definition, QObject *parent = nullptr);

    bool initialize();

    static bool initializeReturnValue;
};

#endif // MOCKFILECOMPONENTPROVIDER_H
