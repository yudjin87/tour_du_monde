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

#include "ComponentDefinitionsModel.h"
#include "ComponentDefinitionsAdapter.h"

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/IComponent.h>
#include <utils/ObservableList.h>

#include <QtGui/QIcon>

//------------------------------------------------------------------------------
ComponentDefinitionsModel::ComponentDefinitionsModel(const ComponentDefinitionsAdapter *adapter, QObject *parent)
    : QAbstractTableModel(parent)
    , m_adapter(adapter)
{
    m_adapter->components().installObserver(this);
}

//------------------------------------------------------------------------------
ComponentDefinitionsModel::~ComponentDefinitionsModel()
{
}

//------------------------------------------------------------------------------
int ComponentDefinitionsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    if (parent.isValid())
        return 0;

    return m_adapter->components().size();
}

//------------------------------------------------------------------------------
int ComponentDefinitionsModel::columnCount(const QModelIndex &parent) const
{
    return (parent.column() > 0) ? 0 : 5;
}

//------------------------------------------------------------------------------
QVariant ComponentDefinitionsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QAbstractItemModel::headerData(section, orientation, role);

    switch (section) {
    case 0: return "Internal name";
    case 1: return "Name";
    case 2: return "Definition location";
    case 3: return "Library location";
    case 4: return "Description";
    default: return QVariant();
    }
}

//------------------------------------------------------------------------------
QVariant ComponentDefinitionsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.model() != this)
        return QVariant();

    const IComponent *comp = m_adapter->components().at(index.row());
    const ComponentDefinition *def = comp->definition();
    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0: return def->componentName();
        case 1: return def->productName();
        case 2: return def->definitionLocation();
        case 3: return def->componentLocation();
        case 4: return def->description();
        default:
            qWarning("data: invalid display value column %d", index.column());
            break;
        }
        break;

    case Qt::CheckStateRole:
        switch (index.column()) {
        case 0: return comp->availability() == IComponent::Enabled
                    ? Qt::Checked
                    : Qt::Unchecked;
        default: return QVariant::Invalid;
        }
        break;

    case Qt::DecorationRole:
        if (index.column() == 0) {
            QIcon icon;
            return icon;
        }
        break;
    }

    return QVariant();
}

//------------------------------------------------------------------------------
bool ComponentDefinitionsModel::setData(const QModelIndex &index, const QVariant &, int role)
{
    if (!index.isValid()
            || index.column() != 0
            || (index.row() > m_adapter->components().size())
            || role != Qt::CheckStateRole)
        return false;

//    ComponentDefinition *def = m_adapter->components().at(index.row())->definition();
//    def->setAvailability(def->availability() != IComponent::Enabled
//            ? IComponent::Enabled
//            : IComponent::Disabled);

    emit dataChanged(index, index);
    return true;
}

//------------------------------------------------------------------------------
Qt::ItemFlags ComponentDefinitionsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (!index.isValid())
        return flags;

    if (index.column() != 0)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

//------------------------------------------------------------------------------
void ComponentDefinitionsModel::onChanged(const Changes<IComponent *> &changes)
{
    int addedItems = changes.affectedItems.size();
    int oldSize = m_adapter->components().size() - addedItems;
    beginInsertRows(QModelIndex(), oldSize, oldSize);
    endInsertRows();
}

//------------------------------------------------------------------------------
