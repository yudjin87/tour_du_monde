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

#include "ToolBarCatalog.h"

#include <QtWidgets/QAction>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtCore/QtAlgorithms>

//------------------------------------------------------------------------------
ToolBarCatalog::ToolBarCatalog(QMainWindow &mainWindow)
    : m_mainWindow(mainWindow)
{
}

//------------------------------------------------------------------------------
ToolBarCatalog::~ToolBarCatalog()
{
    qDeleteAll(m_toolbars);
}

//------------------------------------------------------------------------------
QToolBar *ToolBarCatalog::add(const QString &title)
{
    return add(Qt::TopToolBarArea, title);
}

//------------------------------------------------------------------------------
QToolBar *ToolBarCatalog::add(Qt::ToolBarArea area, const QString &title)
{
    if (title.isEmpty())
        return nullptr;

    QToolBar *found = find(title);
    if (found != nullptr)
        return found;

    QToolBar *newToolbar =  createToolbar(area, title);
    onToolbarAdded(newToolbar);

    return newToolbar;
}

//------------------------------------------------------------------------------
void ToolBarCatalog::deleteToolbar(const QString &title)
{
    QToolBar *toolbar = find(title);
    deleteToolbar(toolbar);
}

//------------------------------------------------------------------------------
void ToolBarCatalog::deleteToolbar(QToolBar *toolbar)
{
    if (m_toolbars.removeOne(toolbar))
        delete toolbar;
}

//------------------------------------------------------------------------------
QToolBar *ToolBarCatalog::find(const QString &title)
{
    return const_cast<QToolBar *>(static_cast<const ToolBarCatalog &>(*this).find(title));
}

//------------------------------------------------------------------------------
const QToolBar *ToolBarCatalog::find(const QString &title) const
{
    for (QToolBar *toolbar : m_toolbars) {
        if (toolbar->windowTitle() == title)
            return toolbar;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
QList<QToolBar *> ToolBarCatalog::toolbars() const
{
    return m_toolbars;
}

//------------------------------------------------------------------------------
void ToolBarCatalog::onToolbarAdded(QToolBar *toolbar)
{
    emit toolbarAdded(toolbar);
}

//------------------------------------------------------------------------------
QToolBar *ToolBarCatalog::createToolbar(Qt::ToolBarArea area, const QString &title)
{
    QToolBar *newToolBar = new QToolBar();
    newToolBar->setWindowTitle(title);
    newToolBar->setObjectName(title);

    m_toolbars.push_back(newToolBar);
    m_mainWindow.addToolBar(area, newToolBar);

    return newToolBar;
}

//------------------------------------------------------------------------------
