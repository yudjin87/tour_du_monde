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

#include "cartoPersist/MapPersist.h"
#include "cartoPersist/ILayerPersist.h"
#include "cartoPersist/LayerPersistCreator.h"

#include <carto/IMap.h>
#include <carto/AbstractLayer.h>
#include <carousel/utils/IServiceLocator.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

MapPersist::MapPersist(IServiceLocator &serviceLocator)
    : m_serviceLocator(serviceLocator)
{
}

void MapPersist::save(QJsonObject &obj, const IMap &map)
{
    QJsonArray jsonLayers;
    const QList<AbstractLayer *> layers = map.layers();
    LayerPersistCreator creator;
    for (const AbstractLayer* layer : layers)
    {
        QJsonObject jsonLayerData;
        ILayerPersistUPtr layerPersist = creator.create(*layer);
        layerPersist->save(jsonLayerData);

        QJsonObject jsonLayer;
        jsonLayer.insert("type", toString(layer->type()));
        jsonLayer.insert("data", jsonLayerData);

        jsonLayers.append(jsonLayer);
    }
    obj.insert("layers", jsonLayers);
}

IMapUPtr MapPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "MapPersist: empty object";
        return nullptr;
    }

    IMapUPtr map(m_serviceLocator.buildInstance<IMap>());
    const QJsonArray jsonLayers = obj.value("layers").toArray();
    LayerPersistCreator creator;
    for (const QJsonValue value : jsonLayers)
    {
        const QJsonObject jsonLayer = value.toObject();
        const QString typeName = jsonLayer.value("type").toString();
        const LayerType type = layerTypeFromString(typeName);
        if (!verifyEnum(type))
        {
            if (error) *error = "Invalid layer type";
            continue;
        }

        const QJsonObject jsonLayerData = jsonLayer.value("data").toObject();
        ILayerPersistUPtr layerPersist = creator.create(type);
        AbstractLayerUPtr layer = layerPersist->load(jsonLayerData, m_serviceLocator, error);
        if (layer == nullptr)
        {
            return nullptr;
        }

        map->addLayer(layer.release());
    }

    return map;
}
