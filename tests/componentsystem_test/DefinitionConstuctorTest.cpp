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

#include "DefinitionConstuctorTest.h"

#include <componentsystem/DefinitionConstuctor.h>

#include <QtTest/QTest>

//------------------------------------------------------------------------------
DefinitionConstuctorTest::DefinitionConstuctorTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldConstructDefinitionFromParser()
{
//    ProxyComponent component; FakeDefinitionParser p; p.m_componentName = "MyComponent";
//    component.setDefinitionLocation(definitionLocation);
//    component.initialize(p);

    //    QCOMPARE(component.name(), QString("MyComponent"));
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldReturnFalseIfComponentNameIsEmpty()
{
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldSetupAbsoluteFileName()
{
//    FakeComponentLoader *loader = new FakeComponentLoader();
//    ProxyComponent component(loader, nullptr);
//    FakeDefinitionParser p;
//    component.setDefinitionLocation(definitionLocation);
//    component.initialize(p);

//#ifdef Q_OS_WIN32
//    QString fileName = pathToComponent("TestComponent2");
//    QCOMPARE(loader->fileName().toLower(), fileName.toLower());
//#else
//    QString fileName = pathToComponent("TestComponent2");
//    QCOMPARE(loader->fileName(), fileName);
    //#endif // Q_WS_WIN
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldSetupFileNameAsComponentNameIfLocationIsAbsent()
{
//    FakeComponentLoader *loader = new FakeComponentLoader();
//    ProxyComponent component(loader, nullptr);
//    FakeDefinitionParser p;
//    p.m_componentLocation = "";
//    component.setDefinitionLocation(definitionLocation);
//    component.initialize(p);

//#ifdef Q_OS_WIN32
//    QString fileName = pathToComponent("TestComponent2");
//    QCOMPARE(loader->fileName().toLower(), fileName.toLower());
//#else
//    QString fileName = pathToComponent("TestComponent2");
//    QCOMPARE(loader->fileName(), fileName);
    //#endif // Q_WS_WIN
}

//------------------------------------------------------------------------------
