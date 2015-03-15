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

#include "MockFileComponentProvider.h"

#include <carousel/componentsystem/ComponentDefinition.h>

#include <QtCore/QtAlgorithms>
MockFileComponentProvider::MockFileComponentProvider(FakeDefinitionParser *parser)
    : FileComponentProvider()
    , parser(parser)
    , constructor(nullptr)
    , loadCalled(0)
    , initializeCalled(false)
    , initializeReturnValue(true)
    , loadResult(nullptr)
{
}

MockFileComponentProvider::MockFileComponentProvider(const QString &path, FakeDefinitionParser *parser)
    : FileComponentProvider(path)
    , parser(parser)
    , constructor(nullptr)
    , loadCalled(0)
    , initializeCalled(false)
    , initializeReturnValue(true)
    , loadResult(nullptr)
{
}

MockFileComponentProvider::~MockFileComponentProvider()
{
    qDeleteAll(this->components());
}

IDefinitionParser *MockFileComponentProvider::createParser()
{
    if (parser == nullptr)
        parser = new FakeDefinitionParser();

    return parser;
}

IComponent *MockFileComponentProvider::loadComponent()
{
    loadCalled++;

    if (loadResult == nullptr)
        return FileComponentProvider::loadComponent();

    return loadResult;
}

bool MockFileComponentProvider::initialize()
{
    initializeCalled = true;
    FileComponentProvider::initialize();

    return initializeReturnValue;
}

ProxyComponent *MockFileComponentProvider::createProxy(ComponentDefinition *definition)
{
    return new MockProxyComponent(definition);
}

DefinitionConstuctor *MockFileComponentProvider::createDefinitionConstuctor()
{
    if (constructor == nullptr)
        constructor = new MockDefaultConstructor();
    return constructor;
}

bool MockProxyComponent::initializeReturnValue = true;

MockProxyComponent::MockProxyComponent(QObject *parent)
    : ProxyComponent(new ComponentDefinition(), parent)
{
}

MockProxyComponent::MockProxyComponent(ComponentDefinition *definition, QObject *parent)
    : ProxyComponent(definition, parent)
{
}

bool MockProxyComponent::initialize(QString *)
{
    return initializeReturnValue;
}

