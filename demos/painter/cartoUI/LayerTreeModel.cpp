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

#include "LayerTreeModel.h"
#include "cartoUI/LayerPropertyWidgetCreator.h"
#include "cartoUI/LayerItemCreator.h"

#include <display/SymbolThumbnail.h>
#include <carto/IMap.h>
#include <carto/FeatureLayer.h>
#include <carto/commands/RenameLayerCommand.h>
#include <carto/commands/MoveLayerCommand.h>
#include <display/IFeatureRenderer.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>
#include <components/interactivity/IDialogService.h>
#include <components/interactivity/PropertiesDialog.h>
#include <components/interactivity/PropertiesWidget.h>

#include <QtCore/QMimeData>

namespace
{
static const char* LAYER_NAME_MIME = "application/layer.name.list"; // TODO: constexpr, when MSVC will support it
static LoggerFacade Log = LoggerFacade::createLogger("LayerTreeModel");
}

LayerTreeModel::LayerTreeModel(IMap *map, IServiceLocator *serviceLocator, QObject *parent)
    : QStandardItemModel(parent)
    , m_map(map)
    , m_serviceLocator(serviceLocator)
{
    for (AbstractLayer* layer : m_map->layers()) {
        onLayerAdded(layer, -1);
    }

    connect(map, &IMap::layerAdded, this, &LayerTreeModel::onLayerAdded);
    connect(map, &IMap::layerRemoved, this, &LayerTreeModel::onLayerRemoved);
}

void LayerTreeModel::showPropertyDialog(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    const QList<AbstractLayer *>& layers = m_map->layers();
    if (layers.size() <= index.row())
    {
        Log.e(QString("Invalid index %1").arg(index.row()));
        return;
    }

    AbstractLayer *layer = layers.at(index.row());

    LayerPropertyWidgetCreator widgetCreator;
    IDialogService *dialogService = m_serviceLocator->locate<IDialogService>();
    PropertiesDialog* dlg = dialogService->createPropertyDialog(widgetCreator.createLayerPropertiesWidget(layer));
    dlg->show();
}

Qt::ItemFlags LayerTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | defaultFlags; // TODO: rename command

    return Qt::ItemIsDropEnabled | defaultFlags;
}

QStringList LayerTreeModel::mimeTypes() const
{
    QStringList types;
    types << LAYER_NAME_MIME;
    return types;
}

struct IndexMimeData : public QMimeData
{
    QModelIndexList indexes;
};

QMimeData *LayerTreeModel::mimeData(const QModelIndexList &indexes) const
{
    IndexMimeData *mimeData = new IndexMimeData();
    mimeData->indexes = indexes;
    QByteArray encodedData;

//    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes)
    {
        QModelIndex child = index.child(0, 0);
        if (!child.isValid())
        {
            return nullptr; // show menu only for layers, assuming that most nested child is a symbol item
        }

//        if (index.isValid()) {
//            //QString text = data(index, Qt::DisplayRole).toString();
//            QString text = index.
//            stream << text;
//        }
    }

    mimeData->setData(LAYER_NAME_MIME, encodedData);
    return mimeData;
}

bool LayerTreeModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(parent);

    if (!data->hasFormat(LAYER_NAME_MIME))
        return false;

    if (column > 0)
        return false;

//    QModelIndex child = parent.child(0, 0);
//    if (!child.isValid())
//    {
//        return false; // show menu only for layers, assuming that most nested child is a symbol item
//    }

    return true;
}

bool LayerTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

//    if (!parent.isValid())
//        return false;

    if (action == Qt::IgnoreAction)
        return true;

    const IndexMimeData *mimeData = static_cast<const IndexMimeData*>(data);


    //QStandardItemModel::dropMimeData(data, action, row, column, parent);

    int beginRow = 0;

    // When row and column are -1 it means that the dropped data should be considered as dropped directly on parent.
    // Usually this will mean appending the data as child items of parent.
    // If row and column are greater than or equal zero, it means that the drop occurred just before the
    // specified row and column in the specified parent.
    // QModelIndex p = parent;
    if (0 <= row)
    {
        Log.d("----------------0 <= row");
        beginRow = row;
    }
    if (parent.isValid())
    {
        Log.d("----------------else if (parent.isValid())");
        beginRow = parent.row();
        return false; // TODO: insert inside layer, or at zero position
    }
    else
    {
        Log.d("----------------else");
        beginRow = rowCount(QModelIndex());
        //return false;// TODO: insert at the end, when expanded
    }

    int nextMoveIndex = row;
    for (const QModelIndex &index : mimeData->indexes)
    {
        MoveLayerCommand* cmd = m_serviceLocator->buildInstance<MoveLayerCommand>();
        cmd->setLayerIndex(index.row());
        cmd->setNewLayerIndex(nextMoveIndex);
        cmd->pushToStack();
    }

    return true;
}


////------------------------------------------------------------------------------
//QVariant LayerTreeModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    const FeatureLayer *layer = static_cast<FeatureLayer *>(m_map->layers().at(index.row()));

//    switch (role) {
//    case Qt::DisplayRole:
//    case Qt::EditRole:
//        return layer->name();

//    case Qt::DecorationRole:
//        IFeatureRenderer *renderer = layer->renderer();
//        SymbolThumbnail thumbnailCreator(16, 2);
//        thumbnailCreator.setBackground(Qt::white);
//        QPixmap symbol = thumbnailCreator.createSymbolThumbnail(renderer->symbol(), layer->shapeType());
//        return symbol;
//    }

//    return QVariant();
//}

//QVariant LayerTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    if (section != 0 || role != Qt::DisplayRole || orientation != Qt::Horizontal)
//        return QVariant();

//    return "Layers";
//}

void LayerTreeModel::onLayerAdded(AbstractLayer *layer, const int index)
{
    LayerItemCreator itemCreator;
    QStandardItem* layerItem = itemCreator.createItem(layer);
    insertRow(index, layerItem);
}

void LayerTreeModel::onLayerRemoved(AbstractLayer *, const int index)
{
    removeRow(index);
}

void LayerTreeModel::onMapRefreshed()
{
    emit dataChanged(QModelIndex(), QModelIndex());
}

