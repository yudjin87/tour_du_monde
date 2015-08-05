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

#include "FeatureLayerItem.h"
#include "LegendClassItem.h"

#include <carto/ILegendGroup.h>
#include <carto/ILegendClass.h>
#include <carto/FeatureLayer.h>
#include <carto/IFeatureRenderer.h>
#include <carto/commands/RenameLayerCommand.h>
#include <carousel/utils/IServiceLocator.h>

FeatureLayerItem::FeatureLayerItem(IServiceLocator *serviceLocator, FeatureLayer &layer)
    : QStandardItem(layer.name())
    , m_layer(layer)
    , m_serviceLocator(serviceLocator)
{
    Qt::ItemFlags defaultFlags = QStandardItem::flags();
    setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | defaultFlags);

    connect(&layer, &FeatureLayer::nameChanged, this, &FeatureLayerItem::onNameChanged);
    connect(&layer, &FeatureLayer::rendererChanged, this, &FeatureLayerItem::onRendererChanged);

    createNestedItems(layer.renderer());
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

void FeatureLayerItem::createNestedItems(const IFeatureRenderer *renderer)
{
    const ILegendGroup* legendGroup = renderer->legend();
    if (legendGroup->classCount() == 0)
    {
        // If layer doesn't have nested items, context menu won't be raised for it (see LayerTreeView)
        appendRow(new QStandardItem("No legend"));
        return;
    }

    for (const ILegendClassUPtr& legendClass : *legendGroup)
    {
        LegendClassItem* symbolItem = new LegendClassItem(m_serviceLocator, legendClass.get(), m_layer.shapeType());
        appendRow(symbolItem);
    }
}

void FeatureLayerItem::onNameChanged(AbstractLayer *, const QString &)
{
    emitDataChanged();
}

void FeatureLayerItem::onRendererChanged(const IFeatureRenderer *newRenderer)
{
    removeRows(0, rowCount());
    createNestedItems(newRenderer);

    emitDataChanged();
}

