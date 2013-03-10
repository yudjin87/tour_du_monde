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

#include "CarouselComponentConfigurationDelegateTest.h"

#include "fakes/MockApplication.h"
#include "fakes/MockCommand.h"
#include "fakes/MockInteractiveExtension.h"
#include "fakes/MockNonInteractiveExtension.h"

#include <interactivity/CarouselComponentConfigurationDelegate.h>
#include <interactivity/Catalogs.h>
#include <interactivity/ConfigurationChanges.h>
#include <interactivity/ICatalogs.h>
#include <interactivity/ICommandCatalog.h>
#include <interactivity/IDockWidgetCatalog.h>
#include <interactivity/IMenuCatalog.h>
#include <interactivity/IToolBarCatalog.h>

#include <QtGui/QMainWindow>
#include <QtTest/QtTest>

static MockApplication &mockApp = static_cast<MockApplication &>(*qApp);
//------------------------------------------------------------------------------
void configureCatalogs(ICatalogs &catalogs);

//------------------------------------------------------------------------------
CarouselComponentConfigurationDelegateTest::CarouselComponentConfigurationDelegateTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void CarouselComponentConfigurationDelegateTest::shouldCallConfigureGuiIfComponentHasInteractiveExtension()
{
    CarouselComponentConfigurationDelegate delegate;
    MockInteractiveExtension component;

    QMainWindow mw; Catalogs ctlgs(mw, nullptr);
    delegate.configure(&component, ctlgs, mockApp);

    QVERIFY(component.mp_interactiveExtension->m_configureCalled);
}

//------------------------------------------------------------------------------
void CarouselComponentConfigurationDelegateTest::shouldNotThrowIfComponentHasNoInteractiveExtension()
{
    CarouselComponentConfigurationDelegate delegate;
    MockNonInteractiveExtension component;

    QMainWindow mw; Catalogs ctlgs(mw, nullptr);
    delegate.configure(&component, ctlgs, mockApp);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselComponentConfigurationDelegateTest::shouldRegisterChangesForComponent()
{
    CarouselComponentConfigurationDelegate delegate;
    MockInteractiveExtension component;
    component.mp_interactiveExtension->setCunfigureFunc(&configureCatalogs);
    QMainWindow mw; Catalogs ctlgs(mw, nullptr);
    delegate.configure(&component, ctlgs, mockApp);

    const ConfigurationChanges &changes = *delegate.changesByComponent(&component);
    QCOMPARE(changes.addedCommands().size(), 1);
    QCOMPARE(changes.addedMenus().size(), 1);

    QCOMPARE(changes.addedCommands()[0], ctlgs.commandCatalog().commands()[0]);
    QCOMPARE(changes.addedMenus()[0], ctlgs.menuCatalog().menus()[0]);
}

//------------------------------------------------------------------------------
void CarouselComponentConfigurationDelegateTest::shouldReturnNullForUnconfiguredComponent()
{
    CarouselComponentConfigurationDelegate delegate;
    MockInteractiveExtension component;
    component.mp_interactiveExtension->setCunfigureFunc(&configureCatalogs);
    QMainWindow mw; Catalogs ctlgs(mw, nullptr);
    delegate.configure(&component, ctlgs, mockApp);

    MockInteractiveExtension component2;
    const ConfigurationChanges *changes = delegate.changesByComponent(&component2);

    QVERIFY(changes == nullptr);
}

//------------------------------------------------------------------------------
void CarouselComponentConfigurationDelegateTest::shouldNotRegisterChangesAfterConfiguring()
{
    CarouselComponentConfigurationDelegate delegate;
    MockInteractiveExtension component;
    component.mp_interactiveExtension->setCunfigureFunc(&configureCatalogs);
    QMainWindow mw; Catalogs ctlgs(mw, nullptr);
    delegate.configure(&component, ctlgs, mockApp);

    const ConfigurationChanges &changes = *delegate.changesByComponent(&component);
    QCOMPARE(changes.addedCommands().size(), 1);
    QCOMPARE(changes.addedMenus().size(), 1);

    ctlgs.menuCatalog().addMenu("One more menu");

    QCOMPARE(changes.addedMenus().size(), 1);
}

//------------------------------------------------------------------------------
void CarouselComponentConfigurationDelegateTest::shouldDeconfigureComponent()
{
    CarouselComponentConfigurationDelegate delegate;
    MockInteractiveExtension component;
    component.mp_interactiveExtension->setCunfigureFunc(&configureCatalogs);
    QMainWindow mw; Catalogs ctlgs(mw, nullptr);

    QCOMPARE(ctlgs.commandCatalog().commands().size(), 0);
    QCOMPARE(ctlgs.menuCatalog().menus().size(), 0);
    QCOMPARE(ctlgs.dockWidgetCatalog().dockWidgets().size(), 0);
    QCOMPARE(ctlgs.toolBarCatalog().toolbars().size(), 0);

    delegate.configure(&component, ctlgs, mockApp);
    delegate.deconfigure(&component, ctlgs);

    QCOMPARE(ctlgs.commandCatalog().commands().size(), 0);
    QCOMPARE(ctlgs.menuCatalog().menus().size(), 0);
    QCOMPARE(ctlgs.dockWidgetCatalog().dockWidgets().size(), 0);
    QCOMPARE(ctlgs.toolBarCatalog().toolbars().size(), 0);
}

//------------------------------------------------------------------------------
void configureCatalogs(ICatalogs &catalogs)
{
    catalogs.commandCatalog().add(new MockCommand());
    catalogs.menuCatalog().addMenu("NewMenu");
}

//------------------------------------------------------------------------------
