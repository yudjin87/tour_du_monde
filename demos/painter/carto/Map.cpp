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

#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>

//------------------------------------------------------------------------------
Map::Map(IPainterDocument *parentDocument, IDisplay *display)
    : m_parentDocument(parentDocument)
    , m_display(display)
{
    connect(m_display, &IDisplay::visibleBoundsUpdated, this, &Map::onVisibleBoundsChanged);
}

//------------------------------------------------------------------------------
Map::~Map()
{
    foreach(AbstractLayer *layer, m_layers)
        delete layer;

    m_layers.clear();

}

//------------------------------------------------------------------------------
void Map::addLayer(AbstractLayer *layer)
{
    m_layers.push_back(layer);
    m_display->transformation()->setBounds(layer->extent());
    emit layerAdded(layer);
}

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
void Map::refresh()
{
    QPainter *painter = m_display->startDrawing();
    foreach(AbstractLayer *layer, m_layers)
        layer->draw(m_display);

    m_display->finishDrawing(painter);
}

//------------------------------------------------------------------------------
void Map::onVisibleBoundsChanged(DisplayTransformation *transform)
{
    Q_UNUSED(transform)
    refresh();
}

//------------------------------------------------------------------------------
