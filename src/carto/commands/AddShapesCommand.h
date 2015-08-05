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
#include <geodatabase/IShapeFileWorkspaceFactory.h>
#include <carousel/commands/BaseUndoableCommand.h>

#include <QtCore/QStringList>
#include <memory>

class ITourDeMondeDocumentController;
class AbstractLayer;

class CARTO_API AddShapesCommand : public BaseUndoableCommand
{
    Q_OBJECT
public:
    AddShapesCommand(IUndoStack *stack, ITourDeMondeDocumentController *docContr, IShapeFileWorkspaceFactory* factory, QObject* parent = nullptr);
    ~AddShapesCommand();

    void addShapeFiles(const QStringList &files);

    void redo() override;
    void undo() override;

private:
    ITourDeMondeDocumentController *m_docContr;
    IShapeFileWorkspaceFactory *m_factory;
    QStringList m_files;
    QList<AbstractLayer*> m_addedLayers;
};

