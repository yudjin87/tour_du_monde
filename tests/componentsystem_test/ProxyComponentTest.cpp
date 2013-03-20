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
#include <componentsystem/ComponentDefinition.h>

#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
ProxyComponentTest::ProxyComponentTest(QObject *parent)
    : QObject(parent)
    , definitionLocation(pathToComponentDefinition("TestComponent2"))
{
    QDir absolutePath = QCoreApplication::applicationDirPath();
    componentFileName = absolutePath.relativeFilePath(pathToComponent("TestComponent2"));

    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, ".");
}

//------------------------------------------------------------------------------
void ProxyComponentTest::shouldReturnSpecifiedNameUntilComponentLoaded()
{
    ProxyComponent component(new ComponentDefinition());
    QCOMPARE(component.name(), QString("Undefined_ProxyComponent"));
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldSetupAbsoluteFileNameToLoader()
{
    ComponentDefinition *def = new ComponentDefinition();  QFileInfo file(componentFileName);
    def->setComponentLocation(file.fileName());

    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(def, loader, nullptr);
    component.setDefinitionLocation(definitionLocation);
    component.initialize();

#ifdef Q_OS_WIN32
    QString fileName = pathToComponent("TestComponent2");
    QCOMPARE(loader->fileName().toLower(), fileName.toLower());
#else
    QString fileName = pathToComponent("TestComponent2");
    QCOMPARE(loader->fileName(), fileName);
#endif // Q_WS_WIN
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldInvokeLoadAvailability()
{
    ComponentDefinition *def = new ComponentDefinition();  QFileInfo file(componentFileName);
    def->setComponentLocation(file.fileName());
    def->setComponentName("TestComponent2");

    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(def, loader, nullptr);
    component.setDefinitionLocation(definitionLocation);

    QSettings settings;
    settings.setValue(QString("components_availability/%1").arg(def->componentName()), ComponentDefinition::Disabled);
    settings.sync();

    QSignalSpy spy(component.definition(), SIGNAL(availabilityChanged(Availability)));

    component.initialize();

    QCOMPARE(spy.size(), 1);
    settings.clear();
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldReturnTrue()
{
    ComponentDefinition *def = new ComponentDefinition();  QFileInfo file(componentFileName);
    def->setComponentLocation(file.fileName());
    def->setComponentName("TestComponent2");
    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(def, loader, nullptr);
    component.setDefinitionLocation(definitionLocation);
    QVERIFY(component.initialize());
}

//------------------------------------------------------------------------------
void ProxyComponentTest::initializeCallShouldReturnFalseIfLibraryFileDoesNotExist()
{
    ComponentDefinition *def = new ComponentDefinition();
    def->setComponentLocation("/to/nowhere/MyComponent");
    def->setComponentName("TestComponent2");
    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(def, loader, nullptr);
    component.setDefinitionLocation(definitionLocation);
    QVERIFY(!component.initialize());
}

//------------------------------------------------------------------------------
void ProxyComponentTest::extensionShouldReturnRealComponentExtension()
{
    FakeComponentLoader *loader = new FakeComponentLoader(new ComponentWithExtensions());

    ProxyComponent component(new ComponentDefinition(), loader, nullptr);
    component.initialize();

    component.startup(this);

    IComponentExtension1 *loadedComponentExtension = component.extension<IComponentExtension1>();
    QVERIFY(loadedComponentExtension != nullptr);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::extensionShouldReturnNullUntilRealComponentIsCreated()
{
    ProxyComponent component(new ComponentDefinition());
    component.initialize();

    // Just do not crash here, it is enough
    component.extension<IComponentExtension1>();
}

//------------------------------------------------------------------------------
void ProxyComponentTest::startupShouldLoadComponent()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ProxyComponent component(new ComponentDefinition(), loader, nullptr);
    component.initialize();

    component.startup(this);

    QCOMPARE(loader->loadCalled, 1);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::startupShouldReturnFalseIfInitialzeWasNotCalled()
{
    ProxyComponent component(new ComponentDefinition());

    bool result = component.startup(this);

    QCOMPARE(result, false);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::startupShouldReturnFalseIfLoadFailed()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    loader->loadResult = false;
    ProxyComponent component(new ComponentDefinition(), loader, nullptr);
    component.initialize();

    bool result = component.startup(this);

    QCOMPARE(result, false);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::startupShouldCallStartupOnTheLoadedComponent()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ((MockComponent *)(loader->mockComponent))->m_returnValue = true;
    ProxyComponent component(new ComponentDefinition(), loader, nullptr);
    component.initialize();

    component.startup(this);

    QVERIFY(loader->mockComponent->started());
}

//------------------------------------------------------------------------------
void ProxyComponentTest::startupShouldReturnResultOfTheLoadedComponentStartup()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ((MockComponent *)(loader->mockComponent))->m_returnValue = true;
    ProxyComponent component(new ComponentDefinition(), loader, nullptr);
    component.initialize();

    bool result = component.startup(this);

    QCOMPARE(result, true);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::shutdownShouldUnloadComponent()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ((MockComponent *)(loader->mockComponent))->m_returnValue = true;
    ProxyComponent component(new ComponentDefinition(), loader, nullptr);
    component.initialize();
    component.startup(this);

    component.shutdown();

    QCOMPARE(loader->unloadCalled, 1);
}

//------------------------------------------------------------------------------
void ProxyComponentTest::shutdownShouldShutdownLoadedComponent()
{
    FakeComponentLoader *loader = new FakeComponentLoader();
    ((MockComponent *)(loader->mockComponent))->m_returnValue = true;
    ProxyComponent component(new ComponentDefinition(), loader, nullptr);
    component.initialize();
    component.startup(this);

    QVERIFY(loader->mockComponent->started());
    component.shutdown();

    QVERIFY(!loader->mockComponent->started());
}

//------------------------------------------------------------------------------
