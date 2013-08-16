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

#include "CarouselInteractionServiceTest.h"
#include "fakes/FakeComponent.h"
#include "fakes/MockComponentConfigurationDelegate.h"
#include "fakes/MockCarouselInteractionService.h"
#include "fakes/MockComponentManager.h"
#include "fakes/MockInputDispatcher.h"
#include "fakes/MockInteractiveExtension.h"
#include "fakes/MockTool.h"

#include <components/interactivity/CarouselInteractionService.h>
#include <components/interactivity/OperationCatalog.h>
#include <components/interactivity/DockWidgetCatalog.h>
#include <components/interactivity/ICatalogs.h>
#include <components/interactivity/IComponentConfigurationDelegate.h>
#include <components/interactivity/InputDispatcher.h>
#include <components/interactivity/MenuCatalog.h>
#include <components/interactivity/ToolBase.h>
#include <components/interactivity/ToolBarCatalog.h>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtTest/QTest>

#include <memory>

//------------------------------------------------------------------------------
CarouselInteractionServiceTest::CarouselInteractionServiceTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldCreateEmptyCatalogs()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    ICatalogs &catalogs = service.catalogs();

    QCOMPARE(catalogs.operationCatalog().operations().size(), 0);
    QCOMPARE(catalogs.dockWidgetCatalog().dockWidgets().size(), 0);
    QCOMPARE(catalogs.menuCatalog().menus().size(), 0);
    QCOMPARE(catalogs.toolBarCatalog().toolbars().size(), 0);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldReturnEmptyToolByDefault()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(service.activeTool() == nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldReturnEmptyInputDispatcher()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(service.dispatcher() == nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldReturnMainWindow()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(&service.mainWindow() == &mainWnd);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupInputDispatcher()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(service.dispatcher() == nullptr);

    InputDispatcher *dispatcher = new InputDispatcher();
    service.setDispatcher(dispatcher);

    QVERIFY(service.dispatcher() == dispatcher);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupCurrentToolToDispatcher()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockTool tool;
    service.setActiveTool(&tool);
    MockInputDispatcher *dispatcher = new MockInputDispatcher();
    dispatcher->setSender(&mainWnd);

    service.setDispatcher(dispatcher);

    QVERIFY(dispatcher->receiver() == &tool);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNullToolAfterItsDeletion()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    {
        MockTool tool;
        service.setActiveTool(&tool);
        QVERIFY(service.activeTool() != nullptr);
    }

    QVERIFY(service.activeTool() == nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfPreviousDispatcherIsNull()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(service.dispatcher() == nullptr);

    InputDispatcher *dispatcher = new InputDispatcher();
    service.setDispatcher(dispatcher);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfNewDispatcherIsNull()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    service.setDispatcher(new InputDispatcher());
    service.setDispatcher(nullptr);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldDeletePreviousInputDispatcher()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(service.dispatcher() == nullptr);

    MockInputDispatcher *dispatcher = new MockInputDispatcher();
    bool wasDeleted = false;
    dispatcher->setDeleteFlag(wasDeleted);
    service.setDispatcher(dispatcher);

    QVERIFY(service.dispatcher() == dispatcher);

    service.setDispatcher(new InputDispatcher());

    QVERIFY(wasDeleted);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldReturnDefaultConfigurationDelegate()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(service.configurationDelegate() != nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupConfigurationDelegate()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    QVERIFY(service.configurationDelegate() == delegate);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfPreviousDelegateIsNull()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    service.setConfigurationDelegate(nullptr);
    service.setConfigurationDelegate(new MockComponentConfigurationDelegate());

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfNewDelegateIsNull()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    service.setConfigurationDelegate(nullptr);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSaveUiStateWhenComponentManagerShutdDown()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    MockCarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    manager.callOnAboutToShutDown();

    QCOMPARE(service.saveUiCalled, 1);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldtCallConfigureWhenComponentManagerStarted()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    manager.addComponent(new FakeComponent());
    manager.addComponent(new FakeComponent("FakeComponent2"));

    manager.callStartedUp();

    QVERIFY(delegate->m_configureCalled);
    QCOMPARE(delegate->m_configureCalls, 2);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotCallConfigureWhenComponentStartedUntilManagerStarted()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    FakeComponent comp;
    manager.callOnComponentStarted(&comp);

    QVERIFY(!delegate->m_configureCalled);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldCallConfigureWhenComponentStarted()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);
    manager.callStartedUp();

    FakeComponent *comp = new FakeComponent();
    manager.addComponent(comp);
    manager.callOnComponentStarted(comp);

    QVERIFY(delegate->m_configureCalled);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldCallLoadUiStateWhenComponentStarted()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    MockCarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);
    manager.callStartedUp();

    FakeComponent *comp = new FakeComponent();
    manager.addComponent(comp);
    manager.callOnComponentStarted(comp);

    QVERIFY(service.loadUiCalled);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldConnectDelegateDeconfigureMethodWithComponentManagerSignal()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);
    manager.callStartedUp();

    FakeComponent comp;
    manager.callOnComponentAboutToShutDown(&comp);

    QVERIFY(delegate->m_deconfigureCalled);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldDeletePreviousConfigurationDelegate()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    bool wasDelete = false;
    delegate->setDeleteFlag(wasDelete);
    service.setConfigurationDelegate(delegate);
    QVERIFY(service.configurationDelegate() == delegate);

    service.setConfigurationDelegate(nullptr);
    QVERIFY(wasDelete);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldCallDeconfigureForAllComponentsWhileResetUi()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    manager.addComponent(new MockInteractiveExtension("comp1"));
    manager.addComponent(new MockInteractiveExtension("comp2"));
    manager.addComponent(new MockInteractiveExtension("comp3"));

    service.resetUi();

    QCOMPARE(delegate->m_deconfigureCalls, 3);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldCallConfigureForAllComponentsWhileResetUi()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    manager.addComponent(new MockInteractiveExtension("comp1"));
    manager.addComponent(new MockInteractiveExtension("comp2"));
    manager.addComponent(new MockInteractiveExtension("comp3"));

    service.resetUi();

    QCOMPARE(delegate->m_configureCalls, 3);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfConfigurationDelegateIsNullWhileResetUi()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    service.setConfigurationDelegate(nullptr);

    manager.addComponent(new MockInteractiveExtension("comp1"));
    manager.addComponent(new MockInteractiveExtension("comp2"));
    manager.addComponent(new MockInteractiveExtension("comp3"));

    service.resetUi();

    // There are no seg faults here
    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupActiveTool()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    MockTool tool;
    service.setActiveTool(&tool);

    QVERIFY(&tool == service.activeTool());
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldDeactivatePreviousActiveTool()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    MockTool previousTool;
    service.setActiveTool(&previousTool);
    QVERIFY(previousTool.stopExecutingCalled == false);

    MockTool newTool;
    service.setActiveTool(&newTool);
    QVERIFY(previousTool.stopExecutingCalled == true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupNullToolWhenActiveIsDeactivated()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    ToolBase tool;
    service.setActiveTool(&tool);
    tool.stopExecuting();

    QVERIFY(service.activeTool() == nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupNullToDispatcherWhenActiveToolIsDeactivated()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockInputDispatcher *dispatcher = new MockInputDispatcher();
    dispatcher->setSender(&mainWnd);
    service.setDispatcher(dispatcher);

    ToolBase tool;
    service.setActiveTool(&tool);

    QVERIFY(dispatcher->receiver() == &tool);

    tool.stopExecuting();

    QVERIFY(dispatcher->receiver() == nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfPreviousActiveToolIsNull()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    MockTool tool;
    service.setActiveTool(&tool);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupNewlyCurrentToolToDispatcher()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockInputDispatcher *dispatcher = new MockInputDispatcher();
    dispatcher->setSender(&mainWnd);
    service.setDispatcher(dispatcher);

    MockTool tool;
    service.setActiveTool(&tool);

    QVERIFY(dispatcher->receiver() == &tool);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfDispatcherIsNull()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockInputDispatcher *dispatcher = new MockInputDispatcher();
    dispatcher->setSender(&mainWnd);
    service.setDispatcher(dispatcher);

    MockTool tool;
    service.setActiveTool(&tool);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfDispatcherIsNullWhenActiveToolIsDeactivated()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    ToolBase tool;
    service.setActiveTool(&tool);
    tool.stopExecuting();

    // just do not crash here
}

//------------------------------------------------------------------------------
