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
#include "fakes/FakeDefinitionParser.h"

#include "Utils.h"

#include <componentsystem/DefinitionConstuctor.h>
#include <componentsystem/ComponentDefinition.h>

#include <QtCore/QDir>
#include <QtTest/QTest>

//------------------------------------------------------------------------------
DefinitionConstuctorTest::DefinitionConstuctorTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldConstructDefinitionFromParser()
{
    FakeDefinitionParser parser;
    parser.m_componentName = "TestComponent2";
    parser.m_description = "ABCD";
    parser.m_productName = "Carousel";
    parser.m_parents.append("ComponentA");
    parser.m_parents.append("Component2");
    QDir absolutePath = QCoreApplication::applicationDirPath();
    QString fileName = absolutePath.relativeFilePath(pathToComponent("TestComponent2"));

    ComponentDefinition definition;
    DefinitionConstuctor constuctor;
    bool result = constuctor.construct(&definition, &parser);

    QVERIFY(result);
    QCOMPARE(definition.description(), QString("ABCD"));
    QCOMPARE(definition.productName(), QString("Carousel"));
    QCOMPARE(definition.componentLocation(), fileName);
    QCOMPARE(definition.parents().size(), 2);
    QVERIFY(definition.parents().contains("ComponentA"));
    QVERIFY(definition.parents().contains("Component2"));
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldReturnFalseIfComponentNameIsEmpty()
{
    FakeDefinitionParser parser;
    parser.m_componentName = " ";

    ComponentDefinition definition;
    DefinitionConstuctor constuctor;
    bool result = constuctor.construct(&definition, &parser);

    QVERIFY(!result);
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldSetupFileNameAsComponentNameIfLocationIsAbsent()
{
    FakeDefinitionParser parser;
    parser.m_componentName = "TestComponent2";
    parser.m_componentLocation = "";

    QDir absolutePath = QCoreApplication::applicationDirPath();
    absolutePath.cd("components");
    QString fileName = absolutePath.relativeFilePath(pathToComponent("TestComponent2"));

    ComponentDefinition definition;
    DefinitionConstuctor constuctor;
    constuctor.construct(&definition, &parser);

#ifdef Q_OS_WIN32
    QCOMPARE(definition.componentLocation().toLower(), fileName.toLower());
#else
    QCOMPARE(definition.componentLocation(), fileName);
#endif // Q_WS_WIN
}

//------------------------------------------------------------------------------
