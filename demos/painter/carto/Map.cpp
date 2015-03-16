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

#include "Map.h"
#include "AbstractLayer.h"

#include <carousel/logging/LoggerFacade.h>
#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>

#include <algorithm>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("Map");
}

Map::Map(IPainterDocument *parentDocument, IDisplay *display)
    : m_parentDocument(parentDocument)
    , m_display(display)
{
    connect(m_display, &IDisplay::deviceFrameChanged, this, &Map::onDeviceFrameChanged);
}

Map::~Map()
{
    for (AbstractLayer *layer : m_layers)
        delete layer;

    m_layers.clear();

}

void Map::addLayer(AbstractLayer *layer)
{
    insertLayer(m_layers.size(), layer);
}

void Map::insertLayer(const int index, AbstractLayer *layer)
{
    const bool firstLayer = m_layers.empty();

    m_layers.insert(index, layer);
    const QRectF layerExt = layer->extent();
    if (firstLayer)
    {
        m_display->transformation()->setBounds(layerExt);
    }
    else
    { // TODO: clean me!
        const QRectF current = m_display->transformation()->bounds();

        const qreal newLeft = std::min(layerExt.left(), current.left());
        const qreal newRight = std::max(layerExt.right(), current.right());
        const qreal newTop = std::min(layerExt.top(), current.top());
        const qreal newBottom = std::max(layerExt.bottom(), current.bottom());

        QRectF newExt;
        newExt.setLeft(newLeft);
        newExt.setRight(newRight);
        newExt.setTop(newTop);
        newExt.setBottom(newBottom);

        m_display->transformation()->setBounds(newExt);
    }

    emit layerAdded(layer, index);
}

AbstractLayer *Map::takeLayer(const int index)
{
    AbstractLayer *layer = getLayer(index);
    m_layers.removeAt(index);

    emit layerRemoved(layer, index);

    return layer;
}

int Map::removeLayer(AbstractLayer *layer)
{
    if (layer == nullptr)
        return -1;

    const auto it = std::find(std::begin(m_layers), std::end(m_layers), layer);
    if (it == std::end(m_layers)) {
        Log.d(QString("Layer \"%1\" wasn't found").arg(layer->name()));
        return -1;
    }

    const size_t layerIndex = std::distance(std::begin(m_layers), it);

    Log.d(QString("Removing layer \"%1\" from position %2").arg(layer->name()).arg(layerIndex));

    AbstractLayer *foundLayer = takeLayer(layerIndex);
    Q_ASSERT(foundLayer == layer);

    delete layer;  // TODO: use smart ptr
    return layerIndex;
}

int Map::moveLayer(AbstractLayer *layer, const int index)
{
    if (layer == nullptr)
        return -1;

    const auto it = std::find(std::begin(m_layers), std::end(m_layers), layer);
    if (it == std::end(m_layers)) {
        Log.d(QString("Layer \"%1\" wasn't found").arg(layer->name()));
        return -1;
    }

    const int oldIndex = std::distance(std::begin(m_layers), it);
    if (oldIndex == index) {
        Log.d(QString("Trying to move layer \"%1\" to the same index %2. Skipping").arg(layer->name()).arg(index));
        return -1;
    }

    const int newIndex = ((0 < index) && (index < m_layers.size()))
            ? index
            : 0;

    const int actualNewIndex = newIndex < oldIndex ? newIndex : newIndex - 1; // since it will be removed from old position

    Log.d(QString("Moving layer \"%1\" to position %2").arg(layer->name()).arg(actualNewIndex));

    AbstractLayer *foundLayer = takeLayer(oldIndex);
    Q_ASSERT(foundLayer == layer);
    insertLayer(actualNewIndex, layer);

    return actualNewIndex;
}

AbstractLayer *Map::getLayer(const int index)
{
    return const_cast<AbstractLayer *>(const_cast<const Map*>(this)->getLayer(index));
}

const AbstractLayer *Map::getLayer(const int index) const
{
    if (m_layers.size() <= index)
        return nullptr;

    return m_layers.at(index);
}

AbstractLayer *Map::getLayer(const QString &name)
{
    return const_cast<AbstractLayer *>(const_cast<const Map*>(this)->getLayer(name));
}

const AbstractLayer *Map::getLayer(const QString &name) const
{
    const auto byName = [name](const AbstractLayer *l){ return l->name() == name;};
    const auto it = std::find_if(std::begin(m_layers), std::end(m_layers), byName);
    if (it == std::end(m_layers)) {
        Log.d(QString("No layer with \"%1\" name was found").arg(name));
        return nullptr;
    }

    return *it;
}

QList<AbstractLayer *> Map::layers() const
{
    return m_layers;
}

IPainterDocument *Map::document()
{
    return m_parentDocument;
}

const IPainterDocument *Map::document() const
{
    return m_parentDocument;
}

void Map::refresh()
{
    if (m_layers.isEmpty())
        return;

    m_display->startDrawing(DispayCache::Geometry);
    for (AbstractLayer *layer : m_layers)
        layer->draw(m_display);

    m_display->finishDrawing(DispayCache::Geometry);
}

void Map::onDeviceFrameChanged(const QRectF &)
{
    refresh();
}

