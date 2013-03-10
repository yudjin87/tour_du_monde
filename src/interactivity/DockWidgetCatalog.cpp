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
#include <QtGui/QDockWidget>
#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
DockWidgetCatalog::DockWidgetCatalog(QMainWindow &i_shell)
    :m_shell(i_shell)
{
}

//------------------------------------------------------------------------------
DockWidgetCatalog::~DockWidgetCatalog()
{
    qDeleteAll(m_widgets);
}

//------------------------------------------------------------------------------
QDockWidget *DockWidgetCatalog::addDockWidget(QWidget *ip_widget, const QString &windowTitle)
{
    return addDockWidget(ip_widget, windowTitle, Qt::LeftDockWidgetArea);
}

//------------------------------------------------------------------------------
QDockWidget *DockWidgetCatalog::addDockWidget(QWidget *ip_widget, const QString &windowTitle, Qt::DockWidgetArea i_area)
{
    if (ip_widget == nullptr)
        return nullptr;

    QDockWidget *p_dock = new QDockWidget();
    p_dock->setWidget(ip_widget);
    p_dock->setWindowTitle(windowTitle);

    m_widgets.push_back(p_dock);
    m_shell.addDockWidget(i_area, p_dock);

    onDockWidgetAdded(p_dock);

    return p_dock;
}

//------------------------------------------------------------------------------
void DockWidgetCatalog::deleteDockWidget(QDockWidget *ip_dockWidget)
{
    if (m_widgets.removeOne(ip_dockWidget))
        delete ip_dockWidget;
}

//------------------------------------------------------------------------------
QList<QDockWidget *> DockWidgetCatalog::dockWidgets() const
{
    return m_widgets;
}

//------------------------------------------------------------------------------
void DockWidgetCatalog::onDockWidgetAdded(QDockWidget *ip_widget)
{
    emit dockWidgetAdded(ip_widget);
}

//------------------------------------------------------------------------------
