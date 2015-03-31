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

#pragma once
#include <carousel/componentsystem/ComponentInstaller.h>

class DirectoryComponentProvider;

/*!
 * @brief
 * @details
 */
class CAROUSEL_API DirectoryInstaller : public ComponentInstaller
{
public:
    DirectoryInstaller(const QString &sourceDirectory, const QString &destinationDirectory = ComponentInstaller::defaultInstallDir());

protected:
    virtual DirectoryComponentProvider *createProvider(const QString &sourceDirectory);

    /*!
     * @details
     *   Discovers components from the @a source @a directory using DirectoryComponentProvider.
     *
     *   The ComponentInstaller takes ownership for discovered components.
     */
    QList<IComponent *> discoverComponents() override;

    /*!
     * @details
     *   Since components already on the user's file system, just returns that list.
     */
    QList<IComponent *> loadComponents(const QList<IComponent *> &componentsToInstall) override;

private:
    QString m_sourceDirectory;
};

