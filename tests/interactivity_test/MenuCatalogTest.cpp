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

#include "MenuCatalogTest.h"

#include <components/interactivity/MenuCatalog.h>

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
MenuCatalogTest::MenuCatalogTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldReturnExistedMenus()
{
    QMenuBar menuBar;
    QMenu *menu1 = menuBar.addMenu("Menu1");
    QMenu *menu2 = menuBar.addMenu("Menu2");

    MenuCatalog catalog(menuBar);

    QList<QMenu *> menus = catalog.menus();

    QCOMPARE(2, menus.count());

    QVERIFY(menus.contains(menu1));
    QVERIFY(menus.contains(menu2));
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldReturnBothRemovedAndExistedMenus()
{
    QMenuBar menuBar;
    QMenu *menu1 = menuBar.addMenu("Menu1");
    QMenu *menu2 = menuBar.addMenu("Menu2");

    MenuCatalog catalog(menuBar);
    catalog.removeMenu("Menu1");

    QList<QMenu *> menus = catalog.menus();

    QCOMPARE(2, menus.count());

    QVERIFY(menus.contains(menu1));
    QVERIFY(menus.contains(menu2));
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldEmitWhenMenuAddedToMenuBar()
{
    QMenuBar menuBar;
    MenuCatalog catalog(menuBar);
    QSignalSpy spy(&catalog, SIGNAL(menuAdded(QMenu *)));

    catalog.addMenu("Menu1");
    QCOMPARE(spy.count(), 1);

    catalog.addMenu(QIcon(), "Menu2");
    QCOMPARE(spy.count(), 2);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldEmitWhenMenuAddedToExistingMenu()
{
    QMenuBar menuBar;
    MenuCatalog catalog(menuBar);
    QSignalSpy spy(&catalog, SIGNAL(subMenuAdded(QMenu *)));

    QMenu *menu1 = catalog.addMenu("Menu1");

    menu1->addMenu("SubMenu1");
    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldEmitWhenMenuAddedToExistingMenuInMenuBar()
{
    QMenuBar menuBar;
    QMenu *menu1 = menuBar.addMenu("Menu1");
    menuBar.addMenu("Menu2");

    MenuCatalog catalog(menuBar);
    QSignalSpy spy(&catalog, SIGNAL(subMenuAdded(QMenu *)));

    menu1->addMenu("SubMenu1");
    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldEmitWhenPopupAdded()
{
    QMenuBar menuBar;
    MenuCatalog catalog(menuBar);
    QSignalSpy spy(&catalog, SIGNAL(subMenuAdded(QMenu *)));

    catalog.addPopup("Menu1");
    QCOMPARE(spy.count(), 1);

    catalog.addPopup(QIcon(), "Menu2");
    QCOMPARE(spy.count(), 2);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldEmitWhenMenuRemovedFromMenuBar()
{
    QMenuBar menuBar;
    menuBar.addMenu("Menu1");
    menuBar.addMenu("Menu2");

    MenuCatalog catalog(menuBar);
    QSignalSpy spy(&catalog, SIGNAL(menuRemoved(QMenu *)));

    catalog.removeMenu("Menu1");
    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldEmitWhenSubMenuRemovedFromExistingMenu()
{
    QMenuBar menuBar;
    QMenu *menu1 = menuBar.addMenu("Menu1");
    QMenu *subMenu1 = menu1->addMenu("SubMenu1");
    menuBar.addMenu("Menu2");

    MenuCatalog catalog(menuBar);
    QSignalSpy spy(&catalog, SIGNAL(subMenuRemoved(QMenu *)));

    menu1->removeAction(subMenu1->menuAction());
    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldFindMenuFromMenuBar()
{
    QMenuBar menuBar;
    menuBar.addMenu("Menu1");
    QMenu *menu2 = menuBar.addMenu("Menu2");
    menuBar.addMenu("Menu3");
    menuBar.addMenu("Menu4");

    MenuCatalog catalog(menuBar);
    QMenu *foundMenu = catalog.findMenu("Menu2");

    QCOMPARE(menu2, foundMenu);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldFindMenuFromSubmenu()
{
    QMenuBar menuBar;
    menuBar.addMenu("Menu1");
    QMenu *menu2 = menuBar.addMenu("Menu2");
    menuBar.addMenu("Menu3");
    menuBar.addMenu("Menu4");

    menu2->addMenu("Menu2.Menu1");
    QMenu *menu2menu2 = menu2->addMenu("Menu2.Menu2");
    menu2->addMenu("Menu2.Menu3");

    MenuCatalog catalog(menuBar);
    QMenu *foundMenu = catalog.findMenu("Menu2.Menu2");

    QCOMPARE(menu2menu2, foundMenu);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldRemoveMenuFromMenuBar()
{
    QMenuBar menuBar;
    menuBar.addMenu("Menu1");
    menuBar.addMenu("Menu2");

    MenuCatalog catalog(menuBar);
    catalog.removeMenu("Menu1");

    QCOMPARE(1, menuBar.actions().count());
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldFindMenuEverywhere()
{
    QMenuBar menuBar;
    QMenu *menu1 = menuBar.addMenu("Menu1");
    QMenu *menu2 = menuBar.addMenu("Menu2");

    MenuCatalog catalog(menuBar);
    catalog.removeMenu("Menu2");

    QMenu *foundMenu1 = catalog.findMenuEverywhere("Menu1");
    QMenu *foundMenu2 = catalog.findMenuEverywhere("Menu2");

    QCOMPARE(menu1, foundMenu1);
    QCOMPARE(menu2, foundMenu2);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldCreatePopupMenu()
{
    QMenuBar menuBar;
    MenuCatalog catalog(menuBar);

    QMenu* popup = catalog.addPopup("Menu1");

    QVERIFY(popup != nullptr);
    QVERIFY(popup->menuAction()->text() == "Menu1");
    QVERIFY(popup->title() == "Menu1");
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldAddPopupMenuToList()
{
    QMenuBar menuBar;
    MenuCatalog catalog(menuBar);

    QMenu* popup = catalog.addPopup("Menu1");

    QVERIFY(catalog.popups().size() == 1);
    QVERIFY(catalog.popups()[0] == popup);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldFindPopup()
{
    QMenuBar menuBar;
    MenuCatalog catalog(menuBar);

    catalog.addPopup("Menu0");
    QMenu* popup = catalog.addPopup("Menu1");
    catalog.addPopup("Menu2");

    QVERIFY(catalog.findPopup("Menu1") == popup);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldFindPopupFromSubmenu()
{
    QMenuBar menuBar;
    MenuCatalog catalog(menuBar);

    catalog.addPopup("Menu0");
    QMenu* popup = catalog.addPopup("Menu1");
    popup->addMenu("Menu3");
    QMenu* menu4 = popup->addMenu("Menu4");
    catalog.addPopup("Menu2");

    QVERIFY(catalog.findPopup("Menu4") == menu4);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldDeleteMenu()
{
    QMenuBar menuBar;
    QMenu *menu1 = menuBar.addMenu("Menu1");
    menuBar.addMenu("Menu2");
    MenuCatalog catalog(menuBar);

    catalog.deleteMenu(menu1);
    QCOMPARE(catalog.menus().size(), 1);
    QVERIFY(catalog.findMenuEverywhere("Menu1") == nullptr);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldDeleteRemovedMenu()
{
    QMenuBar menuBar;
    QMenu *menu1 = menuBar.addMenu("Menu1");
    menuBar.addMenu("Menu2");
    MenuCatalog catalog(menuBar);
    catalog.removeMenu("Menu1");

    catalog.deleteMenu(menu1);
    QCOMPARE(catalog.menus().size(), 1);
    QVERIFY(catalog.findMenuEverywhere("Menu1") == nullptr);
}

//------------------------------------------------------------------------------
void MenuCatalogTest::shouldDeleteMenuByName()
{
    QMenuBar menuBar;
    menuBar.addMenu("Menu1");
    menuBar.addMenu("Menu2");
    MenuCatalog catalog(menuBar);

    catalog.deleteMenu("Menu1");
    QCOMPARE(catalog.menus().size(), 1);
    QVERIFY(catalog.findMenuEverywhere("Menu1") == nullptr);
}

//------------------------------------------------------------------------------
