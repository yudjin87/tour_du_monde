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

#include "DockWidgetCatalog.h"

#include <QtCore/QtAlgorithms>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMainWindow>

//------------------------------------------------------------------------------
DockWidgetCatalog::DockWidgetCatalog(QMainWindow &mainWindow)
    :m_mainWindow(mainWindow)
{
}

//------------------------------------------------------------------------------
DockWidgetCatalog::~DockWidgetCatalog()
{
    qDeleteAll(m_widgets);
}

//------------------------------------------------------------------------------
QDockWidget *DockWidgetCatalog::addDockWidget(QWidget *widget, const QString &windowTitle)
{
    return addDockWidget(widget, windowTitle, Qt::LeftDockWidgetArea);
}

//------------------------------------------------------------------------------
QDockWidget *DockWidgetCatalog::addDockWidget(QWidget *widget, const QString &windowTitle, Qt::DockWidgetArea area)
{
    if (widget == nullptr)
        return nullptr;

    QDockWidget *dock = new QDockWidget();
    dock->setWidget(widget);
    dock->setWindowTitle(windowTitle);
    dock->setObjectName(windowTitle);

    m_widgets.push_back(dock);
    m_mainWindow.addDockWidget(area, dock);

    onDockWidgetAdded(dock);

    return dock;
}

//------------------------------------------------------------------------------
void DockWidgetCatalog::deleteDockWidget(QDockWidget *dockWidget)
{
    if (m_widgets.removeOne(dockWidget))
        delete dockWidget;
}

//------------------------------------------------------------------------------
QList<QDockWidget *> DockWidgetCatalog::dockWidgets() const
{
    return m_widgets;
}

//------------------------------------------------------------------------------
void DockWidgetCatalog::onDockWidgetAdded(QDockWidget *widget)
{
    emit dockWidgetAdded(widget);
}

//------------------------------------------------------------------------------
