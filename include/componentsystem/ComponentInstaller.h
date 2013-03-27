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

#ifndef COMPONENTINSTALLER_H
#define COMPONENTINSTALLER_H

#include "componentsystem/componentsystem_global.h"
#include "componentsystem/DependenciesSolvingResult.h"

#include <QtCore/QString>

class DirectoryComponentProvider;
class IComponent;

/*!
 * @brief
 * @details
 */
class COMP_API ComponentInstaller
{
public:
    ComponentInstaller(const QString &sourceDirectory);

    const QString &installDirectory() const;
    void setInstallDirectory(const QString &destinationDirectory);

    void addExistedComponent(const IComponent *component);

    void addDefinitionToInstall(const QString &definitionPath);
    void addDefinitionsToInstall(const QStringList &definitionPathes);

    DependenciesSolvingResult install();

    QStringList installedComponentPathes() const;

protected:
    virtual DirectoryComponentProvider *createProvider(const QString &sourceDirectory);

private:
    QString m_sourceDirectory;
};

#endif // COMPONENTINSTALLER_H
