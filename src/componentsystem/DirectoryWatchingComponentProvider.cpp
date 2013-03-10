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

#include "DirectoryWatchingComponentProvider.h"
#include "DirectoryComponentProvider.h"

#include <QtCore/QFileSystemWatcher>

//------------------------------------------------------------------------------
DirectoryWatchingComponentProvider::DirectoryWatchingComponentProvider(IDirectoryComponentProvider *provider, QObject *parent)
    : ComponentProvider(parent)
    , mp_provider(provider)
    , mp_watcher(nullptr)
{
    Q_ASSERT(provider != nullptr);
}

//------------------------------------------------------------------------------
DirectoryWatchingComponentProvider::DirectoryWatchingComponentProvider(const QString &path, QObject *parent)
    : ComponentProvider(parent)
    , mp_provider(new DirectoryComponentProvider(path, this))
    , mp_watcher(nullptr)
{
}

//------------------------------------------------------------------------------
DirectoryWatchingComponentProvider::DirectoryWatchingComponentProvider(const QString &path, const QString &definitionExtension, QObject *parent)
    : ComponentProvider(parent)
    , mp_provider(new DirectoryComponentProvider(path, definitionExtension, this))
    , mp_watcher(nullptr)
{
}

//------------------------------------------------------------------------------
DirectoryWatchingComponentProvider::~DirectoryWatchingComponentProvider()
{
    delete mp_provider;
    mp_provider = nullptr;

    delete mp_watcher;
    mp_watcher = nullptr;
}

//------------------------------------------------------------------------------
const IDirectoryComponentProvider *DirectoryWatchingComponentProvider::provider() const
{
    return mp_provider;
}

//------------------------------------------------------------------------------
const QFileSystemWatcher *DirectoryWatchingComponentProvider::watcher() const
{
    return mp_watcher;
}

//------------------------------------------------------------------------------
bool DirectoryWatchingComponentProvider::_initialize()
{
    bool result = mp_provider->initialize();

    mp_watcher = createWatcher();
    mp_watcher->addPath(mp_provider->path());

    connect(mp_watcher, SIGNAL(directoryChanged(const QString &)), SLOT(onDirectoryChanged(const QString &)));

    return result;
}

//------------------------------------------------------------------------------
QFileSystemWatcher *DirectoryWatchingComponentProvider::createWatcher() const
{
    return new QFileSystemWatcher();
}

//------------------------------------------------------------------------------
void DirectoryWatchingComponentProvider::onDirectoryChanged(const QString &path)
{
    Q_UNUSED(path)

    const QVector<IComponent *> &newComponetns = mp_provider->update();
    if (!newComponetns.isEmpty())
        emit newComponentsDiscovered(newComponetns);
}

//------------------------------------------------------------------------------
