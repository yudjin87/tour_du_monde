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

#include <carto/commands/MoveLayerCommand.h>
#include <carto/IMap.h>
#include <carto/AbstractLayer.h>
#include <carto/IPainterDocument.h>
#include <carto/IPainterDocumentController.h>
#include <carousel/logging/LoggerFacade.h>

#include <algorithm>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("MoveLayerCommand");
}

MoveLayerCommand::MoveLayerCommand(IUndoStack *stack, IPainterDocumentController *docContr, QObject *parent)
    : BaseUndoableCommand(stack, parent)
    , m_docContr(docContr)
    , m_layerToMove(-1)
    , m_layerToMoveTo(-1)
    , m_withRefresh(true)
{
    setText("layer moving");
}

MoveLayerCommand::~MoveLayerCommand()
{
}

void MoveLayerCommand::setLayerIndex(const int layerToMove)
{
    m_layerToMove = layerToMove;
}

void MoveLayerCommand::setNewLayerIndex(const int layerToMoveTo)
{
    m_layerToMoveTo = layerToMoveTo;
}

void MoveLayerCommand::redo()
{
    Log.d(QString("Trying to move layer from position %1 to position %2").arg(m_layerToMove).arg(m_layerToMoveTo));
    IPainterDocument *doc = m_docContr->document();
    IMap* map = doc->map();
    AbstractLayer* layerToMove = map->getLayer(m_layerToMove);
    if (layerToMove  == nullptr)
    {
        return;
    }

    int res = map->moveLayer(layerToMove, m_layerToMoveTo);
    if (res == -1)
    {
        return;
    }

    m_layerToMoveTo = res;
    if (m_withRefresh)
    {
        map->refresh();
    }

    std::swap(m_layerToMoveTo, m_layerToMove);
}

void MoveLayerCommand::undo()
{
    redo();
}


