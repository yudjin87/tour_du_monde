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

#include "ComponentInstaller.h"
#include "ComponentDefinition.h"
#include "ComponentDependencies.h"
#include "IComponent.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QScopedPointer>
#include <QtCore/QtAlgorithms>

//------------------------------------------------------------------------------
static const char *DEFAULT_DIRECTORY = "./components";

typedef QScopedPointer<IComponentDependencies> IComponentDependenciesPtr;

//------------------------------------------------------------------------------
ComponentInstaller::ComponentInstaller(const QString &destinationDirectory)
    : m_destinationDirectory(destinationDirectory)
    , m_separateDirForComponent(true)
{
}

//------------------------------------------------------------------------------
ComponentInstaller::~ComponentInstaller()
{
    deleteComponents();
}

//------------------------------------------------------------------------------
QString ComponentInstaller::defaultInstallDir()
{
    return DEFAULT_DIRECTORY;
}

//------------------------------------------------------------------------------
bool ComponentInstaller::installComponentInSeparateDir() const
{
    return m_separateDirForComponent;
}

//------------------------------------------------------------------------------
void ComponentInstaller::setInstallComponentInSeparateDir(bool separate)
{
    m_separateDirForComponent = separate;
}

//------------------------------------------------------------------------------
void ComponentInstaller::addExistedComponent(IComponent *component)
{
    if (component == nullptr)
        return;

    m_existedComponents.push_back(component);
}

//------------------------------------------------------------------------------
QList<IComponent *> ComponentInstaller::existedComponents() const
{
    return m_existedComponents;
}

//------------------------------------------------------------------------------
const QString &ComponentInstaller::installDirectory() const
{
    return m_destinationDirectory;
}

//------------------------------------------------------------------------------
void ComponentInstaller::setInstallDirectory(const QString &destinationDirectory)
{
    m_destinationDirectory = destinationDirectory;
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentInstaller::tryToInstall(const QStringList &componentNames)
{
    deleteComponents();

    // Add existed componens to resolve componens for install
    IComponentDependenciesPtr dependencies(createDependencies());
    foreach(IComponent *comp, m_existedComponents)
        dependencies->addComponent(comp);

    QList<IComponent *> discoveredComponents = discoverComponents();

    // Select components to install from the all discovered components
    QList<IComponent *> toInstall;
    foreach(IComponent *comp, discoveredComponents) {
        dependencies->addComponent(comp);
        if (componentNames.contains(comp->name()))
            toInstall.push_back(comp);
    }

    // Find all parents for components to install
    DependenciesSolvingResult result = dependencies->completeListWithChildren(toInstall);
    if (!result.orphans().isEmpty()) {
        qDeleteAll(toInstall);
        return result;
    }

    // Return only components that have to be installed
    foreach(IComponent *comp, result.ordered()) {
        if (toInstall.contains(comp))
            continue;

        if (discoveredComponents.contains(comp))
            toInstall.push_back(comp);
    }

    // Delete unused components
    foreach(IComponent *comp, discoveredComponents) {
        if (!toInstall.contains(comp))
            delete comp;
    }

    m_componentsToInstall = toInstall;

    return DependenciesSolvingResult(m_componentsToInstall);
}

//------------------------------------------------------------------------------
QStringList ComponentInstaller::install()
{
    if (m_componentsToInstall.isEmpty())
        return QStringList();

    loadComponents(m_componentsToInstall);

    QStringList copiedDefinitions;
    foreach(IComponent *comp, m_componentsToInstall) {
        QString componentPath = createComponentDirectory(comp->name());

        QString definitionFileName = componentPath + QDir::separator() + comp->name() + ".definition";
        definitionFileName = QDir::toNativeSeparators(definitionFileName);
        QFile::copy(comp->definition()->definitionLocation(), definitionFileName);

        QFileInfo library(comp->definition()->componentLocation());
        QString libraryFileName = componentPath + QDir::separator() + library.fileName();
        QFile::copy(comp->definition()->componentLocation(), libraryFileName);

        copiedDefinitions.push_back(definitionFileName);
    }

    return copiedDefinitions;
}

//------------------------------------------------------------------------------
IComponentDependencies *ComponentInstaller::createDependencies()
{
    return new ComponentDependencies();
}

//------------------------------------------------------------------------------
QString ComponentInstaller::createComponentDirectory(const QString &componentName)
{
    QString componentDirectoryPath = m_destinationDirectory + QDir::separator();
    if (m_separateDirForComponent)
        componentDirectoryPath += componentName + QDir::separator();

    QDir dir(componentDirectoryPath);
    componentDirectoryPath = QDir::cleanPath(dir.absolutePath());

    dir.mkpath(componentDirectoryPath);

    return componentDirectoryPath;
}

//------------------------------------------------------------------------------
void ComponentInstaller::deleteComponents()
{
    qDeleteAll(m_componentsToInstall);
    m_componentsToInstall.clear();
}

//------------------------------------------------------------------------------
