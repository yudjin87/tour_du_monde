#ifndef LAYERSTREEMODEL_H
#define LAYERSTREEMODEL_H

#include <QtCore/QAbstractListModel>

class AbstractLayer;
class Map;

class LayersTreeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LayersTreeModel(Map *map, QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private slots:
    void onLayerAdded(AbstractLayer *layer);

private:
    Map *m_map;
};

#endif // LAYERSTREEMODEL_H
