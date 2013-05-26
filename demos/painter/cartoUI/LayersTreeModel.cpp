//#include "LayersTreeModel.h"

//#include <carto/Map.h>
//#include <carto/AbstractLayer.h>
//#include <display/FeatureRenderer.h>

//#include <QtGui/QPixmap>

////------------------------------------------------------------------------------
//LayersTreeModel::LayersTreeModel(Map *map, QObject *parent)
//    : QAbstractListModel(parent)
//    , m_map(map)
//{
//    connect(map, SIGNAL(layerAdded(AbstractLayer*)), this, SLOT(onLayerAdded(AbstractLayer*)));
//}

////------------------------------------------------------------------------------
//int LayersTreeModel::rowCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//    return m_map->layers().size();
//}

////------------------------------------------------------------------------------
//QVariant LayersTreeModel::data(const QModelIndex &index, int role) const
//{
//    const AbstractLayer *layer = m_map->layers().at(index.row());

//    switch (role) {
//    case Qt::DisplayRole:
//        return layer->name();

//    case Qt::DecorationRole:
//        FeatureRenderer *renderer = layer->renderer();
//        QPixmap pixmap(10, 10);
//        pixmap.fill(renderer->brush().color());
//        return pixmap;
//    }
//    return QVariant();
//}

////------------------------------------------------------------------------------
//void LayersTreeModel::onLayerAdded(AbstractLayer *layer)
//{
//    Q_UNUSED(layer);
//    beginInsertRows(QModelIndex(), 0, m_map->layers().size());
//    endInsertRows();
//}

////------------------------------------------------------------------------------
