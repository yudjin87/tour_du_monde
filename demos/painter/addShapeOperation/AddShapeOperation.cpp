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

#include "AddShapeOperation.h"

#include <carto/Map.h>
#include <carto/FeatureLayer.h>
#include <dom/IPainterDocument.h>
#include <dom/IPainterDocumentController.h>
#include <geodatabase/IFeatureWorkspace.h>
#include <geodatabase/IShapeFileWorkspaceFactory.h>
#include <geodatabase/IFeatureClass.h>

#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtGui/QFileDialog>
#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
AddShapeOperation::AddShapeOperation()
    : Operation("Open shape")
    , m_app(nullptr)
{
    setIcon(QIcon(":/core/images/add.png"));
    setIconVisibleInMenu(true);
}

//------------------------------------------------------------------------------
void AddShapeOperation::execute()
{
    IServiceLocator &locator = m_app->serviceLocator();

    QSettings settings;
    QByteArray state = settings.value("Open_shape_dialog").toByteArray();
    QFileDialog fileDialog(locator.locate<QMainWindow>(), "Open shape");
    fileDialog.setFilter("Shape Files (*.shp)");
    fileDialog.restoreState(state);
    if (!fileDialog.exec())
        return;

    state = fileDialog.saveState();
    settings.setValue("Open_shape_dialog", state);

    QDir workspaceLocation = fileDialog.directory();
    QString fileName = fileDialog.selectedFiles().first();


    IPainterDocumentController* docController = m_app->serviceLocator().locate<IPainterDocumentController>();
    IPainterDocument *doc = docController->document();

    IShapeFileWorkspaceFactory *factory = locator.buildInstance<IShapeFileWorkspaceFactory>();
    IFeatureWorkspace *workspace = (IFeatureWorkspace *) factory->openFromFile(workspaceLocation.absolutePath());
    IFeatureClass *railwaysClass = workspace->openFeatureClass(fileName);
    FeatureLayer *railwaysLayer = new FeatureLayer();
    railwaysLayer->setFeatureClass(railwaysClass);
    doc->map().addLayer(railwaysLayer);
}

//------------------------------------------------------------------------------
void AddShapeOperation::initialize(QObject *ip_startUpData)
{
    m_app = qobject_cast<AbstractApplication *>(ip_startUpData);
    if (m_app == nullptr)
        return;
}

//------------------------------------------------------------------------------
