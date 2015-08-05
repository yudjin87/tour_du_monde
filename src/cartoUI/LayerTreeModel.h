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

#pragma once
#include <geometry/GeometryType.h>

#include <QtGui/QStandardItemModel>

class AbstractLayer;
class IMap;
class IServiceLocator;

class LayerTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit LayerTreeModel(IMap *map, IServiceLocator *serviceLocator, QObject *parent = nullptr);

//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

//    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
//    QModelIndex parent(const QModelIndex &index) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
//    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

//    // Editing

//    // Layer reordering:
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    void showAttributeTable(const QModelIndex &index);
    void showPropertyDialog(const QModelIndex &index);
    void removeLayer(const QModelIndex &index);

private slots:
    void onLayerAdded(AbstractLayer *layer, const int index);
    void onLayerRemoved(AbstractLayer *layer, const int index);
    void onMapRefreshed();

private:
    IMap *m_map;
    IServiceLocator *m_serviceLocator;
};

