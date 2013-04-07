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

#ifndef COMPONENTMANAGERMODEL_H
#define COMPONENTMANAGERMODEL_H

#include "componentsystemUI/componentsystem_ui_global.h"

#include <utils/IListObserver.h>

#include <QtCore/QAbstractTableModel>
#include <QtCore/QList>

class ComponentDefinition;
class ComponentDefinitionsAdapter;
class IComponent;

class COMP_SYSTEM_UI_API ComponentDefinitionsModel : public QAbstractTableModel, public IListObserver<IComponent *>
{
    Q_OBJECT
public:
    explicit ComponentDefinitionsModel(const ComponentDefinitionsAdapter *adapter, QObject *parent = nullptr);
    ~ComponentDefinitionsModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    void onChanged(const Changes<IComponent *> &changes);

private:
    const ComponentDefinitionsAdapter *m_adapter;
};

#endif // COMPONENTMANAGERMODEL_H
