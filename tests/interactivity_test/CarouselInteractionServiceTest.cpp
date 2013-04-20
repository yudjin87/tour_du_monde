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
#include "fakes/MockApplication.h"
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
#include <utils/IServiceLocator.h>

#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtTest/QTest>

#include <memory>

//------------------------------------------------------------------------------
#define CONSTRUCT_APP MockApplication& app = dynamic_cast<MockApplication &>(*qApp);\
                      app.resetServices(); \
                      QMainWindow mw; \
                      mw.setMenuBar(new QMenuBar(&mw)); \
                      app.serviceLocator().registerInstance(&mw); \
                      MockComponentManager mockComponentManager; \
                      app.serviceLocator().registerInstance<IComponentManager>(&mockComponentManager);

//------------------------------------------------------------------------------
CarouselInteractionServiceTest::CarouselInteractionServiceTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldCreateEmptyCatalogs()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    ICatalogs &catalogs = service.catalogs();

    QCOMPARE(catalogs.operationCatalog().operations().size(), 0);
    QCOMPARE(catalogs.dockWidgetCatalog().dockWidgets().size(), 0);
    QCOMPARE(catalogs.menuCatalog().menus().size(), 0);
    QCOMPARE(catalogs.toolBarCatalog().toolbars().size(), 0);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldReturnEmptyToolByDefault()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    QVERIFY(service.activeTool() == nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldReturnEmptyInputInterceptor()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    QVERIFY(service.inputInterceptor() == nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldReturnMainWindow()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    QVERIFY(&service.mainWindow() == &mw);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupInputInterceptor()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    QVERIFY(service.inputInterceptor() == nullptr);

    InputInterceptor *interceptor = new InputInterceptor();
    service.setInputInterceptor(interceptor);

    QVERIFY(service.inputInterceptor() == interceptor);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupCurrentToolToInterceptor()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);
    MockTool tool;
    service.setActiveTool(&tool);
    MockInputInterceptor *interceptor = new MockInputInterceptor();
    interceptor->setSender(&mw);

    service.setInputInterceptor(interceptor);

    QVERIFY(interceptor->receiver() == &tool);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfPreviousInterceptorIsNull()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    QVERIFY(service.inputInterceptor() == nullptr);

    InputInterceptor *interceptor = new InputInterceptor();
    service.setInputInterceptor(interceptor);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfNewInterceptorIsNull()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    service.setInputInterceptor(new InputInterceptor());
    service.setInputInterceptor(nullptr);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldDeletePreviousInputInterceptor()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

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
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    QVERIFY(service.configurationDelegate() != nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupConfigurationDelegate()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    QVERIFY(service.configurationDelegate() == delegate);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfPreviousDelegateIsNull()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    service.setConfigurationDelegate(nullptr);
    service.setConfigurationDelegate(new MockComponentConfigurationDelegate());

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfNewDelegateIsNull()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    service.setConfigurationDelegate(nullptr);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldCallConfigureWhenComponentStarted()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    FakeComponent comp;
    mockComponentManager.callOnComponentStarted(&comp);

    QVERIFY(delegate->m_configureCalled);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldCallLoadUiStateWhenComponentStarted()
{
    CONSTRUCT_APP

    MockCarouselInteractionService service(app);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    FakeComponent comp;
    mockComponentManager.callOnComponentStarted(&comp);

    QVERIFY(service.loadUiCalled);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldConnectDelegateDeconfigureMethodWithComponentManagerSignal()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    FakeComponent comp;
    mockComponentManager.callOnComponentShutedDown(&comp);

    QVERIFY(delegate->m_deconfigureCalled);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldDeletePreviousConfigurationDelegate()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

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
    CONSTRUCT_APP

    CarouselInteractionService service(app);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    mockComponentManager.addComponent(new MockInteractiveExtension("comp1"));
    mockComponentManager.addComponent(new MockInteractiveExtension("comp2"));
    mockComponentManager.addComponent(new MockInteractiveExtension("comp3"));

    service.resetUi();

    QCOMPARE(delegate->m_deconfigureCalls, 3);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldCallConfigureForAllComponentsWhileResetUi()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);
    MockComponentConfigurationDelegate* delegate = new MockComponentConfigurationDelegate();
    service.setConfigurationDelegate(delegate);

    mockComponentManager.addComponent(new MockInteractiveExtension("comp1"));
    mockComponentManager.addComponent(new MockInteractiveExtension("comp2"));
    mockComponentManager.addComponent(new MockInteractiveExtension("comp3"));

    service.resetUi();

    QCOMPARE(delegate->m_configureCalls, 3);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfConfigurationDelegateIsNullWhileResetUi()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);
    service.setConfigurationDelegate(nullptr);

    mockComponentManager.addComponent(new MockInteractiveExtension("comp1"));
    mockComponentManager.addComponent(new MockInteractiveExtension("comp2"));
    mockComponentManager.addComponent(new MockInteractiveExtension("comp3"));

    service.resetUi();

    // There are no seg faults here
    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupActiveTool()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    MockTool tool;
    service.setActiveTool(&tool);

    QVERIFY(&tool == service.activeTool());
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldDeactivatePreviousActiveTool()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

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
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    ToolBase tool;
    service.setActiveTool(&tool);
    tool.stopExecuting();

    QVERIFY(service.activeTool() == nullptr);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupNullToInterceptorWhenActiveToolIsDeactivated()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);
    MockInputInterceptor *interceptor = new MockInputInterceptor();
    interceptor->setSender(&mw);
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
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    MockTool tool;
    service.setActiveTool(&tool);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldSetupNewlyCurrentToolToInterceptor()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);
    MockInputInterceptor *interceptor = new MockInputInterceptor();
    interceptor->setSender(&mw);
    service.setInputInterceptor(interceptor);

    MockTool tool;
    service.setActiveTool(&tool);

    QVERIFY(interceptor->receiver() == &tool);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfInterceptorIsNull()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);
    MockInputInterceptor *interceptor = new MockInputInterceptor();
    interceptor->setSender(&mw);
    service.setInputInterceptor(interceptor);

    MockTool tool;
    service.setActiveTool(&tool);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselInteractionServiceTest::shouldNotThrowIfInterceptorIsNullWhenActiveToolIsDeactivated()
{
    CONSTRUCT_APP

    CarouselInteractionService service(app);

    ToolBase tool;
    service.setActiveTool(&tool);
    tool.stopExecuting();

    // just do not crash here
}

//------------------------------------------------------------------------------
