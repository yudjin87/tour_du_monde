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

#include <carousel/commands/InstallComponentsCommand.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtCore/QCoreApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMainWindow>

InstallComponentsOperation::InstallComponentsOperation()
    : Operation("Install new")
    , m_serviceLocator(nullptr)
{
    setIcon(QIcon(":/componentSystemUi/images/install_component.png"));
    setIconVisibleInMenu(true);
}

void InstallComponentsOperation::execute()
{
    QFileDialog fileDialog(m_serviceLocator->locate<QMainWindow>(), "Install component");
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setNameFilter("Components (*.definition)"); // TODO: get from the app settings
    fileDialog.setDirectory(QCoreApplication::applicationDirPath() + "/externalSource");  // TODO: get last selected directory from settings
    if (!fileDialog.exec())
        return;

    QFileInfo selectedFile(fileDialog.selectedFiles().first());

    InstallComponentsCommand* command = m_serviceLocator->buildInstance<InstallComponentsCommand>();
    command->setSourceDirectoryPath(selectedFile.absolutePath());

    for (const QString &fileName : fileDialog.selectedFiles())
        command->addDefinitionPath(fileName);

    command->pushToStack();
}

void InstallComponentsOperation::initialize(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
}

