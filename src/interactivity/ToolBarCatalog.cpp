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

#include <QtGui/QAction>
#include <QtGui/QMainWindow>
#include <QtGui/QToolBar>
#include <QtCore/QtAlgorithms>

//------------------------------------------------------------------------------
ToolBarCatalog::ToolBarCatalog(QMainWindow &i_shell)
    : m_shell(i_shell)
{
}

//------------------------------------------------------------------------------
ToolBarCatalog::~ToolBarCatalog()
{
    qDeleteAll(m_toolbars);
}

//------------------------------------------------------------------------------
QToolBar *ToolBarCatalog::add(const QString &i_title)
{
    return add(Qt::TopToolBarArea, i_title);
}

//------------------------------------------------------------------------------
QToolBar *ToolBarCatalog::add(Qt::ToolBarArea i_area, const QString &i_title)
{
    if (i_title.isEmpty())
        return nullptr;

    QToolBar *found = find(i_title);
    if (found != nullptr)
        return found;

    QToolBar *newToolbar =  _createToolbar(i_area, i_title);
    onToolbarAdded(newToolbar);

    return newToolbar;
}

//------------------------------------------------------------------------------
void ToolBarCatalog::deleteToolbar(const QString &i_title)
{
    QToolBar *toolbar = find(i_title);
    deleteToolbar(toolbar);
}

//------------------------------------------------------------------------------
void ToolBarCatalog::deleteToolbar(QToolBar *toolbar)
{
    if (m_toolbars.removeOne(toolbar))
        delete toolbar;
}

//------------------------------------------------------------------------------
QToolBar *ToolBarCatalog::find(const QString &i_title)
{
    return const_cast<QToolBar *>(static_cast<const ToolBarCatalog &>(*this).find(i_title));
}

//------------------------------------------------------------------------------
const QToolBar *ToolBarCatalog::find(const QString &i_title) const
{
    foreach(QToolBar *toolbar, m_toolbars) {
        if (toolbar->windowTitle() == i_title)
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
QToolBar *ToolBarCatalog::_createToolbar(Qt::ToolBarArea i_area, const QString &i_title)
{
    QToolBar *newToolBar = new QToolBar();
    newToolBar->setWindowTitle(i_title);
    newToolBar->setObjectName(i_title);

    m_toolbars.push_back(newToolBar);
    m_shell.addToolBar(i_area, newToolBar);

    return newToolBar;
}

//------------------------------------------------------------------------------
