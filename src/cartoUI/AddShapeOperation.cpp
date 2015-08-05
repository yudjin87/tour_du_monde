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

#include "AddShapeOperation.h"
#include <carto/commands/AddShapesCommand.h>

#include <carousel/utils/IServiceLocator.h>

#include <QtCore/QCoreApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMainWindow>

AddShapeOperation::AddShapeOperation()
    : Operation("Open shape")
    , m_serviceLocator(nullptr)
{
    setIcon(QIcon(":/cartoUI/images/add.png"));
    setIconVisibleInMenu(true);
}

void AddShapeOperation::execute()
{
    QFileDialog fileDialog(m_serviceLocator->locate<QMainWindow>(), "Open shape");
    fileDialog.setNameFilter("Shape Files (*.shp)");
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setDirectory(QCoreApplication::applicationDirPath() + "/data");  // TODO: get last selected directory from settings
    if (!fileDialog.exec())
        return;

    AddShapesCommand *addShapesCommand = m_serviceLocator->buildInstance<AddShapesCommand>();
    addShapesCommand->addShapeFiles(fileDialog.selectedFiles());
    addShapesCommand->pushToStack();
}

void AddShapeOperation::initialize(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
}

