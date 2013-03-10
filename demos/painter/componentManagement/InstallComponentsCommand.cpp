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

#include <componentsystem/FileComponentProvider.h>
#include <componentsystem/IComponentManager.h>
#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtGui/QFileDialog>
#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
InstallComponentsCommand::InstallComponentsCommand()
    : Command("Install components")
    , m_app(nullptr)
{
    setIcon(QIcon(":/componentManagement/images/install_component.png"));
    setIconVisibleInMenu(true);
}

//------------------------------------------------------------------------------
void InstallComponentsCommand::execute()
{
    IServiceLocator &locator = m_app->serviceLocator();

    QSettings settings;
    QByteArray state = settings.value("Install_component_dialog").toByteArray();
    QFileDialog fileDialog(locator.locate<QMainWindow>(), "Install component");
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setFilter("Components (*.definition)");
    fileDialog.restoreState(state);
    if (!fileDialog.exec())
        return;

    state = fileDialog.saveState();
    settings.setValue("Install_component_dialog", state);

    QList<IComponent *> components;
    foreach(const QString &fileName, fileDialog.selectedFiles()) {
        FileComponentProvider provider(fileName);
        IComponent *component = provider.loadComponent();
        components.push_back(component);
    }

    IComponentManager *manager = locator.locate<IComponentManager>();
    manager->addComponents(components);
    manager->startupComponents(components, m_app);
}

//------------------------------------------------------------------------------
void InstallComponentsCommand::initialize(QObject *ip_startUpData)
{
    m_app = qobject_cast<AbstractApplication *>(ip_startUpData);
    if (m_app == nullptr)
        return;
}

//------------------------------------------------------------------------------
