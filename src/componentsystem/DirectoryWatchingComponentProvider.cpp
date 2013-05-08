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
    , m_provider(provider)
    , m_watcher(nullptr)
{
    Q_ASSERT(provider != nullptr);
}

//------------------------------------------------------------------------------
DirectoryWatchingComponentProvider::DirectoryWatchingComponentProvider(const QString &path, QObject *parent)
    : ComponentProvider(parent)
    , m_provider(new DirectoryComponentProvider(path, this))
    , m_watcher(nullptr)
{
}

//------------------------------------------------------------------------------
DirectoryWatchingComponentProvider::DirectoryWatchingComponentProvider(const QString &path, const QString &definitionExtension, QObject *parent)
    : ComponentProvider(parent)
    , m_provider(new DirectoryComponentProvider(path, definitionExtension, this))
    , m_watcher(nullptr)
{
}

//------------------------------------------------------------------------------
DirectoryWatchingComponentProvider::~DirectoryWatchingComponentProvider()
{
    delete m_provider;
    m_provider = nullptr;

    delete m_watcher;
    m_watcher = nullptr;
}

//------------------------------------------------------------------------------
const IDirectoryComponentProvider *DirectoryWatchingComponentProvider::provider() const
{
    return m_provider;
}

//------------------------------------------------------------------------------
const QFileSystemWatcher *DirectoryWatchingComponentProvider::watcher() const
{
    return m_watcher;
}

//------------------------------------------------------------------------------
bool DirectoryWatchingComponentProvider::onInitialize()
{
    bool result = m_provider->initialize();

    m_watcher = createWatcher();
    m_watcher->addPath(m_provider->path());

    connect(m_watcher, SIGNAL(directoryChanged(const QString &)), SLOT(onDirectoryChanged(const QString &)));

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

    const QList<IComponent *> &newComponetns = m_provider->update();
    if (!newComponetns.isEmpty())
        emit newComponentsDiscovered(newComponetns);
}

//------------------------------------------------------------------------------
