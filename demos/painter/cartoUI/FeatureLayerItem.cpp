/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include "FeatureLayerItem.h"
#include "SymbolItem.h"

#include <carto/commands/RenameLayerCommand.h>
#include <carto/FeatureLayer.h>
#include <display/IFeatureRenderer.h>
#include <carousel/utils/IServiceLocator.h>

FeatureLayerItem::FeatureLayerItem(IServiceLocator *serviceLocator, FeatureLayer &layer)
    : QStandardItem(layer.name())
    , m_layer(layer)
    , m_serviceLocator(serviceLocator)
{
    Qt::ItemFlags defaultFlags = QStandardItem::flags();
    setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | defaultFlags);

    SymbolItem* symbolItem = new SymbolItem(layer.renderer()->symbol(), layer.shapeType());
    appendRow(symbolItem);
    QObject::connect(layer.renderer(), &IFeatureRenderer::symbolChanged, symbolItem, &SymbolItem::setSymbol);

    connect(&layer, &AbstractLayer::nameChanged, this, &FeatureLayerItem::onNameChanged);
}

FeatureLayerItem::~FeatureLayerItem()
{
}

QVariant FeatureLayerItem::data(int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QStandardItem::data(role);
    }

    return m_layer.name();
}

void FeatureLayerItem::setData(const QVariant &value, int role)
{
    QStandardItem::setData(value, role);
    if (role != Qt::EditRole)
    {
        return;
    }

    RenameLayerCommand* rename = m_serviceLocator->buildInstance<RenameLayerCommand>();
    rename->setLayer(&m_layer);
    rename->setNewName(value.toString());
    rename->pushToStack();
}

void FeatureLayerItem::onNameChanged(AbstractLayer *, const QString &)
{
    emitDataChanged();
}

