/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include "LayersListView.h"
#include "LayersTreeModel.h"
#include "FeatureLayerDelegate.h"

#include <QtGui/QContextMenuEvent>
#include <QtWidgets/QMenu>

LayersListView::LayersListView(LayersTreeModel *model, QWidget *parent)
    : QListView(parent)
    , m_menu(new QMenu(this))
    , m_model(model)
    , m_contexMenuItemIndex()
{
    m_model->setParent(this);
    setModel(m_model);
    setItemDelegate(new FeatureLayerDelegate(this));
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);

    QAction* propertiesAction = new QAction("Properties", m_menu);
    connect(propertiesAction, &QAction::triggered, this, &LayersListView::onPropertyDialog);

    m_menu->addAction(propertiesAction);
}

LayersListView::~LayersListView()
{

}

void LayersListView::contextMenuEvent(QContextMenuEvent *event)
{
    m_contexMenuItemIndex = indexAt(event->pos());
    if (!m_contexMenuItemIndex.isValid())
    {
        return;
    }

    m_menu->popup(viewport()->mapToGlobal(event->pos()));
}

void LayersListView::onPropertyDialog()
{
    m_model->showPropertyDialog(m_contexMenuItemIndex);
    m_contexMenuItemIndex = QModelIndex();
}
