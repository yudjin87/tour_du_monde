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

#include "ComponentManagerModel.h"

#include <QtGui/QIcon>

//------------------------------------------------------------------------------
ComponentManagerModel::ComponentManagerModel(IComponentManager *manager, QObject *parent)
    : QAbstractTableModel(parent)
    , mp_manager(manager)
{
}

//------------------------------------------------------------------------------
int ComponentManagerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    if (parent.isValid())
        return 0;

    return 99;
}

//------------------------------------------------------------------------------
int ComponentManagerModel::columnCount(const QModelIndex &parent) const
{
    return (parent.column() > 0) ? 0 : 4;
}

//------------------------------------------------------------------------------
QVariant ComponentManagerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.model() != this)
        return QVariant();

    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        switch (index.column()) {
//        case 0: return displayName(index);
//        case 1: return size(index);
//        case 2: return type(index);
//        case 3: return time(index);
        default:
            qWarning("data: invalid display value column %d", index.column());
            break;
        }
        break;

    case Qt::DecorationRole:
        if (index.column() == 0) {
            QIcon icon;// = icon(index);
//            if (icon.isNull()) {
//                if (node(index)->isDir())
//                    icon = fileInfoGatherer.iconProvider()->icon(QFileIconProvider::Folder);
//                else
//                    icon = d->fileInfoGatherer.iconProvider()->icon(QFileIconProvider::File);
//            }
            return icon;
        }
        break;
    case Qt::TextAlignmentRole:
        if (index.column() == 1)
            return Qt::AlignRight;
        break;

    }

    return QVariant();
}

//------------------------------------------------------------------------------
bool ComponentManagerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()
        || index.column() != 0
        || role != Qt::EditRole
        || (flags(index) & Qt::ItemIsEditable) == 0) {
        return false;
    }

    QString newName = value.toString();
    QString oldName = index.data().toString();
    if (newName == index.data().toString())
        return true;

    return true;
}

//------------------------------------------------------------------------------
QVariant ComponentManagerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role) {
    case Qt::DecorationRole:
        if (section == 0) {
            QImage pixmap(16, 1, QImage::Format_Mono);
            pixmap.fill(0);
            pixmap.setAlphaChannel(pixmap.createAlphaMask());
            return pixmap;
        }
        break;
    case Qt::TextAlignmentRole:
        return Qt::AlignLeft;
    }

    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QAbstractItemModel::headerData(section, orientation, role);

    QString returnValue;
    switch (section) {
    case 0: returnValue = tr("Name");
            break;
    case 1: returnValue = tr("Size");
            break;
    case 2: returnValue =
                   tr("Type", "All other platforms");
    case 3: returnValue = tr("Date Modified");
            break;
    default: return QVariant();
    }
    return returnValue;
}

//------------------------------------------------------------------------------
Qt::ItemFlags ComponentManagerModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (!index.isValid())
        return flags;

    return flags;
}

//------------------------------------------------------------------------------
void ComponentManagerModel::sort(int column, Qt::SortOrder order)
{
    //if (sortOrder == order && sortColumn == column && !forceSort)
    //    return;

    emit layoutAboutToBeChanged();
    QModelIndexList oldList = persistentIndexList();
//    QList<QPair<QFileSystemModelPrivate::QFileSystemNode*, int> > oldNodes;
//    for (int i = 0; i < oldList.count(); ++i) {
//        QPair<QFileSystemModelPrivate::QFileSystemNode*, int> pair(d->node(oldList.at(i)), oldList.at(i).column());
//        oldNodes.append(pair);
//    }

//    if (!(d->sortColumn == column && d->sortOrder != order && !d->forceSort)) {
//        //we sort only from where we are, don't need to sort all the model
//        d->sortChildren(column, index(rootPath()));
//        d->sortColumn = column;
//        d->forceSort = false;
//    }
//    d->sortOrder = order;

    QModelIndexList newList;
//    for (int i = 0; i < oldNodes.count(); ++i) {
//        QModelIndex idx = d->index(oldNodes.at(i).first);
//        idx = idx.sibling(idx.row(), oldNodes.at(i).second);
//        newList.append(idx);
//    }
    changePersistentIndexList(oldList, newList);
    emit layoutChanged();
}

//------------------------------------------------------------------------------
