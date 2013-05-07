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

#include "DockWidgetCatalogTest.h"

#include <interactivity/DockWidgetCatalog.h>

#include <QtGui/QDockWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
DockWidgetCatalogTest::DockWidgetCatalogTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldAddDockWidgetToMainWindow()
{
    QMainWindow window;
    DockWidgetCatalog catalog(window);

    QList<QDockWidget *> dockWidgets = window.findChildren<QDockWidget *>();
    QVERIFY(dockWidgets.count() == 0);

    catalog.addDockWidget(new QWidget());

    dockWidgets = window.findChildren<QDockWidget *>();
    QVERIFY(dockWidgets.count() == 1);
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldNotAddDockWidgetToMainWindowIfNullPointerIsPassed()
{
    QMainWindow window;
    DockWidgetCatalog catalog(window);

    catalog.addDockWidget(0);

    QList<QDockWidget *> dockWidgets = window.findChildren<QDockWidget *>();
    QVERIFY(dockWidgets.count() == 0);
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldEmitWhenWidgetAdded()
{
    QMainWindow window;
    DockWidgetCatalog catalog(window);
    QWidget *widget = new QWidget();
    QSignalSpy spy(&catalog, SIGNAL(dockWidgetAdded(QDockWidget *)));

    catalog.addDockWidget(widget);
    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldSetSepcifiedWidgetToTheCreatedDockWidget()
{
    QWidget *widget = new QWidget();
    QMainWindow window;
    DockWidgetCatalog catalog(window);
    QDockWidget *dock = catalog.addDockWidget(widget);

    QVERIFY(dock != nullptr);
    QCOMPARE(dock->widget(), widget);
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldSetSpecifiedWindowTitleToTheCreatedDockWidget()
{
    QWidget *widget = new QWidget();
    QMainWindow window;
    DockWidgetCatalog catalog(window);
    QDockWidget *dock = catalog.addDockWidget(widget, "Title");

    QVERIFY(dock != nullptr);
    QCOMPARE(dock->windowTitle(), QString("Title"));
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldSetSpecifiedObjectNameToTheCreatedDockWidget()
{
    QWidget *widget = new QWidget();
    QMainWindow window;
    DockWidgetCatalog catalog(window);
    QDockWidget *dock = catalog.addDockWidget(widget, "Title");

    QVERIFY(dock != nullptr);
    QCOMPARE(dock->objectName(), QString("Title"));
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldReturnDockWidgets()
{
    QMainWindow window;
    DockWidgetCatalog catalog(window);
    QDockWidget *dock = catalog.addDockWidget(new QWidget());

    QVERIFY(!catalog.dockWidgets().empty());
    QCOMPARE(dock, catalog.dockWidgets()[0]);
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldDeleteDockWidget()
{
    QMainWindow window;
    DockWidgetCatalog catalog(window);
    QDockWidget *dock = catalog.addDockWidget(new QWidget());
    catalog.addDockWidget(new QWidget());

    catalog.deleteDockWidget(dock);
    QCOMPARE(catalog.dockWidgets().size(), 1);
    QVERIFY(catalog.dockWidgets().contains(dock) == false);
}

//------------------------------------------------------------------------------
