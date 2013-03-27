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

//------------------------------------------------------------------------------
ComponentInstaller::ComponentInstaller(const QString &sourceDirectory)
    : m_sourceDirectory(sourceDirectory)
{
}

//------------------------------------------------------------------------------
const QString &ComponentInstaller::installDirectory() const
{
    return m_sourceDirectory;
}

//------------------------------------------------------------------------------
void ComponentInstaller::setInstallDirectory(const QString &destinationDirectory)
{
    Q_UNUSED(destinationDirectory)
}

//------------------------------------------------------------------------------
void ComponentInstaller::addExistedComponent(const IComponent *component)
{
    Q_UNUSED(component)
}

//------------------------------------------------------------------------------
void ComponentInstaller::addDefinitionToInstall(const QString &definitionPath)
{
    Q_UNUSED(definitionPath)
}

//------------------------------------------------------------------------------
void ComponentInstaller::addDefinitionsToInstall(const QStringList &definitionPathes)
{
    Q_UNUSED(definitionPathes)
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentInstaller::install()
{
    return DependenciesSolvingResult();
}

//------------------------------------------------------------------------------
QStringList ComponentInstaller::installedComponentPathes() const
{
    return QStringList();
}

//------------------------------------------------------------------------------
DirectoryComponentProvider *ComponentInstaller::createProvider(const QString &sourceDirectory)
{
    Q_UNUSED(sourceDirectory)
    return nullptr;
}

//------------------------------------------------------------------------------
