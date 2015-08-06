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

#include <carto/commands/ChangeLayerStyleCommand.h>
#include <carto/IMap.h>
#include <carto/FeatureLayer.h>
#include <carto/ITourDuMondeDocument.h>
#include <carto/ITourDuMondeDocumentController.h>
#include <carto/IFeatureRenderer.h>

ChangeLayerStyleCommand::ChangeLayerStyleCommand(IUndoStack *stack, ITourDuMondeDocumentController *docContr, QObject *parent)
    : BaseUndoableCommand(stack, parent)
    , m_docContr(docContr)
    , m_layer(nullptr)
    , m_newRenderer(nullptr)
    , m_oldRenderer(nullptr)
{
    setText("layer style changing");
}

void ChangeLayerStyleCommand::setLayer(FeatureLayer *layer)
{
    m_layer = layer;
}

void ChangeLayerStyleCommand::setNewRenderer(const IFeatureRenderer *renderer)
{
    m_newRenderer.reset(renderer->clone());
}

void ChangeLayerStyleCommand::redo()
{
    if (m_oldRenderer == nullptr)
    {
        m_oldRenderer.reset(m_layer->renderer()->clone());
    }
    m_layer->setRenderer(m_newRenderer->clone());
    ITourDuMondeDocument *doc = m_docContr->document();
    IMap* map = doc->map();
    map->refresh();
}

void ChangeLayerStyleCommand::undo()
{
    m_layer->setRenderer(m_oldRenderer->clone());

    ITourDuMondeDocument *doc = m_docContr->document();
    IMap* map = doc->map();
    map->refresh();
}


