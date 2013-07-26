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

#include <carousel/booting/IBootloader.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/utils/IServiceLocator.h>

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
    m_serviceLocator = startLoadingSequence(bootloader);
    finishLoadingSequence(m_serviceLocator);
    return QApplication::exec();
}

//------------------------------------------------------------------------------
void AbstractApplication::shutdownComponentManager(IComponentManager *componentManager)
{
    componentManager->shutdown();
}

//------------------------------------------------------------------------------
void AbstractApplication::startComponentManager(IComponentManager *componentManager)
{
    componentManager->startup();
}

//------------------------------------------------------------------------------
void AbstractApplication::showMainWindow(QMainWindow *mainWindow)
{
    mainWindow->show();
}

//------------------------------------------------------------------------------
IServiceLocator *AbstractApplication::startLoadingSequence(IBootloader &bootloader)
{
    bootloader.run();
    connect(this, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));
    return bootloader.serviceLocator();
}

//------------------------------------------------------------------------------
void AbstractApplication::finishLoadingSequence(IServiceLocator *serviceLocator)
{
    startComponentManager(serviceLocator->locate<IComponentManager>());
    showMainWindow(serviceLocator->locate<QMainWindow>());
}

//------------------------------------------------------------------------------
void AbstractApplication::onAboutToQuit()
{
    shutdownComponentManager(m_serviceLocator->locate<IComponentManager>());
    m_serviceLocator = nullptr;
}

//------------------------------------------------------------------------------
