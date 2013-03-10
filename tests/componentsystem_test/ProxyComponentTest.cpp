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

#include "ProxyComponentTest.h"
#include "fakes/ComponentWithExtensions.h"
#include "fakes/FakeDefinitionParser.h"
#include "fakes/FakeComponentLoader.h"
#include "fakes/MockComponent.h"

#include "Utils.h"

#include <componentsystem/ProxyComponent.h>
#include <componentsystem/IComponentDefinition.h>

#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

#ifdef Q_OS_WIN32
static const QString libraryPattern("%1/%2.dll");
#endif // Q_WS_WIN
#ifdef Q_OS_MAC
static const QString libraryPattern("%1/lib%2.dylib");
#endif // Q_WS_MAC
#ifdef Q_OS_LINUX
static const QString libraryPattern("%1/lib%2.so");
#endif // Q_WS_X11

//------------------------------------------------------------------------------
ProxyComponentTest::ProxyComponentTest(QObject *parent)
    : QObject(parent)
    , definitionLocation(pathToComponentDefinition("TestComponent2"))
{
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, ".");
}

//------------------------------------------------------------------------------
void ProxyComponentTest::shouldReturnSpecifiedNameUntilComponentLoaded()
{
    ProxyComponent component;
    QCOMPARE(component.name(), QString("Undefined_ProxyComponent"));
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldSetupComponentName()
{
    ProxyComponent component; FakeDefinitionParser p; p.m_componentName = "MyComponent";
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);

    QCOMPARE(component.name(), QString("MyComponent"));
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldSetupLoaderFileName()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(loader, nullptr); FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);

    QCOMPARE(loader->setFileNameCalled, 1);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldSetupLoaderFileNameAsComponentNameIfLocationIsAbsent()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(loader, nullptr);
    FakeDefinitionParser p;
    p.m_componentLocation = "";
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);

#ifdef Q_OS_WIN32
    QString fileName = pathToComponent("TestComponent2");
    QCOMPARE(loader->fileName().toLower(), fileName.toLower());
#else
    QString fileName = pathToComponent("TestComponent2");
    QCOMPARE(loader->fileName(), fileName);
#endif // Q_WS_WIN
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldSetupAbsoluteFileNameToLoader()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(loader, nullptr);
    FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);

#ifdef Q_OS_WIN32
    QString fileName = pathToComponent("TestComponent2");
    QCOMPARE(loader->fileName().toLower(), fileName.toLower());
#else
    QString fileName = pathToComponent("TestComponent2");
    QCOMPARE(loader->fileName(), fileName);
#endif // Q_WS_WIN
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldSetupComponentDefinition()
{
    FakeDefinitionParser parser;
    parser.m_description = "ABCD";
    parser.m_productName = "Carousel";
    parser.m_parents.append("ComponentA");
    parser.m_parents.append("Component2");

    ProxyComponent component;
    component.setDefinitionLocation(definitionLocation);

    component.initialize(parser);

    QString fileName = pathToComponent("TestComponent2");

    QCOMPARE(component.definition()->description(), QString("ABCD"));
    QCOMPARE(component.definition()->productName(), QString("Carousel"));
    QCOMPARE(component.definition()->componentLocation(), fileName);
    QCOMPARE(component.definition()->parents().size(), 2);
    QVERIFY(component.definition()->parents().contains("ComponentA"));
    QVERIFY(component.definition()->parents().contains("Component2"));

    // Relative path:
    parser.m_componentLocation = "./TestComponent2";
    ProxyComponent component2;
    component2.setDefinitionLocation(definitionLocation);
    component2.initialize(parser);

    fileName = QDir::cleanPath(pathToComponent("TestComponent2"));
#ifdef Q_OS_WIN32
    QCOMPARE(component2.definition()->componentLocation().toLower(), fileName.toLower());
#else
    QCOMPARE(component2.definition()->componentLocation(), fileName);
#endif // Q_WS_WIN
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldInvokeLoadAvailability()
{
    FakeDefinitionParser p;
    ProxyComponent component;
    component.setDefinitionLocation(definitionLocation);

    QSettings settings;
    settings.setValue(QString("components_availability/%1").arg(p.m_componentName), IComponentDefinition::Disabled);
    settings.sync();

    QSignalSpy spy(component.definition(), SIGNAL(availabilityChanged(Availability)));

    component.initialize(p);

    QCOMPARE(spy.size(), 1);

    settings.clear();
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldReturnTrue()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(loader, nullptr); FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    QVERIFY(component.initialize(p));
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldReturnFalseIfLibraryFileDoesNotExist()
{
    FakeDefinitionParser p;
    p.m_componentName = "MyComponent";
    p.m_componentLocation = "/to/nowhere/MyComponent";

    ProxyComponent component;
    component.setDefinitionLocation("/to/nowhere/MyComponent.definition");

    QVERIFY(!component.initialize(p));
}

//------------------------------------------------------------------------------
void ProxyComponentTest::extensionShouldReturnRealComponentExtension()
{
    FakeComponentLoader *loader = new FakeComponentLoader(new ComponentWithExtensions());

    ProxyComponent component(loader, nullptr); FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);

    component.startup(this);

    IComponentExtension1 *loadedComponentExtension = component.extension<IComponentExtension1>();
    QVERIFY(loadedComponentExtension != nullptr);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::extensionShouldReturnNullUntilRealComponentIsCreated()
{
    ProxyComponent component; FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);

    // Just do not crash here, it is enough
    component.extension<IComponentExtension1>();
}

//------------------------------------------------------------------------------
void ProxyComponentTest::startupShouldLoadComponent()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(loader, nullptr); FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);

    component.startup(this);

    QCOMPARE(loader->loadCalled, 1);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::startupShouldReturnFalseIfInitialzeWasNotCalled()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(loader, nullptr); FakeDefinitionParser p;

    bool result = component.startup(this);

    QCOMPARE(result, false);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::startupShouldReturnFalseIfLoadFailed()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    loader->loadResult = false;
    ProxyComponent component(loader, nullptr); FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);

    bool result = component.startup(this);

    QCOMPARE(result, false);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::startupShouldCallStartupOnTheLoadedComponent()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ((MockComponent *)(loader->mockComponent))->m_returnValue = true;
    ProxyComponent component(loader, nullptr); FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);

    component.startup(this);

    QVERIFY(loader->mockComponent->started());
}

//------------------------------------------------------------------------------
void ProxyComponentTest::startupShouldReturnResultOfTheLoadedComponentStartup()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ((MockComponent *)(loader->mockComponent))->m_returnValue = true;
    ProxyComponent component(loader, nullptr); FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);

    bool result = component.startup(this);

    QVERIFY(result);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::shutdownShouldUnloadComponent()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ((MockComponent *)(loader->mockComponent))->m_returnValue = true;
    ProxyComponent component(loader, nullptr); FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);
    component.startup(this);

    component.shutdown();

    QCOMPARE(loader->unloadCalled, 1);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::shutdownShouldShutdownLoadedComponent()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ((MockComponent *)(loader->mockComponent))->m_returnValue = true;
    ProxyComponent component(loader, nullptr); FakeDefinitionParser p;
    component.setDefinitionLocation(definitionLocation);
    component.initialize(p);
    component.startup(this);

    QVERIFY(loader->mockComponent->started());
    component.shutdown();

    QVERIFY(!loader->mockComponent->started());
}

//------------------------------------------------------------------------------
