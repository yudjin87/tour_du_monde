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

#include "InstallComponentsCommand.h"

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/DirectoryInstaller.h>
#include <carousel/componentsystem/FileComponentProvider.h>
#include <carousel/componentsystem/IComponent.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/utils/ObservableList.h>
#include <carousel/utils/FileUtils.h>

#include <QtCore/QFileInfo>
#include <QtCore/QDir>

//------------------------------------------------------------------------------
InstallComponentsCommand::InstallComponentsCommand(IComponentManager *manager, QUndoCommand *parent)
    : QUndoCommand(parent)
    , m_manager(manager)
    , m_sourceDirectoryPath("")
    , m_installPath("./installedComponents") // TODO: should be obtained from the app settings
    , m_addAfterInstallation(true)
    , m_startAfterInstallation(true)
{
    setText("installing new components");
}

//------------------------------------------------------------------------------
InstallComponentsCommand::~InstallComponentsCommand()
{
}

//------------------------------------------------------------------------------
void InstallComponentsCommand::addDefinitionPath(const QString &definitionPath)
{
    m_definitionFiles.push_back(definitionPath);
}

//------------------------------------------------------------------------------
void InstallComponentsCommand::setInstallPath(const QString &installPath)
{
    m_installPath = installPath;
}

//------------------------------------------------------------------------------
const QString &InstallComponentsCommand::installPath() const
{
    return m_installPath;
}

//------------------------------------------------------------------------------
void InstallComponentsCommand::setSourceDirectoryPath(const QString &sourceDirectoryPath)
{
    m_sourceDirectoryPath = sourceDirectoryPath;
}

//------------------------------------------------------------------------------
const QString &InstallComponentsCommand::sourceDirectoryPath() const
{
    return m_sourceDirectoryPath;
}

//------------------------------------------------------------------------------
bool InstallComponentsCommand::addComponentsAfterInstallation() const
{
    return m_addAfterInstallation;
}

//------------------------------------------------------------------------------
void InstallComponentsCommand::setAddComponentsAfterInstallation(bool start)
{
    m_addAfterInstallation = start;
}

//------------------------------------------------------------------------------
bool InstallComponentsCommand::startComponentsAfterInstallation() const
{
    return m_startAfterInstallation;
}

//------------------------------------------------------------------------------
void InstallComponentsCommand::setStartComponentsAfterInstallation(bool start)
{
    m_startAfterInstallation = start;
}

//------------------------------------------------------------------------------
bool InstallComponentsCommand::tryRedo()
{
    //TODO: implement me!
    return true;
}

//------------------------------------------------------------------------------
void InstallComponentsCommand::redo()
{
    if (!m_installedComponents.empty()) {
        // Redo after undo installing
        m_manager->startupComponents(m_installedComponents);
        return;
    }
    // Get component names from the files
    QStringList componentNames;
    foreach(const QString &fileName, m_definitionFiles) {
        QFileInfo definitionFile(fileName);
        componentNames.push_back(definitionFile.baseName());
    }

    // Add existed components
    DirectoryInstaller installer(m_sourceDirectoryPath, m_installPath);
    foreach(IComponent *comp, m_manager->components()) {
        installer.addExistedComponent(comp);
    }

    installer.tryToInstall(componentNames);
    QStringList installedDefinitionFiles = installer.install();

    if (!m_addAfterInstallation)
        return;

    // Startup installed components
    foreach(const QString &fileName, installedDefinitionFiles) {
        FileComponentProvider provider(fileName);
        IComponent *component = provider.loadComponent();
        if (m_manager->addComponent(component))
            m_installedComponents.push_back(component);
        else
            delete component;
    }

    if (!m_startAfterInstallation)
        return;

    m_manager->startupComponents(m_installedComponents);
}

//------------------------------------------------------------------------------
void InstallComponentsCommand::undo()
{
    m_manager->shutdownComponents(m_installedComponents);
}

//------------------------------------------------------------------------------
