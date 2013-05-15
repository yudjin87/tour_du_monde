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

#include "AddShapesCommand.h"

#include <carto/Map.h>
#include <carto/FeatureLayer.h>
#include <dom/IPainterDocument.h>
#include <dom/IPainterDocumentController.h>
#include <geodatabase/IFeatureWorkspace.h>
#include <geodatabase/IShapeFileWorkspaceFactory.h>
#include <geodatabase/IFeatureClass.h>
#include <utils/IServiceLocator.h>

#include <QtCore/QFileInfo>
#include <QtCore/QScopedPointer>

//------------------------------------------------------------------------------
typedef QScopedPointer<IShapeFileWorkspaceFactory> IShapeFileWorkspaceFactoryPtr;

//------------------------------------------------------------------------------
AddShapesCommand::AddShapesCommand(IServiceLocator *locator, QUndoCommand *parent)
    : QUndoCommand(parent)
    , m_locator(locator)
{
    setText("adding shape layer(s)");
}

//------------------------------------------------------------------------------
AddShapesCommand::~AddShapesCommand()
{
}

//------------------------------------------------------------------------------
void AddShapesCommand::addShapeFiles(const QStringList &files)
{
    m_files = files;
}

//------------------------------------------------------------------------------
void AddShapesCommand::redo()
{
    foreach(const QString &fileName, m_files) {
        QFileInfo shapeFile(fileName);
        const QString &workingDirectory = shapeFile.absolutePath();

        IPainterDocumentController* docController = m_locator->locate<IPainterDocumentController>();
        IPainterDocument *doc = docController->document();

        IShapeFileWorkspaceFactoryPtr factory(m_locator->buildInstance<IShapeFileWorkspaceFactory>());
        IFeatureWorkspace *workspace = (IFeatureWorkspace *) factory->openFromFile(workingDirectory);

        IFeatureClass *railwaysClass = workspace->openFeatureClass(fileName);
        FeatureLayer *railwaysLayer = new FeatureLayer();
        railwaysLayer->setFeatureClass(railwaysClass);
        doc->map().addLayer(railwaysLayer);
    }
}

//------------------------------------------------------------------------------
void AddShapesCommand::undo()
{

}

//------------------------------------------------------------------------------

