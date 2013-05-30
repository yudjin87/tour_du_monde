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

#include "AbstractApplication.h"

#include <booting/IBootloader.h>
#include <componentsystem/IComponentManager.h>
#include <utils/IServiceLocator.h>

#include <QtWidgets/QMainWindow>

//------------------------------------------------------------------------------
AbstractApplication::AbstractApplication(int &argc, char **argv, int flags)
    : QApplication(argc, argv, flags)
    , m_serviceLocator(nullptr)
{
}

//------------------------------------------------------------------------------
AbstractApplication::~AbstractApplication()
{
}

//------------------------------------------------------------------------------
int AbstractApplication::runApplicationLoop(IBootloader &bootloader)
{
    startLoadingSequence(bootloader);

    finishLoadingSequence();

    return QApplication::exec();
}

//------------------------------------------------------------------------------
void AbstractApplication::startLoadingSequence(IBootloader &bootloader)
{
    bootloader.run();
    m_serviceLocator = bootloader.serviceLocator();

    connect(this, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));
}

//------------------------------------------------------------------------------
void AbstractApplication::finishLoadingSequence()
{
    IComponentManager *componentManager = m_serviceLocator->locate<IComponentManager>();
    componentManager->startup();

    QMainWindow *mainWindow = m_serviceLocator->locate<QMainWindow>();
    mainWindow->show();
}

//------------------------------------------------------------------------------
void AbstractApplication::onAboutToQuit()
{
    IComponentManager *componentManager = m_serviceLocator->locate<IComponentManager>();
    componentManager->shutdown();
}

//------------------------------------------------------------------------------
