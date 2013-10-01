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

#ifndef ICOMPONENTINSTALLER_H
#define ICOMPONENTINSTALLER_H

#include <carousel/carousel_global.h>
#include <carousel/componentsystem/DependenciesSolvingResult.h>

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>

class IComponent;
class DependenciesSolvingResult;

/*!
 * @brief
 * @details
 */
class CAROUSEL_API IComponentInstaller
{
public:
    IComponentInstaller(){}
    virtual ~IComponentInstaller(){}

    virtual bool installComponentInSeparateDir() const = 0;
    virtual void setInstallComponentInSeparateDir(bool separate) = 0;

    virtual const QString &installDirectory() const = 0;
    virtual void setInstallDirectory(const QString &destinationDirectory) = 0;

    virtual void addExistedComponent(IComponent *component) = 0;

    virtual QList<IComponent *> existedComponents() const = 0;

    virtual DependenciesSolvingResult tryToInstall(const QStringList &componentNames) = 0;

    virtual QStringList install() = 0;

private:
    Q_DISABLE_COPY(IComponentInstaller)
};

#endif // ICOMPONENTINSTALLER_H
