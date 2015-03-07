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

#include <carto/commands/ChangeLayerSymbolCommand.h>
#include <carto/IMap.h>
#include <carto/FeatureLayer.h>
#include <carto/IPainterDocument.h>
#include <carto/IPainterDocumentController.h>
#include <display/IFeatureRenderer.h>

//------------------------------------------------------------------------------
ChangeLayerSymbolCommand::ChangeLayerSymbolCommand(IUndoStack *stack, IPainterDocumentController *docContr, QObject *parent)
    : BaseUndoableCommand(stack, parent)
    , m_docContr(docContr)
    , m_layer(nullptr)
    , m_newSymbol(nullptr)
    , m_oldSymbol(nullptr)
{
    setText("layer symbol changing");
}

void ChangeLayerSymbolCommand::setLayer(FeatureLayer *layer)
{
    m_layer = layer;
}

void ChangeLayerSymbolCommand::setNewSymbol(const ISymbol *newSymbol)
{
    m_newSymbol.reset(newSymbol->clone());
}

//------------------------------------------------------------------------------
void ChangeLayerSymbolCommand::redo()
{
    if (m_oldSymbol == nullptr)
    {
        m_oldSymbol.reset(m_layer->renderer()->symbol()->clone());
    }
    m_layer->renderer()->setSymbol(m_newSymbol->clone());
    IPainterDocument *doc = m_docContr->document();
    IMap* map = doc->map();
    map->refresh();
}

//------------------------------------------------------------------------------
void ChangeLayerSymbolCommand::undo()
{
    m_layer->renderer()->setSymbol(m_oldSymbol->clone());

    IPainterDocument *doc = m_docContr->document();
    IMap* map = doc->map();
    map->refresh();
}

//------------------------------------------------------------------------------

