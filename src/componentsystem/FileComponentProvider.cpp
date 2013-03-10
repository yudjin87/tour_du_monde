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

#include "FileComponentProvider.h"
#include "XmlDefinitionParser.h"
#include "ProxyComponent.h"

#include <QtCore/QFile>
#include <QtCore/QFileInfoList>
#include <QtCore/QScopedPointer>

//------------------------------------------------------------------------------
typedef QScopedPointer<IDefinitionParser> IDefinitionParserPtr;

//------------------------------------------------------------------------------
FileComponentProvider::FileComponentProvider(QObject *parent)
    : ComponentProvider(parent)
    , m_path("")
    , mp_lastLoadedComponent(nullptr)
{
}

//------------------------------------------------------------------------------
FileComponentProvider::FileComponentProvider(const QString &path, QObject *parent)
    : ComponentProvider(parent)
    , m_path("")
    , mp_lastLoadedComponent(nullptr)
{
    setPath(path);
}

//------------------------------------------------------------------------------
FileComponentProvider::~FileComponentProvider()
{
}

//------------------------------------------------------------------------------
void FileComponentProvider::setPath(const QString &path)
{
    QFileInfo directoryToComponents(path);
    if (!directoryToComponents.isFile())
        return;

    m_path = path;
}

//------------------------------------------------------------------------------
const QString &FileComponentProvider::path() const
{
    return m_path;
}

//------------------------------------------------------------------------------
IComponent *FileComponentProvider::lastLoadedComponent() const
{
    return mp_lastLoadedComponent;
}

//------------------------------------------------------------------------------
IComponent *FileComponentProvider::loadComponent()
{
    if (m_path.isEmpty())
        return nullptr;

    IDefinitionParserPtr parser(createParser());
    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly))
        return nullptr;

    if (!parser->read(&file))
        return nullptr;

    ProxyComponent *proxy = createProxy();
    proxy->setDefinitionLocation(m_path);
    if (!proxy->initialize(*parser.data())) {
        delete proxy;
        return nullptr;
    }

    mp_lastLoadedComponent = proxy;
    registerComponent(proxy);

    return proxy;
}

//------------------------------------------------------------------------------
bool FileComponentProvider::_initialize()
{
    IComponent *loadedComponent = loadComponent();
    return loadedComponent != nullptr;
}

//------------------------------------------------------------------------------
IDefinitionParser *FileComponentProvider::createParser()
{
    return new XmlDefinitionParser();
}

//------------------------------------------------------------------------------
ProxyComponent *FileComponentProvider::createProxy()
{
    return new ProxyComponent();
}

//------------------------------------------------------------------------------
