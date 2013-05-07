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

#include "ToolBarCatalogTest.h"

#include <interactivity/ToolBarCatalog.h>

#include <QtGui/QAction>
#include <QtGui/QMainWindow>
#include <QtGui/QToolBar>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
ToolBarCatalogTest::ToolBarCatalogTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldAddToolbarToList()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    QVERIFY(toolbar.toolbars().count() == 0);

    toolbar.add("TB1");

    QVERIFY(toolbar.toolbars().count() == 1);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldSetupAddedToolbar()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    toolbar.add("TB1");

    QVERIFY(toolbar.toolbars()[0]->windowTitle() == "TB1");
    QVERIFY(toolbar.toolbars()[0]->objectName() == "TB1");
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldAddToolbarToMainWindow()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    QList<QToolBar *> toolbars = window.findChildren<QToolBar *>();
    QVERIFY(toolbars.count() == 0);

    toolbar.add("TB1");

    toolbars = window.findChildren<QToolBar *>();
    QVERIFY(toolbars.count() == 1);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldEmitWhenToolbarAdded()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);
    QSignalSpy spy(&toolbar, SIGNAL(toolbarAdded(QToolBar *)));

    toolbar.add("TB1");
    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldNotAddToolbarWithEmptyTitleToList()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    QVERIFY(toolbar.toolbars().count() == 0);

    toolbar.add("");

    QVERIFY(toolbar.toolbars().count() == 0);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldNotAddToolbarWithEmptyTitleToMainWindow()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    QList<QToolBar *> toolbars = window.findChildren<QToolBar *>();
    QVERIFY(toolbars.count() == 0);

    toolbar.add("");

    toolbars = window.findChildren<QToolBar *>();
    QVERIFY(toolbars.count() == 0);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldReturnNullIfAddToolbarEmptyTitle()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    QToolBar* tb = toolbar.add("");
    QVERIFY(tb == nullptr);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldNotAddToolbarWithExistedTitleToList()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    toolbar.add("TB1");
    QVERIFY(toolbar.toolbars().count() == 1);

    toolbar.add("TB1");
    QVERIFY(toolbar.toolbars().count() == 1);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldNotAddToolbarWithExistedTitleToMainWindow()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    toolbar.add("TB1");
    QList<QToolBar *> toolbars = window.findChildren<QToolBar *>();
    QVERIFY(toolbars.count() == 1);

    toolbar.add("TB1");
    toolbars = window.findChildren<QToolBar *>();
    QVERIFY(toolbars.count() == 1);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldReturnExistedToolbarActionIfAddToolbarWithExistedTitle()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    toolbar.add("TB1");

    QToolBar* tb = toolbar.add("TB1");

    QVERIFY(toolbar.toolbars()[0] == tb);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldFindToolbarByTilte()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    toolbar.add("TB1");

    QVERIFY(toolbar.toolbars()[0] == toolbar.find("TB1"));
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldReturnNullIfToolbarDoesNotFoundByTilte()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    toolbar.add("TB1");

    QVERIFY(toolbar.find("TB2") == nullptr);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldReturnCorrectToolbarAction()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    QToolBar* tb = toolbar.add("TB1");

    QVERIFY(toolbar.toolbars()[0] == tb);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::returnedToolbarActionShouldHasSpecifiedText()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);

    QAction* toogleAction = toolbar.add("TB1")->toggleViewAction();

    QVERIFY(toogleAction->text() == "TB1");
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldDeleteToolbar()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);
    QToolBar *tb = toolbar.add("TB1");
    toolbar.add("TB2");

    toolbar.deleteToolbar(tb);
    QCOMPARE(toolbar.toolbars().size(), 1);
    QVERIFY(toolbar.find("TB1") == nullptr);
}

//------------------------------------------------------------------------------
void ToolBarCatalogTest::shouldDeleteToolbarByName()
{
    QMainWindow window;
    ToolBarCatalog toolbar(window);
    toolbar.add("TB1");
    toolbar.add("TB2");

    toolbar.deleteToolbar("TB1");
    QCOMPARE(toolbar.toolbars().size(), 1);
    QVERIFY(toolbar.find("TB1") == nullptr);
}

//------------------------------------------------------------------------------
