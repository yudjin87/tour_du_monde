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
    , m_inputInterceptor(nullptr)
    , m_componentConfigurationDelegate(new CarouselComponentConfigurationDelegate())
    , m_componentManager(nullptr)
    , m_activeTool(nullptr)
    , m_catalogs(nullptr)
    , m_mainWindow(nullptr)
{
    setParent(parent);

    m_mainWindow = i_application.serviceLocator().locate<QMainWindow>();
    assert(m_mainWindow != nullptr);

    m_componentManager = i_application.serviceLocator().locate<IComponentManager>();
    assert(m_componentManager != nullptr);

    m_catalogs = new Catalogs(*m_mainWindow, &i_application);

    connect(m_componentManager, SIGNAL(componentStarted(IComponent *)),
            SLOT(onComponentStartedUp(IComponent *)));

    connect(m_componentManager, SIGNAL(componentAboutToShutDown(IComponent *)),
            SLOT(onComponentAboutToShutDown(IComponent *)));
}

//------------------------------------------------------------------------------
CarouselInteractionService::~CarouselInteractionService()
{
    saveUiState();

    delete m_catalogs;
    m_catalogs = nullptr;
    delete m_inputInterceptor;
    m_inputInterceptor = nullptr;
    delete m_componentConfigurationDelegate;
    m_componentConfigurationDelegate = nullptr;

    m_componentManager = nullptr;
    m_mainWindow = nullptr;
}

//------------------------------------------------------------------------------
ITool *CarouselInteractionService::activeTool()
{
    return m_activeTool;
}

//------------------------------------------------------------------------------
ICatalogs &CarouselInteractionService::catalogs()
{
    return const_cast<ICatalogs &>(static_cast<const CarouselInteractionService &>(*this).catalogs());
}

//------------------------------------------------------------------------------
const ICatalogs &CarouselInteractionService::catalogs() const
{
    return *m_catalogs;
}

//------------------------------------------------------------------------------
IComponentConfigurationDelegate *CarouselInteractionService::configurationDelegate()
{
    return m_componentConfigurationDelegate;
}

//------------------------------------------------------------------------------
IInputInterceptor *CarouselInteractionService::inputInterceptor()
{
    return m_inputInterceptor;
}

//------------------------------------------------------------------------------
QMainWindow &CarouselInteractionService::mainWindow()
{
    return *m_mainWindow;
}

//------------------------------------------------------------------------------
void CarouselInteractionService::resetUi()
{
    if (m_componentConfigurationDelegate == nullptr)
        return;

    foreach(IComponent *comp, m_componentManager->components()) {
        m_componentConfigurationDelegate->deconfigure(comp, *m_catalogs);
        m_componentConfigurationDelegate->configure(comp, *m_catalogs, m_app);
    }
}

//------------------------------------------------------------------------------
void CarouselInteractionService::setActiveTool(ITool *activeTool)
{
    if (activeTool != nullptr) {
        QObject *tool = dynamic_cast<QObject *>(activeTool);
        Q_ASSERT(tool != nullptr);
        this->connect(tool, SIGNAL(executingStopped()), SLOT(onToolExecutingStopped()));
    }

    if (m_activeTool != nullptr)
        m_activeTool->stopExecuting();

    if (m_inputInterceptor != nullptr)
        m_inputInterceptor->setReceiver(activeTool);

    m_activeTool = activeTool;
}

//------------------------------------------------------------------------------
void CarouselInteractionService::setConfigurationDelegate(IComponentConfigurationDelegate *configurationDelegate)
{
    if (m_componentConfigurationDelegate != nullptr)
        delete m_componentConfigurationDelegate;

    m_componentConfigurationDelegate = configurationDelegate;
}

//------------------------------------------------------------------------------
void CarouselInteractionService::setInputInterceptor(IInputInterceptor *inputInterceptor)
{
    if (m_inputInterceptor != nullptr)
        delete m_inputInterceptor;

    if (inputInterceptor != nullptr)
        inputInterceptor->setReceiver(m_activeTool);

    m_inputInterceptor = inputInterceptor;

}

//------------------------------------------------------------------------------
void CarouselInteractionService::saveUiState(int version /*= 0*/)
{
    QSettings settings;
    settings.setValue(m_mainWindow->objectName() + "/state", m_mainWindow->saveState(version));
    settings.setValue(m_mainWindow->objectName() +"/geometry", m_mainWindow->saveGeometry());
}

//------------------------------------------------------------------------------
void CarouselInteractionService::loadUiState(int version /* = 0*/)
{
    QSettings settings;
    m_mainWindow->restoreState(settings.value(m_mainWindow->objectName() +"/state").toByteArray(), version);
    m_mainWindow->restoreGeometry(settings.value(m_mainWindow->objectName() +"/geometry").toByteArray());
}

//------------------------------------------------------------------------------
void CarouselInteractionService::onComponentStartedUp(IComponent *component)
{
    if (m_componentConfigurationDelegate == nullptr)
        return;

    m_componentConfigurationDelegate->configure(component, *m_catalogs, m_app);

    // TODO:
    // Load only if configure returns true
    loadUiState();
}

//------------------------------------------------------------------------------
void CarouselInteractionService::onComponentAboutToShutDown(IComponent *component)
{
    if (m_componentConfigurationDelegate == nullptr)
        return;

    m_componentConfigurationDelegate->deconfigure(component, *m_catalogs);
}

//------------------------------------------------------------------------------
void CarouselInteractionService::onToolExecutingStopped()
{
    m_activeTool = nullptr;
    if (m_inputInterceptor != nullptr)
        m_inputInterceptor->setReceiver(nullptr);
}

//------------------------------------------------------------------------------
