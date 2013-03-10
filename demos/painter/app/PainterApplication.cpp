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

#include "PainterApplication.h"

#include <booting/IBootloader.h>
#include <componentsystem/IComponentManager.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
PainterApplication::PainterApplication(int &argc, char **argv, int flags)
    : AbstractApplication(argc, argv, flags)
    , mp_serviceLocator(nullptr)
{
    connect(this, SIGNAL(aboutToQuit()), SLOT(cleanUp()));
}

//------------------------------------------------------------------------------
PainterApplication::PainterApplication(int &argc, char **argv, bool GUIenabled, int flags)
    : AbstractApplication(argc, argv, GUIenabled, flags)
    , mp_serviceLocator(nullptr)
{
    connect(this, SIGNAL(aboutToQuit()), SLOT(cleanUp()));
}

//------------------------------------------------------------------------------
PainterApplication::PainterApplication(int &argc, char **argv, QApplication::Type type, int flags)
    : AbstractApplication(argc, argv, type, flags)
    , mp_serviceLocator(nullptr)
{
    connect(this, SIGNAL(aboutToQuit()), SLOT(cleanUp()));
}

//------------------------------------------------------------------------------
PainterApplication::~PainterApplication()
{
    mp_serviceLocator = nullptr;
}

//------------------------------------------------------------------------------
int PainterApplication::run(IBootloader &bootloader)
{
    bootloader.run();
    mp_serviceLocator = bootloader.serviceLocator();

    IComponentManager *componentManager = mp_serviceLocator->locate<IComponentManager>();
    componentManager->startupAllComponents(this);

    QMainWindow *mainWindow = mp_serviceLocator->locate<QMainWindow>();
    mainWindow->show();

    return AbstractApplication::exec();
}

//------------------------------------------------------------------------------
IServiceLocator &PainterApplication::serviceLocator()
{
    return *mp_serviceLocator;
}

//------------------------------------------------------------------------------
void PainterApplication::cleanUp()
{
    IComponentManager *componentManager = mp_serviceLocator->locate<IComponentManager>();
    componentManager->shutdownAllComponents();
}

//------------------------------------------------------------------------------
