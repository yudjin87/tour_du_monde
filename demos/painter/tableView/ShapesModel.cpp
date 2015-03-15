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

#include "ShapesModel.h"
#include <dom/IShape.h>

#include <QtGui/QColor>

ShapesModel::ShapesModel(const ObservableList<IShape *> &data, QObject *parent)
    : QAbstractListModel(parent)
    , m_data(data)
{
}

QVariant ShapesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return "Color";
            case 1:
                return "x";
            case 2:
                return "y";
            default:
                return QVariant();
            }
        } else if(orientation == Qt::Vertical) {
            return section + 1;
        }
    }

    return QVariant::Invalid;
}

int ShapesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

int ShapesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.size();
}

QVariant ShapesModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= m_data.size())
        qWarning("BAAAAAAAAD");

    IShape *data = m_data[index.row()];
    switch (role) {
    case Qt::DisplayRole: {
        switch (index.column()) {
        case 0:
            return QVariant::Invalid;
        case 1:
            return data->origin().x();
        case 2:
            return data->origin().y();
        default:
            return QVariant::Invalid;
        }
    }
    case Qt::BackgroundColorRole: {
        switch (index.column()) {
        case 0:
            return QVariant(QColor(data->r(), data->g(), data->b(), data->a()));
        default:
            return QVariant::Invalid;
        }
    }
    }

    return QVariant::Invalid;
}

