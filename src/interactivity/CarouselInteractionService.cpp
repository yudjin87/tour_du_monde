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

#include "CarouselInteractionService.h"

#include "Catalogs.h"
#include "CarouselComponentConfigurationDelegate.h"
#include "IInputInterceptor.h"
#include "ITool.h"

#include <framework/AbstractApplication.h>
#include <componentsystem/IComponent.h>
#include <componentsystem/IComponentManager.h>
#include <utils/IServiceLocator.h>
#include <utils/ObservableList.h>

#include <QtCore/QSettings>
#include <QtGui/QMainWindow>

#include <assert.h>
//------------------------------------------------------------------------------
CarouselInteractionService::CarouselInteractionService(AbstractApplication &i_application, QObject *parent /*= nullptr*/)
    : m_app(i_application)
    , mp_inputInterceptor(nullptr)
    , mp_componentConfigurationDelegate(new CarouselComponentConfigurationDelegate())
    , mp_componentManager(nullptr)
    , mp_activeTool(nullptr)
    , mp_catalogs(nullptr)
    , mp_mainWindow(nullptr)
{
    setParent(parent);

    mp_mainWindow = i_application.serviceLocator().locate<QMainWindow>();
    assert(mp_mainWindow != nullptr);

    mp_componentManager = i_application.serviceLocator().locate<IComponentManager>();
    assert(mp_componentManager != nullptr);

    mp_catalogs = new Catalogs(*mp_mainWindow, &i_application);

    connect(mp_componentManager, SIGNAL(componentStarted(IComponent *)),
            SLOT(onComponentStartedUp(IComponent *)));

    connect(mp_componentManager, SIGNAL(componentAboutToShutDown(IComponent *)),
            SLOT(onComponentAboutToShutDown(IComponent *)));
}

//------------------------------------------------------------------------------
CarouselInteractionService::~CarouselInteractionService()
{
    saveUiState();

    delete mp_catalogs;
    mp_catalogs = nullptr;
    delete mp_inputInterceptor;
    mp_inputInterceptor = nullptr;
    delete mp_componentConfigurationDelegate;
    mp_componentConfigurationDelegate = nullptr;

    mp_componentManager = nullptr;
    mp_mainWindow = nullptr;
}

//------------------------------------------------------------------------------
ITool *CarouselInteractionService::activeTool()
{
    return mp_activeTool;
}

//------------------------------------------------------------------------------
ICatalogs &CarouselInteractionService::catalogs()
{
    return const_cast<ICatalogs &>(static_cast<const CarouselInteractionService &>(*this).catalogs());
}

//------------------------------------------------------------------------------
const ICatalogs &CarouselInteractionService::catalogs() const
{
    return *mp_catalogs;
}

//------------------------------------------------------------------------------
IComponentConfigurationDelegate *CarouselInteractionService::configurationDelegate()
{
    return mp_componentConfigurationDelegate;
}

//------------------------------------------------------------------------------
IInputInterceptor *CarouselInteractionService::inputInterceptor()
{
    return mp_inputInterceptor;
}

//------------------------------------------------------------------------------
QMainWindow &CarouselInteractionService::mainWindow()
{
    return *mp_mainWindow;
}

//------------------------------------------------------------------------------
void CarouselInteractionService::resetUi()
{
    if (mp_componentConfigurationDelegate == nullptr)
        return;

    foreach(IComponent *comp, mp_componentManager->components()) {
        mp_componentConfigurationDelegate->deconfigure(comp, *mp_catalogs);
        mp_componentConfigurationDelegate->configure(comp, *mp_catalogs, m_app);
    }
}

//------------------------------------------------------------------------------
void CarouselInteractionService::setActiveTool(ITool *ip_activeTool)
{
    if (ip_activeTool != nullptr) {
        QObject *tool = dynamic_cast<QObject *>(ip_activeTool);
        Q_ASSERT(tool != nullptr);
        this->connect(tool, SIGNAL(executingStopped()), SLOT(onToolExecutingStopped()));
    }

    if (mp_activeTool != nullptr)
        mp_activeTool->stopExecuting();

    if (mp_inputInterceptor != nullptr)
        mp_inputInterceptor->setReceiver(ip_activeTool);

    mp_activeTool = ip_activeTool;
}

//------------------------------------------------------------------------------
void CarouselInteractionService::setConfigurationDelegate(IComponentConfigurationDelegate *ip_configurationDelegate)
{
    if (mp_componentConfigurationDelegate != nullptr)
        delete mp_componentConfigurationDelegate;

    mp_componentConfigurationDelegate = ip_configurationDelegate;
}

//------------------------------------------------------------------------------
void CarouselInteractionService::setInputInterceptor(IInputInterceptor *ip_inputInterceptor)
{
    if (mp_inputInterceptor != nullptr)
        delete mp_inputInterceptor;

    if (ip_inputInterceptor != nullptr)
        ip_inputInterceptor->setReceiver(mp_activeTool);

    mp_inputInterceptor = ip_inputInterceptor;

}

//------------------------------------------------------------------------------
void CarouselInteractionService::saveUiState(int version /*= 0*/)
{
    QSettings settings;
    settings.setValue(mp_mainWindow->objectName() + "/state", mp_mainWindow->saveState(version));
    settings.setValue(mp_mainWindow->objectName() +"/geometry", mp_mainWindow->saveGeometry());
}

//------------------------------------------------------------------------------
void CarouselInteractionService::loadUiState(int version /* = 0*/)
{
    QSettings settings;
    mp_mainWindow->restoreState(settings.value(mp_mainWindow->objectName() +"/state").toByteArray(), version);
    mp_mainWindow->restoreGeometry(settings.value(mp_mainWindow->objectName() +"/geometry").toByteArray());
}

//------------------------------------------------------------------------------
void CarouselInteractionService::onComponentStartedUp(IComponent *ip_component)
{
    if (mp_componentConfigurationDelegate == nullptr)
        return;

    mp_componentConfigurationDelegate->configure(ip_component, *mp_catalogs, m_app);

    // TODO:
    // Load only if configure returns true
    loadUiState();
}

//------------------------------------------------------------------------------
void CarouselInteractionService::onComponentAboutToShutDown(IComponent *ip_component)
{
    if (mp_componentConfigurationDelegate == nullptr)
        return;

    mp_componentConfigurationDelegate->deconfigure(ip_component, *mp_catalogs);
}

//------------------------------------------------------------------------------
void CarouselInteractionService::onToolExecutingStopped()
{
    mp_activeTool = nullptr;
    if (mp_inputInterceptor != nullptr)
        mp_inputInterceptor->setReceiver(nullptr);
}

//------------------------------------------------------------------------------
