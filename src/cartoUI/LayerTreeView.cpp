/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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

#include "cartoUI/LayerTreeView.h"
#include "cartoUI/LayerTreeModel.h"

#include <QtGui/QContextMenuEvent>
#include <QtWidgets/QMenu>

LayerTreeView::LayerTreeView(QWidget *parent)
  : QTreeView(parent)
  , m_menu(new QMenu(this))
  , m_model(nullptr)
  , m_contexMenuItemIndex()
{
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setAnimated(true);

    QAction* removeLayerAction = new QAction("Remove layer", m_menu);
    connect(removeLayerAction, &QAction::triggered, this, &LayerTreeView::onRemoveLayer);
    m_menu->addAction(removeLayerAction);

    QAction* showAttributeTableAction = new QAction("Show attributes", m_menu);
    connect(showAttributeTableAction, &QAction::triggered, this, &LayerTreeView::onShowAttributeTable);
    m_menu->addAction(showAttributeTableAction);

    QAction* propertiesAction = new QAction("Properties", m_menu);
    connect(propertiesAction, &QAction::triggered, this, &LayerTreeView::onPropertyDialog);
    m_menu->addAction(propertiesAction);
}

LayerTreeView::~LayerTreeView()
{
}

void LayerTreeView::setLayerTreeModel(LayerTreeModel *model)
{
    delete m_model;
    m_model = model;
    setModel(m_model);

    if (m_model != nullptr)
    {
        m_model->setParent(this);
    }
}

void LayerTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    m_contexMenuItemIndex = indexAt(event->pos());
    if (!m_contexMenuItemIndex.isValid())
    {
        return;
    }

    QModelIndex child = m_contexMenuItemIndex.child(0, 0);
    if (!child.isValid())
    {
        return; // show menu only for layers, assuming that most nested child is a symbol item
    }

    m_menu->popup(viewport()->mapToGlobal(event->pos()));
}

void LayerTreeView::onShowAttributeTable()
{
    m_model->showAttributeTable(m_contexMenuItemIndex);
}

void LayerTreeView::onPropertyDialog()
{
    m_model->showPropertyDialog(m_contexMenuItemIndex);
    m_contexMenuItemIndex = QModelIndex();
}

void LayerTreeView::onRemoveLayer()
{
    m_model->removeLayer(m_contexMenuItemIndex);
    m_contexMenuItemIndex = QModelIndex();
}

