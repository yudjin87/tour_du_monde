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

#include "DirectoryWatchingComponentProviderTest.h"
#include "fakes/MockDirectoryComponentProvider.h"
#include "fakes/MockDirectoryWatchingComponentProvider.h"
#include "Utils.h"

#include <carousel/componentsystem/DirectoryWatchingComponentProvider.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QFileSystemWatcher>
#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
typedef AutoComponentProvider<MockDirectoryWatchingComponentProvider> AutoDirectoryWatchingComponentProvider;

//------------------------------------------------------------------------------
DirectoryWatchingComponentProviderTest::DirectoryWatchingComponentProviderTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void DirectoryWatchingComponentProviderTest::initialize_shouldCallProviderInitialize()
{
    MockDirectoryComponentProvider *mock = new MockDirectoryComponentProvider();
    AutoDirectoryWatchingComponentProvider provider(mock);

    QVERIFY(provider.initialize());
    QVERIFY(mock->initializeCalled);
}

//------------------------------------------------------------------------------
void DirectoryWatchingComponentProviderTest::initialize_shouldCreateWatcher()
{
    MockDirectoryComponentProvider *mock = new MockDirectoryComponentProvider();
    MockDirectoryWatchingComponentProvider provider(mock);

    provider.initialize();
    QVERIFY(provider.mockWatcher != nullptr);
}

//------------------------------------------------------------------------------
void DirectoryWatchingComponentProviderTest::initialize_shouldCreateWatcherIfInternalProviderInitializationFault()
{
    MockDirectoryComponentProvider *mock = new MockDirectoryComponentProvider();
    mock->initializeReturnValue = false;
    MockDirectoryWatchingComponentProvider provider(mock);

    // DirectoryComponentProvider initialize() can return false when no components
    // were discovered, but it is normal sutiation for the DirectoryWatchingComponentProvider
    // because components may appear late.
    QVERIFY(!provider.initialize());
    QVERIFY(provider.mockWatcher != nullptr);
}

//------------------------------------------------------------------------------
void DirectoryWatchingComponentProviderTest::initialize_shouldSetupPathToTheWatcher()
{
    MockDirectoryComponentProvider *mock = new MockDirectoryComponentProvider(QCoreApplication::applicationDirPath());
    AutoDirectoryWatchingComponentProvider provider(mock);

    provider.initialize();

    const QFileSystemWatcher *watcher = provider.watcher();
    QCOMPARE(watcher->directories().size(), 1);
    QCOMPARE(watcher->directories()[0], QCoreApplication::applicationDirPath());
}

//------------------------------------------------------------------------------
void DirectoryWatchingComponentProviderTest::shouldCallUpdateAfter_directoryChanged_signal()
{
	// Cannot emit private signal! (since Qt5)
    //MockDirectoryComponentProvider *mock = new MockDirectoryComponentProvider();
    //MockDirectoryWatchingComponentProvider provider(mock);

    //provider.initialize();
    //QCOMPARE(mock->updateCalled, 1);

    //provider.mockWatcher->emitDirectoryChanged();

    //QCOMPARE(mock->updateCalled, 2);
}

//------------------------------------------------------------------------------
void DirectoryWatchingComponentProviderTest::shouldEmitChangesAfter_directoryChanged_signal()
{
	// Cannot emit private signal! (since Qt5)
    //MockDirectoryComponentProvider *mock = new MockDirectoryComponentProvider();
    //QList<IComponent *> updates; updates.push_back(nullptr);
    //mock->updateResult = updates;
    //MockDirectoryWatchingComponentProvider provider(mock);

    //QSignalSpy spy(&provider, SIGNAL(newComponentsDiscovered(const QList<IComponent *> &)));

    //provider.initialize();
    //provider.mockWatcher->emitDirectoryChanged();

    //QCOMPARE(spy.size(), 1);
}

//------------------------------------------------------------------------------
