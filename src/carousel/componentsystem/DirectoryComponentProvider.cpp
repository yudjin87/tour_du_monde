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

#include "DirectoryComponentProvider.h"
#include "ComponentProvider.h"
#include "FileComponentProvider.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QFileInfoList>
#include <QtCore/QScopedPointer>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("DirectoryComponentProvider");
}

//------------------------------------------------------------------------------
typedef QScopedPointer<FileComponentProvider> FileComponentProviderPtr;

//------------------------------------------------------------------------------
DirectoryComponentProvider::DirectoryComponentProvider(QObject *parent)
    : m_path("")
    , m_definitionExtension("*.definition")
    , m_flags(QDirIterator::Subdirectories)
    , m_filters(QDir::NoDotAndDotDot | QDir::Readable)
    , m_alreadyInit(false)
    , m_provider(new ComponentProvider())
{
    setParent(parent);
}

//------------------------------------------------------------------------------
DirectoryComponentProvider::DirectoryComponentProvider(const QString &path, QObject *parent)
    : m_path("")
    , m_definitionExtension("*.definition")
    , m_flags(QDirIterator::Subdirectories)
    , m_filters(QDir::NoDotAndDotDot | QDir::Readable | QDir::Files | QDir::AllDirs)
    , m_alreadyInit(false)
    , m_provider(new ComponentProvider())
{
    setParent(parent);
    setPath(path);
}

//------------------------------------------------------------------------------
DirectoryComponentProvider::DirectoryComponentProvider(const QString &path, const QString &definitionExtension, QObject *parent)
    : m_path("")
    , m_definitionExtension(definitionExtension)
    , m_flags(QDirIterator::Subdirectories)
    , m_filters(QDir::NoDotAndDotDot | QDir::Readable)
    , m_alreadyInit(false)
    , m_provider(new ComponentProvider())
{
    setParent(parent);
    setPath(path);
}

//------------------------------------------------------------------------------
DirectoryComponentProvider::~DirectoryComponentProvider()
{
    delete m_provider;
    m_provider = nullptr;
}

//------------------------------------------------------------------------------
QList<IComponent *> DirectoryComponentProvider::components() const
{
    return m_provider->components();
}

//------------------------------------------------------------------------------
bool DirectoryComponentProvider::initialize()
{
    if (m_alreadyInit)
        return true;

    m_alreadyInit = onInitialize();

    return m_alreadyInit;
}

//------------------------------------------------------------------------------
bool DirectoryComponentProvider::isInitialized() const
{
    return m_alreadyInit;
}

//------------------------------------------------------------------------------
void DirectoryComponentProvider::registerComponent(IComponent *component)
{
    m_provider->registerComponent(component);
}

//------------------------------------------------------------------------------
void DirectoryComponentProvider::setPath(const QString &path)
{
    QFileInfo directoryToComponents(path);
    if (!directoryToComponents.isDir())
        return;

    QDir dir(QCoreApplication::applicationDirPath());
    m_path =  dir.absoluteFilePath(path);
}

//------------------------------------------------------------------------------
void DirectoryComponentProvider::setExtension(const QString &definitionExtension)
{
    m_definitionExtension = definitionExtension;
}

//------------------------------------------------------------------------------
void DirectoryComponentProvider::setFilters(QDir::Filters filters)
{
    m_filters = filters;
}

//------------------------------------------------------------------------------
void DirectoryComponentProvider::setFlags(QDirIterator::IteratorFlags flags)
{
    m_flags = flags;
}

//------------------------------------------------------------------------------
const QString &DirectoryComponentProvider::path() const
{
    return m_path;
}

//------------------------------------------------------------------------------
const QString &DirectoryComponentProvider::extension() const
{
    return m_definitionExtension;
}


//------------------------------------------------------------------------------
QDirIterator::IteratorFlags DirectoryComponentProvider::flags() const
{
    return m_flags;
}

//------------------------------------------------------------------------------
QList<IComponent *> DirectoryComponentProvider::update()
{
    if (m_path.isEmpty())
        return QList<IComponent *>();

    QStringList nameFilters(m_definitionExtension);
    QDirIterator iterator(m_path, nameFilters, m_filters, m_flags);
    Log.d(QString("Looking for components in \"%1\"").arg(m_path));

    QList<IComponent *> discoveredComponents;
    while (iterator.hasNext()) {
        QString fileName = iterator.next();
        QFileInfo directoryToComponents(fileName);
        if (directoryToComponents.isDir())
            continue;

        if (m_processedFiles.contains(fileName))
            continue;

        FileComponentProviderPtr provider(createFileComponentProvider(fileName));
        if (!provider->initialize())
            continue;

        m_processedFiles.push_back(fileName);

        IComponent *loadedComponent = provider->lastLoadedComponent();
        discoveredComponents.push_back(loadedComponent);
        registerComponent(loadedComponent);
    }

    return discoveredComponents;
}

//------------------------------------------------------------------------------
QDir::Filters DirectoryComponentProvider::filters() const
{
    return m_filters;
}

//------------------------------------------------------------------------------
bool DirectoryComponentProvider::onInitialize()
{
    QList<IComponent *> discoveredComponents = update();
    return !discoveredComponents.empty();
}

//------------------------------------------------------------------------------
FileComponentProvider *DirectoryComponentProvider::createFileComponentProvider(const QString &definitionPath)
{
    return new FileComponentProvider(definitionPath);
}

//------------------------------------------------------------------------------
