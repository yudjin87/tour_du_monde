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

#include "LayersTreeModel.h"
#include "cartoUI/LayerPropertyWidgetCreator.h"

#include <display/SymbolThumbnail.h>
#include <carto/IMap.h>
#include <carto/FeatureLayer.h>
#include <carto/commands/RenameLayerCommand.h>
#include <display/FeatureRenderer.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>
#include <components/interactivity/IDialogService.h>
#include <components/interactivity/PropertiesDialog.h>
#include <components/interactivity/PropertiesWidget.h>

#include <QtCore/QMimeData>

//------------------------------------------------------------------------------
namespace
{
static const char* LAYER_NAME_MIME = "application/layer.name.list"; // TODO: constexpr, when MSVC will support it
static LoggerFacade Log = LoggerFacade::createLogger("LayersTreeModel");
}

//------------------------------------------------------------------------------
LayersTreeModel::LayersTreeModel(IMap *map, IServiceLocator *serviceLocator, QObject *parent)
    : QAbstractListModel(parent)
    , m_map(map)
    , m_serviceLocator(serviceLocator)
{
    for (AbstractLayer* layer : m_map->layers()) {
        connect(layer, &AbstractLayer::nameChanged, this, &LayersTreeModel::onNameChanged);
    }

    connect(map, &IMap::layerAdded, this, &LayersTreeModel::onLayerAdded);
    connect(map, &IMap::layerRemoved, this, &LayersTreeModel::onLayerRemoved);
    connect(map, &IMap::refreshed, this, &LayersTreeModel::onMapRefreshed);
}

//------------------------------------------------------------------------------
Qt::ItemFlags LayersTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | defaultFlags;

    return Qt::ItemIsDropEnabled | defaultFlags;
}

//------------------------------------------------------------------------------
QStringList LayersTreeModel::mimeTypes() const
{
    QStringList types;
    types << LAYER_NAME_MIME;
    return types;
}

//------------------------------------------------------------------------------
QMimeData *LayersTreeModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }

    mimeData->setData(LAYER_NAME_MIME, encodedData);
    return mimeData;
}

//------------------------------------------------------------------------------
bool LayersTreeModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(parent);

    if (!data->hasFormat(LAYER_NAME_MIME))
        return false;

    if (column > 0)
        return false;

    return true;
}

//------------------------------------------------------------------------------
bool LayersTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    if (action == Qt::IgnoreAction)
        return true;

    int beginRow = 0;

    if (row != -1)
        beginRow = row;
    else if (parent.isValid())
        beginRow = parent.row();
    else
        beginRow = rowCount(QModelIndex());

    QByteArray encodedData = data->data(LAYER_NAME_MIME);
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    int rows = 0;

    int nextMoveIndex = row;
    while (!stream.atEnd()) {
        QString name;
        stream >> name;
        AbstractLayer* movedLayer = m_map->getLayer(name);
        Q_ASSERT(movedLayer != nullptr && "Invalid layer name during Drag&Drop");

        m_map->moveLayer(movedLayer, nextMoveIndex);
        ++nextMoveIndex;
        ++rows;
    }

//    insertRows(beginRow, rows, QModelIndex());
//    foreach (const QString &text, newItems) {
//        QModelIndex idx = index(beginRow, 0, QModelIndex());
//        setData(idx, text);
//        beginRow++;
//    }

    m_map->refresh();
    return true;
}

// TODO:
#include <QtWidgets/QDialog>

//------------------------------------------------------------------------------
void LayersTreeModel::showPropertyDialog(const QModelIndex &index)
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

//------------------------------------------------------------------------------
bool LayersTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (role != Qt::EditRole)
        return false;

    RenameLayerCommand *renameCommand = m_serviceLocator->buildInstance<RenameLayerCommand>();
    renameCommand->setLayerIndex(index.row());
    renameCommand->setNewName(value.toString());
    renameCommand->pushToStack();

    return true;
}

//------------------------------------------------------------------------------
int LayersTreeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_map->layers().size();
}

//------------------------------------------------------------------------------
QVariant LayersTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const FeatureLayer *layer = static_cast<FeatureLayer *>(m_map->layers().at(index.row()));

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return layer->name();

    case Qt::DecorationRole:
        FeatureRenderer *renderer = layer->renderer();
        SymbolThumbnail thumbnailCreator(16, 2);
        thumbnailCreator.setBackground(Qt::white);
        QPixmap symbol = thumbnailCreator.createSymbolThumbnail(renderer->symbol(), layer->shapeType());
        return symbol;
    }

    return QVariant();
}

//------------------------------------------------------------------------------
void LayersTreeModel::onLayerAdded(AbstractLayer *layer)
{
    connect(layer, &AbstractLayer::nameChanged, this, &LayersTreeModel::onNameChanged);

    // TODO: selection lost here
    beginInsertRows(QModelIndex(), 0, m_map->layers().size());
    endInsertRows();
}

//------------------------------------------------------------------------------
void LayersTreeModel::onLayerRemoved(AbstractLayer *layer)
{
    disconnect(layer, &AbstractLayer::nameChanged, this, &LayersTreeModel::onNameChanged);

    // TODO: selection lost here
    beginRemoveRows(QModelIndex(), 0, m_map->layers().size());
    endRemoveRows();
}

//------------------------------------------------------------------------------
void LayersTreeModel::onMapRefreshed()
{
    emit dataChanged(QModelIndex(), QModelIndex());
}

//------------------------------------------------------------------------------
void LayersTreeModel::onNameChanged(AbstractLayer *sender, const QString &newName)
{
    Q_UNUSED(sender)
    Q_UNUSED(newName)
    emit dataChanged(QModelIndex(), QModelIndex());
}

//------------------------------------------------------------------------------
