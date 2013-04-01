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

#ifndef DIRECTORYWATCHINGCOMPONENTPROVIDER_H
#define DIRECTORYWATCHINGCOMPONENTPROVIDER_H

#include "componentsystem/componentsystem_global.h"
#include "componentsystem/ComponentProvider.h"
#include "componentsystem/IDirectoryComponentProvider.h"

class IDirectoryComponentProvider;
class QFileSystemWatcher;

/*!
 * @brief
 * @details
 */
class COMP_API DirectoryWatchingComponentProvider : public ComponentProvider
{
    Q_OBJECT
public:
    DirectoryWatchingComponentProvider(IDirectoryComponentProvider *provider, QObject *parent = nullptr);
    DirectoryWatchingComponentProvider(const QString &path, QObject *parent = nullptr);
    DirectoryWatchingComponentProvider(const QString &path, const QString &definitionExtension, QObject *parent = nullptr);

    ~DirectoryWatchingComponentProvider();

    const IDirectoryComponentProvider *provider() const;

    const QFileSystemWatcher *watcher() const;

signals:
    void newComponentsDiscovered(const QList<IComponent *> &components);

protected:
    virtual QFileSystemWatcher *createWatcher() const;

    /*!
     * @details
     *   Initializes the IDirectoryComponentProvider and starts watch for
     *   its path for changes.
     *
     *   Returns provider's initialization result.
     */
    bool _initialize();

private slots:
    void onDirectoryChanged(const QString &path);

private:
    IDirectoryComponentProvider *mp_provider;
    QFileSystemWatcher *mp_watcher;
};

#endif // DIRECTORYWATCHINGCOMPONENTPROVIDER_H
