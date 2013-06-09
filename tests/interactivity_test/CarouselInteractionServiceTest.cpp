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
#include "fakes/MockInputInterceptor.h"
#include "fakes/MockInteractiveExtension.h"
#include "fakes/MockTool.h"

#include <interactivity/CarouselInteractionService.h>
#include <interactivity/OperationCatalog.h>
#include <interactivity/DockWidgetCatalog.h>
#include <interactivity/ICatalogs.h>
#include <interactivity/IComponentConfigurationDelegate.h>
#include <interactivity/InputInterceptor.h>
#include <interactivity/MenuCatalog.h>
#include <interactivity/ToolBase.h>
#include <interactivity/ToolBarCatalog.h>

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
void CarouselInteractionServiceTest::shouldReturnEmptyInputInterceptor()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(service.inputInterceptor() == nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldReturnMainWindow()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(&service.mainWindow() == &mainWnd);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupInputInterceptor()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(service.inputInterceptor() == nullptr);

    InputInterceptor *interceptor = new InputInterceptor();
    service.setInputInterceptor(interceptor);

    QVERIFY(service.inputInterceptor() == interceptor);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupCurrentToolToInterceptor()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockTool tool;
    service.setActiveTool(&tool);
    MockInputInterceptor *interceptor = new MockInputInterceptor();
    interceptor->setSender(&mainWnd);

    service.setInputInterceptor(interceptor);

    QVERIFY(interceptor->receiver() == &tool);
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
void CarouselInteractionServiceTest::shouldNotThrowIfPreviousInterceptorIsNull()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(service.inputInterceptor() == nullptr);

    InputInterceptor *interceptor = new InputInterceptor();
    service.setInputInterceptor(interceptor);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfNewInterceptorIsNull()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    service.setInputInterceptor(new InputInterceptor());
    service.setInputInterceptor(nullptr);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldDeletePreviousInputInterceptor()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    QVERIFY(service.inputInterceptor() == nullptr);

    MockInputInterceptor *interceptor = new MockInputInterceptor();
    bool wasDeleted = false;
    interceptor->setDeleteFlag(wasDeleted);
    service.setInputInterceptor(interceptor);

    QVERIFY(service.inputInterceptor() == interceptor);

    service.setInputInterceptor(new InputInterceptor());

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
void CarouselInteractionServiceTest::shouldCallConfigureWhenComponentStarted()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    FakeComponent comp;
    manager.callOnComponentStarted(&comp);

    QVERIFY(delegate->m_configureCalled);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldCallLoadUiStateWhenComponentStarted()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    MockCarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    FakeComponent comp;
    manager.callOnComponentStarted(&comp);

    QVERIFY(service.loadUiCalled);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldConnectDelegateDeconfigureMethodWithComponentManagerSignal()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

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
void CarouselInteractionServiceTest::shouldSetupNullToInterceptorWhenActiveToolIsDeactivated()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockInputInterceptor *interceptor = new MockInputInterceptor();
    interceptor->setSender(&mainWnd);
    service.setInputInterceptor(interceptor);

    ToolBase tool;
    service.setActiveTool(&tool);

    QVERIFY(interceptor->receiver() == &tool);

    tool.stopExecuting();

    QVERIFY(interceptor->receiver() == nullptr);
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
void CarouselInteractionServiceTest::shouldSetupNewlyCurrentToolToInterceptor()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockInputInterceptor *interceptor = new MockInputInterceptor();
    interceptor->setSender(&mainWnd);
    service.setInputInterceptor(interceptor);

    MockTool tool;
    service.setActiveTool(&tool);

    QVERIFY(interceptor->receiver() == &tool);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfInterceptorIsNull()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);
    MockInputInterceptor *interceptor = new MockInputInterceptor();
    interceptor->setSender(&mainWnd);
    service.setInputInterceptor(interceptor);

    MockTool tool;
    service.setActiveTool(&tool);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfInterceptorIsNullWhenActiveToolIsDeactivated()
{
    QMainWindow mainWnd; MockComponentManager manager(&m_serviceLocator);

    CarouselInteractionService service(&m_serviceLocator, &mainWnd, &manager);

    ToolBase tool;
    service.setActiveTool(&tool);
    tool.stopExecuting();

    // just do not crash here
}

//------------------------------------------------------------------------------
