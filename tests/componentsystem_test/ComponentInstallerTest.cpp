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

#include "ComponentInstallerTest.h"
#include "fakes/FakeComponentInstaller.h"
#include "fakes/MockComponent.h"
#include "fakes/MockComponent.h"
#include "fakes/MockComponentDependencies.h"

#include "Utils.h"

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/ComponentInstaller.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
static const char *DEFAULT_DIRECTORY = "testComponents";

//------------------------------------------------------------------------------
ComponentInstallerTest::ComponentInstallerTest(QObject *parent)
    : QObject(parent)
    , componentsDir(QCoreApplication::applicationDirPath() + QDir::separator() + DEFAULT_DIRECTORY)
{
}

//------------------------------------------------------------------------------
ComponentInstallerTest::~ComponentInstallerTest()
{
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::shouldSetupInstallDirectoryByDefault()
{
    FakeComponentInstaller installer;
    QString defaultDir = "./components";
    QCOMPARE(installer.installDirectory(), defaultDir);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::tryToInstall_shouldCallDiscoverComponents()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    installer.tryToInstall(QStringList());

    QVERIFY(installer.discoverCalled);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::tryToInstall_shouldAddComponentsToInstallToDependencies()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    installer.discovered.push_back(new MockComponent(QString("TestComponent1")));
    installer.discovered.push_back(new MockComponent(QString("TestComponent2")));
    QSignalSpy spy(installer.dependencies, SIGNAL(onAdded(IComponent *)));

    installer.tryToInstall(QStringList() << "TestComponent1");

    QCOMPARE(spy.size(), 2);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::tryToInstall_shouldResolveWithComponentsToInstall()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    installer.discovered.push_back(new MockComponent(QString("TestComponent1")));
    QSignalSpy spy(installer.dependencies, SIGNAL(onCompleteListWithChildren(IComponent *)));

    installer.tryToInstall(QStringList() << "TestComponent1");

    QCOMPARE(spy.size(), 1);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::tryToInstall_shouldAddExistedComponentsToDependencies()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    MockComponent compA(QString("TestComponent1"));
    installer.addExistedComponent(&compA);

    QSignalSpy spy(installer.dependencies, SIGNAL(onAdded(IComponent *)));

    installer.tryToInstall(QStringList());

    QCOMPARE(spy.size(), 1);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::tryToInstall_shouldReturnResolveResult()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    installer.discovered.push_back(new MockComponent(QString("TestComponent1")));
    installer.discovered.push_back(new MockComponent(QString("TestComponent2")));

    DependenciesSolvingResult result = installer.tryToInstall(QStringList() << "TestComponent1" << "TestComponent2");

    QCOMPARE(result.ordered().size(), 2);
    QCOMPARE(result.missing().size(), 0);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::tryToInstall_shouldReturnResolveResultWithAllDiscoveredDependencies()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    MockChildComponent *child = new MockChildComponent(QString("TestComponent1"));
    child->parents().push_back("TestComponent2");

    installer.discovered.push_back(child);
    installer.discovered.push_back(new MockComponent(QString("TestComponent2")));

    DependenciesSolvingResult result = installer.tryToInstall(QStringList() << "TestComponent1");

    QCOMPARE(result.ordered().size(), 2);
    QCOMPARE(result.missing().size(), 0);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::install_shouldCallLoadComponents()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    installer.discovered.push_back(new MockComponent(QString("TestComponent1")));
    installer.discovered.push_back(new MockComponent(QString("TestComponent2")));
    installer.tryToInstall(QStringList() << "TestComponent1" << "TestComponent2");

    installer.install();

    QVERIFY(installer.loadCalled);
    QCOMPARE(installer.passedComponents.size(), 2);
    removeDir(componentsDir);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::install_shouldNotCallLoadComponentsIfTryWasNotCalled()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);

    installer.install();

    QVERIFY(!installer.loadCalled);
    removeDir(componentsDir);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::install_shouldNotCallLoadComponentsIfOrphanComponentsWere()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    MockChildComponent *child = new MockChildComponent(QString("TestComponent1")); child->parents().push_back("C");
    installer.discovered.push_back(child);
    installer.tryToInstall(QStringList() << "TestComponent1");

    installer.install();

    QVERIFY(!installer.loadCalled);
    removeDir(componentsDir);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::install_shouldCreateSubDirectoryForEachComponent()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    MockComponent *child1 = new MockComponent(QString("TestComponent1"));
    ComponentDefinition *def1 = const_cast<ComponentDefinition *>(child1->definition());
    def1->setDefinitionLocation(pathToComponentDefinition("TestComponent1"));
    def1->setComponentLocation(pathToComponent("TestComponent1"));

    MockComponent *child2 = new MockComponent(QString("TestComponent2"));
    ComponentDefinition *def2 = const_cast<ComponentDefinition *>(child2->definition());
    def2->setDefinitionLocation(pathToComponentDefinition("TestComponent2"));
    def2->setComponentLocation(pathToComponent("TestComponent2"));

    installer.discovered.push_back(child1);
    installer.discovered.push_back(child2);

    installer.tryToInstall(QStringList() << "TestComponent1" << "TestComponent2");

    removeDir(componentsDir);

    installer.install();

    QDir dir = installer.installDirectory();
    QVERIFY(dir.cd("TestComponent1"));

    QDir dir2 = installer.installDirectory();
    QVERIFY(dir2.cd("TestComponent2"));

    removeDir(componentsDir);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::install_shouldReturnPathesToTheCopiedDefinitions()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    MockComponent *child1 = new MockComponent(QString("TestComponent1"));
    ComponentDefinition *def1 = const_cast<ComponentDefinition *>(child1->definition());
    def1->setDefinitionLocation(pathToComponentDefinition("TestComponent1"));
    def1->setComponentLocation(pathToComponent("TestComponent1"));

    installer.discovered.push_back(child1);

    installer.tryToInstall(QStringList() << "TestComponent1");

    QStringList pathes = installer.install();
    QString copiedDefinitionLocation = componentsDir
            + QDir::separator() + QString("TestComponent1")
            + QDir::separator() + QString("TestComponent1.definition");

    QCOMPARE(pathes.size(), 1);

#ifdef Q_OS_WIN32
    QCOMPARE(pathes[0].toLower(), QDir::toNativeSeparators(copiedDefinitionLocation).toLower());
#else
    QCOMPARE(pathes[0], QDir::toNativeSeparators(copiedDefinitionLocation));
#endif // Q_WS_WIN

    removeDir(componentsDir);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::install_shouldCopyDefinitionFile()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    MockComponent *child1 = new MockComponent(QString("TestComponent1"));
    ComponentDefinition *def1 = const_cast<ComponentDefinition *>(child1->definition());
    def1->setDefinitionLocation(pathToComponentDefinition("TestComponent1"));
    def1->setComponentLocation(pathToComponent("TestComponent1"));

    installer.discovered.push_back(child1);

    installer.tryToInstall(QStringList() << "TestComponent1");

    installer.install();

    QString copiedDefinitionLocation = componentsDir
            + QDir::separator() + QString("TestComponent1")
            + QDir::separator() + QString("TestComponent1.definition");

    QFileInfo definitionFile (copiedDefinitionLocation);
    QVERIFY(definitionFile.exists());

    removeDir(componentsDir);
}

//------------------------------------------------------------------------------
void ComponentInstallerTest::install_shouldCopyLibraryFile()
{
    FakeComponentInstaller installer(DEFAULT_DIRECTORY);
    MockComponent *child1 = new MockComponent(QString("TestComponent1"));
    ComponentDefinition *def1 = const_cast<ComponentDefinition *>(child1->definition());
    def1->setDefinitionLocation(pathToComponentDefinition("TestComponent1"));
    def1->setComponentLocation(pathToComponent("TestComponent1"));

    installer.discovered.push_back(child1);

    installer.tryToInstall(QStringList() << "TestComponent1");

    installer.install();

    QString copiedLibraryLocation = componentsDir
            + QDir::separator() + QString("TestComponent1")
            + QDir::separator() + formatLibraryName("TestComponent1");

    QFileInfo libraryFile (copiedLibraryLocation);
    QVERIFY(libraryFile.exists());

    removeDir(componentsDir);
}

//------------------------------------------------------------------------------
