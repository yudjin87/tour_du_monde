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

#include "ProxyComponent.h"

#include "ComponentDefinition.h"
#include "ComponentLoader.h"
#include "IDefinitionParser.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

#ifdef Q_OS_WIN32
static const QString libraryPattern("%1%2.dll");
#endif // Q_WS_WIN
#ifdef Q_OS_MAC
static const QString libraryPattern("%1lib%2.dylib");
#endif // Q_WS_MAC
#ifdef Q_OS_LINUX
static const QString libraryPattern("%1lib%2.so");
#endif // Q_WS_X11


//------------------------------------------------------------------------------
ProxyComponent::ProxyComponent(QObject *parent)
    : BaseComponent("Undefined_ProxyComponent", parent)
    , mp_loader(new ComponentLoader())
    , mp_component(nullptr)
    , m_initialized(false)
{
}

//------------------------------------------------------------------------------
ProxyComponent::ProxyComponent(IComponentLoader *loader, QObject *parent)
    : BaseComponent("Undefined_ProxyComponent", parent)
    , mp_loader(loader)
    , mp_component(nullptr)
    , m_initialized(false)
{
}

//------------------------------------------------------------------------------
void *ProxyComponent::getExtension(const QString &i_byTypeId) const
{
    if (mp_component == nullptr)
        return nullptr;

    return mp_component->getExtension(i_byTypeId);
}

//------------------------------------------------------------------------------
ProxyComponent::~ProxyComponent()
{
    delete mp_loader;
    mp_loader = nullptr;
}

//------------------------------------------------------------------------------
IComponentDefinition *ProxyComponent::definition() const
{
    return mp_definition;
}

//------------------------------------------------------------------------------
const QString &ProxyComponent::name() const
{
    return BaseComponent::name();
}

//------------------------------------------------------------------------------
bool ProxyComponent::initialize(const IDefinitionParser &parser)
{
    if (mp_loader == nullptr)
        return false;

    m_name = parser.componentName();
    if (m_name.trimmed().isEmpty())
        return false;

    setObjectName(m_name);

    mp_definition->setDescription(parser.description());
    mp_definition->setProductName(parser.productName());

    const QString &componentLocation = parser.componentLocation().trimmed().isEmpty()
            ? m_name
            : parser.componentLocation();

    // Get the correct library file name, e.g. libComponent.so or
    // Component.dll
    QFileInfo fileInfo(componentLocation);
    QString fileDir = fileInfo.filePath().replace(fileInfo.fileName(), "");
    QString filePath = libraryPattern.arg(fileDir).arg(fileInfo.fileName());

    // Get the absolute library file name, using definition's location
    // as a pivot for relative component path
    QFileInfo definitionFileName(m_definitionLocation);
    QDir definitionDirPath(definitionFileName.absoluteDir());
    QString libraryAbsolutePath = definitionDirPath.absoluteFilePath(filePath);
    QString cleanPath = QDir::cleanPath(libraryAbsolutePath);

    // Library file should exist and should be readable
    QFileInfo checkFile(cleanPath);
    if (!checkFile.isReadable())
        return false;

    mp_definition->setComponentLocation(cleanPath);
    mp_loader->setFileName(cleanPath);
    foreach(const QString &parentName, parser.parents())
        mp_definition->addParent(parentName);

    mp_definition->loadAvailability();

    m_initialized = true;

    return true;
}

//------------------------------------------------------------------------------
IComponent *ProxyComponent::loadedComponent() const
{
    return mp_component;
}

//------------------------------------------------------------------------------
void ProxyComponent::setDefinitionLocation(const QString &definitionLocation)
{
    m_definitionLocation = definitionLocation;
}

//------------------------------------------------------------------------------
void ProxyComponent::_onShutdown()
{
    mp_component->shutdown();
    bool result = mp_loader->deleteInstance();
    Q_ASSERT(result);

    mp_component = nullptr;
}

//------------------------------------------------------------------------------
bool ProxyComponent::_onStartup(QObject *ip_initData)
{
    if (!m_initialized)
        return false;

    if (mp_loader == nullptr)
        return false;

    if (!mp_loader->load())
        return false;

    mp_component = mp_loader->instance();

    if (mp_component == nullptr)
        return false;

    return mp_component->startup(ip_initData);
}

//------------------------------------------------------------------------------
