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

#include <carto/commands/RemoveLayerCommand.h>
#include <carto/IMap.h>
#include <carto/AbstractLayer.h>
#include <carto/IPainterDocument.h>
#include <carto/IPainterDocumentController.h>

RemoveLayerCommand::RemoveLayerCommand(IUndoStack *stack, IPainterDocumentController *docContr, QObject *parent)
    : BaseUndoableCommand(stack, parent)
    , m_docContr(docContr)
    , m_layersToRemove()
    , m_layersToRestore()
{
    setText("removing layer");
}

RemoveLayerCommand::~RemoveLayerCommand()
{
    for (QPair<int, AbstractLayer*>& layer : m_layersToRestore)
    {
        delete layer.second;
    }

    m_layersToRestore.clear();
}

void RemoveLayerCommand::addLayer(AbstractLayer *layer)
{
    Q_ASSERT(layer != nullptr);
    m_layersToRemove.push_back(layer);
}

void RemoveLayerCommand::redo()
{
    IPainterDocument *doc = m_docContr->document();
    IMap* map = doc->map();

    // TODO: group layers?
    for (AbstractLayer* layer : m_layersToRemove)
    {
        const int index = map->getLayerIndex(layer);
        map->takeLayer(layer);

        m_layersToRestore.push_back(QPair<int, AbstractLayer*>(index, layer));
    }
    m_layersToRemove.clear();
    map->refresh();
}

void RemoveLayerCommand::undo()
{
    IPainterDocument *doc = m_docContr->document();
    IMap* map = doc->map();

    for (QPair<int, AbstractLayer*>& layer : m_layersToRestore)
    {
        map->insertLayer(layer.first, layer.second);
        m_layersToRemove.push_back(layer.second);
    }
    m_layersToRestore.clear();
    map->refresh();
}
