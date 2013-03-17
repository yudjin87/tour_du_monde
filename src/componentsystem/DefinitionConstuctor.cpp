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

#include "DefinitionConstuctor.h"

#include "IComponentDefinition.h"
#include "IDefinitionParser.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

//------------------------------------------------------------------------------
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
DefinitionConstuctor::DefinitionConstuctor()
{
}

//------------------------------------------------------------------------------
DefinitionConstuctor::~DefinitionConstuctor()
{
}

//------------------------------------------------------------------------------
bool DefinitionConstuctor::construct(IComponentDefinition *definition, const IDefinitionParser *parser)
{
    QString name = parser->componentName();
    if (name.trimmed().isEmpty())
        return false;

    definition->setComponentName(name);
    definition->setDescription(parser->description());
    definition->setProductName(parser->productName());

    const QString &componentLocation = parser->componentLocation().trimmed().isEmpty()
            ? name
            : parser->componentLocation();

    // Get the correct library file name, e.g. libComponent.so or
    // Component.dll
    QFileInfo fileInfo(componentLocation);
    QString fileDir = fileInfo.filePath().replace(fileInfo.fileName(), "");
    QString filePath = libraryPattern.arg(fileDir).arg(fileInfo.fileName());
    definition->setComponentLocation(filePath);

    foreach(const QString &parentName, parser->parents())
        definition->addParent(parentName);

    return true;
}

//------------------------------------------------------------------------------
