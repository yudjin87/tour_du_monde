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

#include "InstallComponentsOperation.h"

#include <componentsystemui/InstallComponentsCommand.h>
#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QFileDialog>
#include <QtGui/QMainWindow>
#include <QtGui/QUndoStack>

//------------------------------------------------------------------------------
InstallComponentsOperation::InstallComponentsOperation()
    : Operation("Install components")
    , m_app(nullptr)
{
    setIcon(QIcon(":/componentManagement/images/install_component.png"));
    setIconVisibleInMenu(true);
}

//------------------------------------------------------------------------------
void InstallComponentsOperation::execute()
{
    IServiceLocator &locator = m_app->serviceLocator();

    QFileDialog fileDialog(locator.locate<QMainWindow>(), "Install component");
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setFilter("Components (*.definition)"); // TODO: get from the app settings
    if (!fileDialog.exec())
        return;

    InstallComponentsCommand* command = locator.buildInstance<InstallComponentsCommand>();
    command->setSourceDirectoryPath(fileDialog.directory().absolutePath());

    foreach(const QString &fileName, fileDialog.selectedFiles())
        command->addDefinitionPath(fileName);

    QUndoStack *undo = locator.locate<QUndoStack>();
    undo->push(command);
}

//------------------------------------------------------------------------------
void InstallComponentsOperation::initialize(QObject *ip_startUpData)
{
    m_app = qobject_cast<AbstractApplication *>(ip_startUpData);
    if (m_app == nullptr)
        return;
}

//------------------------------------------------------------------------------
