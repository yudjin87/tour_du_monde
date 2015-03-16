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

#include <carto/commands/RenameLayerCommand.h>
#include <carto/IMap.h>
#include <carto/AbstractLayer.h>
#include <carto/IPainterDocument.h>
#include <carto/IPainterDocumentController.h>

RenameLayerCommand::RenameLayerCommand(IUndoStack *stack, QObject *parent)
    : BaseUndoableCommand(stack, parent)
    , m_layer(nullptr)
    , m_newName()
    , m_oldName()
{
    setText("layer renaming");
}

RenameLayerCommand::~RenameLayerCommand()
{
}

void RenameLayerCommand::setLayer(AbstractLayer *layer)
{
    m_layer = layer;
}

void RenameLayerCommand::setNewName(const QString &newName)
{
    m_newName = newName;
}

void RenameLayerCommand::redo()
{
    if (m_layer == nullptr)
    {
        return;
    }

    m_oldName = m_layer->name();
    m_layer->setName(m_newName);
}

void RenameLayerCommand::undo()
{
    if (m_layer == nullptr)
    {
        return;
    }

    m_newName = m_layer->name();
    m_layer->setName(m_oldName);
}
