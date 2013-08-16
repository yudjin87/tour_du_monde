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

#include "DirectoryInstaller.h"
#include "DirectoryComponentProvider.h"

#include <QtCore/QScopedPointer>

#include <carousel/logging/LoggerFacade.h>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("DirectoryInstaller");
}

//------------------------------------------------------------------------------
typedef QScopedPointer<DirectoryComponentProvider> DirectoryComponentProviderPtr;

//------------------------------------------------------------------------------
DirectoryInstaller::DirectoryInstaller(const QString &sourceDirectory, const QString &destinationDirectory)
    : ComponentInstaller(destinationDirectory)
    , m_sourceDirectory(sourceDirectory)
{
}

//------------------------------------------------------------------------------
DirectoryComponentProvider *DirectoryInstaller::createProvider(const QString &sourceDirectory)
{
    return new DirectoryComponentProvider(sourceDirectory);
}

//------------------------------------------------------------------------------
QList<IComponent *> DirectoryInstaller::discoverComponents()
{
    Log.d(QString("Discovering components in the \"%1\" direcotry...").arg(m_sourceDirectory));
    DirectoryComponentProviderPtr provider(createProvider(m_sourceDirectory));
    if (!provider->initialize())
        return QList<IComponent *>();

    return provider->components();
}

//------------------------------------------------------------------------------
QList<IComponent *> DirectoryInstaller::loadComponents(const QList<IComponent *> &componentsToInstall)
{
    return componentsToInstall;
}

//------------------------------------------------------------------------------
