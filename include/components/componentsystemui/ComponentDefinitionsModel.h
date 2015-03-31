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

#pragma once
#include <components/componentsystemui/componentsystem_ui_global.h>

#include <QtCore/QAbstractTableModel>
#include <QtCore/QList>

class ComponentDefinition;
class ComponentCollection;
class IComponent;
class IServiceLocator;

class COMP_SYSTEM_UI_API ComponentDefinitionsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ComponentDefinitionsModel(const ComponentCollection &components, QObject *parent = nullptr);
    ~ComponentDefinitionsModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void injectServiceLocator(IServiceLocator *locator);

public slots:
    void onInstall();
    void onDescription(const QModelIndex &index);
    void onToogleEnable(const QModelIndex &index);

private slots:
    void onComponentsChanged(IComponent *);

private:
    const ComponentCollection &m_components;
    IServiceLocator *m_locator;
};

