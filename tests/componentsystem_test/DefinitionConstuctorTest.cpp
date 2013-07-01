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
#include "fakes/FakeComponentLocationConstructorDelegate.h"

#include "Utils.h"

#include <carousel/componentsystem/DefinitionConstuctor.h>
#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/Version.h>

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
    parser.m_shortName = "Component2";
    parser.m_version = "1.2.3.4";
    parser.m_description = "ABCD";
    parser.m_productName = "Carousel";
    parser.m_provider = "CarouselTeam";
    parser.m_parents.insert("ComponentA", "2.3.4.5");
    parser.m_parents.insert("ComponentB", "3.4.5.6");
    QDir absolutePath = QCoreApplication::applicationDirPath();

    // Decorated relative name, something like following
    // components/libTestComponent2.so
    QString fileName = absolutePath.relativeFilePath(pathToComponent("TestComponent2"));
    QString definitionFileName = absolutePath.relativeFilePath(pathToComponentDefinition("TestComponent2"));

    ComponentDefinition definition;
    DefinitionConstuctor constuctor;
    bool result = constuctor.construct(&definition, &parser);

    QVERIFY(result);
    QCOMPARE(definition.componentName(), QString("TestComponent2"));
    QCOMPARE(definition.shortComponentName(), QString("Component2"));
    QCOMPARE(definition.version()->toString(), QString("1.2.3.4"));
    QCOMPARE(definition.description(), QString("ABCD"));
    QCOMPARE(definition.productName(), QString("Carousel"));
    QCOMPARE(definition.provider(), QString("CarouselTeam"));
    QCOMPARE(definition.componentLocation(), fileName);
    QCOMPARE(definition.definitionLocation(), definitionFileName);
    QCOMPARE(definition.parents().size(), 2);
    QCOMPARE(definition.parents()["ComponentA"]->toString(), QString("2.3.4.5"));
    QCOMPARE(definition.parents()["ComponentB"]->toString(), QString("3.4.5.6"));
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldUseDefaultProviderIfParserReturnsEmpty()
{
    FakeDefinitionParser parser;
    parser.m_productName = "Carousel";
    parser.m_provider = "";

    ComponentDefinition definition;
    DefinitionConstuctor constuctor;
    constuctor.construct(&definition, &parser);

    QCOMPARE(definition.provider(), ComponentDefinition::defaultProvider());
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldUseDefaultVersionIfParserReturnsEmpty()
{
    FakeDefinitionParser parser;
    parser.m_productName = "Carousel";
    parser.m_version = "";

    ComponentDefinition definition;
    DefinitionConstuctor constuctor;
    QVERIFY(constuctor.construct(&definition, &parser));

    QVERIFY(definition.version()->toString().contains("1.0.0"));
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldUseNameIfShortNameIsEmpty()
{
    FakeDefinitionParser parser;
    parser.m_componentName = "Carousel";
    parser.m_shortName = "";

    ComponentDefinition definition;
    DefinitionConstuctor constuctor;
    constuctor.construct(&definition, &parser);

    QCOMPARE(definition.shortComponentName(), QString("Carousel"));
}

//------------------------------------------------------------------------------
void DefinitionConstuctorTest::construct_ShouldUseDelegateIfAny()
{
    FakeDefinitionParser parser;
    parser.m_componentName = "TestComponent2";

    ComponentDefinition definition;
    DefinitionConstuctor constuctor;
    constuctor.setLocationConstructorDelegate(new FakeComponentLocationConstructorDelegate("/some/where"));
    constuctor.construct(&definition, &parser);

    QCOMPARE(definition.componentLocation(), QString("/some/where"));
    QCOMPARE(definition.definitionLocation(), QString("/some/where"));
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
void DefinitionConstuctorTest::construct_ShouldReturnFalseIfComponentVersionCouldNotParsed()
{
    FakeDefinitionParser parser;
    parser.m_productName = "Carousel";
    parser.m_version = "asdf";

    ComponentDefinition definition;
    DefinitionConstuctor constuctor;
    QVERIFY(!constuctor.construct(&definition, &parser));

    QVERIFY(definition.version()->isEmpty());
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
