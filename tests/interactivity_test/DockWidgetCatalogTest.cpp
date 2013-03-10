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
    QWidget *p_widget = new QWidget();
    QMainWindow window;
    DockWidgetCatalog catalog(window);
    QDockWidget *p_dock = catalog.addDockWidget(p_widget);

    QVERIFY(p_dock != nullptr);
    QCOMPARE(p_dock->widget(), p_widget);
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldSetSpecifiedWindowTitleToTheCreatedDockWidget()
{
    QWidget *p_widget = new QWidget();
    QMainWindow window;
    DockWidgetCatalog catalog(window);
    QDockWidget *p_dock = catalog.addDockWidget(p_widget, "Title");

    QVERIFY(p_dock != nullptr);
    QCOMPARE(p_dock->windowTitle(), QString("Title"));
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldReturnDockWidgets()
{
    QMainWindow window;
    DockWidgetCatalog catalog(window);
    QDockWidget *p_dock = catalog.addDockWidget(new QWidget());

    QVERIFY(!catalog.dockWidgets().empty());
    QCOMPARE(p_dock, catalog.dockWidgets()[0]);
}

//------------------------------------------------------------------------------
void DockWidgetCatalogTest::shouldDeleteDockWidget()
{
    QMainWindow window;
    DockWidgetCatalog catalog(window);
    QDockWidget *p_dock = catalog.addDockWidget(new QWidget());
    catalog.addDockWidget(new QWidget());

    catalog.deleteDockWidget(p_dock);
    QCOMPARE(catalog.dockWidgets().size(), 1);
    QVERIFY(catalog.dockWidgets().contains(p_dock) == false);
}

//------------------------------------------------------------------------------
