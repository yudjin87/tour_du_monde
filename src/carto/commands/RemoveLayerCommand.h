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

#pragma once
#include <carto/carto_api.h>
#include <carousel/commands/BaseUndoableCommand.h>

#include <QtCore/QVector>
#include <QtCore/QPair>

class ITourDuMondeDocumentController;
class AbstractLayer;

class CARTO_API RemoveLayerCommand : public BaseUndoableCommand
{
    Q_OBJECT
public:
    RemoveLayerCommand(IUndoStack *stack, ITourDuMondeDocumentController *docContr, QObject* parent = nullptr);
    ~RemoveLayerCommand();

    void addLayer(AbstractLayer* layer);

    void redo() override;
    void undo() override;

private:
    ITourDuMondeDocumentController *m_docContr;
    QVector<AbstractLayer*> m_layersToRemove;

    QVector<QPair<int, AbstractLayer*>> m_layersToRestore;
};
