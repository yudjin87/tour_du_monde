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

#include "BootloaderBase.h"

#include <logging/TextLogger.h>
#include <componentsystem/ComponentDependencies.h>
#include <componentsystem/ComponentManager.h>
#include <componentsystem/ComponentProvider.h>
#include <utils/ServiceLocator.h>

#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
BootloaderBase::BootloaderBase()
    : m_componentManager(nullptr)
    , m_componentProvider(nullptr)
    , m_logger(nullptr)
    , m_serviceLocator(nullptr)
    , m_mainWindow(nullptr)
    , m_alreadyRunned(false)
{
}

//------------------------------------------------------------------------------
BootloaderBase::~BootloaderBase()
{
    delete m_componentManager;
    m_componentManager = nullptr;

    delete m_componentProvider;
    m_componentProvider = nullptr;

    delete m_logger;
    m_logger = nullptr;

    delete m_serviceLocator;
    m_serviceLocator = nullptr;

    delete m_mainWindow;
    m_mainWindow = nullptr;
}

//------------------------------------------------------------------------------
void BootloaderBase::run()
{
    if (m_alreadyRunned)
        return;

    _run();

    m_alreadyRunned = true;
}

//------------------------------------------------------------------------------
IServiceLocator *BootloaderBase::serviceLocator() const
{
    return m_serviceLocator;
}

//------------------------------------------------------------------------------
void BootloaderBase::_configureComponentManager()
{
}

//------------------------------------------------------------------------------
void BootloaderBase::_configureComponentProvider()
{
}

//------------------------------------------------------------------------------
IComponentManager *BootloaderBase::_createComponentManager()
{
    return new ComponentManager(new ComponentDependencies(), *m_logger);
}

//------------------------------------------------------------------------------
IComponentProvider *BootloaderBase::_createComponentProvider()
{
    return new ComponentProvider();
}

//------------------------------------------------------------------------------
ILogger *BootloaderBase::_createLogger()
{
    static QTextStream text(stdout);
    return new TextLogger(text);
}

//------------------------------------------------------------------------------
IServiceLocator *BootloaderBase::_createServiceLocator()
{
    return new ServiceLocator();
}

//------------------------------------------------------------------------------
QMainWindow *BootloaderBase::_createMainWindow()
{
    return new QMainWindow();
}

//------------------------------------------------------------------------------
void BootloaderBase::_initialiseComponentProvider()
{
}

//------------------------------------------------------------------------------
