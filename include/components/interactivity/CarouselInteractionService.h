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

#ifndef CAROUSELINTERACTIONSERVICE_H
#define CAROUSELINTERACTIONSERVICE_H

#include "IInteractionService.h"

class IComponent;
class IComponentManager;
class IServiceLocator;
class Catalogs;
class QMainWindow;

/*!
 * @brief
 *   This class is registered into the application services
 *   by the InteractionServiceComponent.
 *
 * @sa IInteractionService.
 */
class INTERACTIVITY_API CarouselInteractionService : public IInteractionService
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{CarouselInteractionService} using specified instances of the @a application,
     *   @a mainWindow and @a manager.
     */
    CarouselInteractionService(IServiceLocator *serviceLocator, QMainWindow *mainWindow, IComponentManager *manager, QObject *parent = nullptr);
    ~CarouselInteractionService();

    /*!
     * @details
     *   The currently selected tool in application. When not null,
     *   user's mouse and keyboard events from the central widget are
     *   sent to this tool by IInputDispatcher.
     * @sa setDispatcher, dispatcher
     */
    ITool *activeTool();

    /*!
     * @details
     *   Gets the catalog collection.
     */
    ICatalogs &catalogs();

    /*!
     * @details
     *   Gets the immutable catalog collection.
     */
    const ICatalogs &catalogs() const;

    /*!
     * @details
     *   Gets the current configuration delegate responsible for the configuring
     *   started up component.
     * @sa setConfigurationDelegate;
     */
    IComponentConfigurationDelegate *configurationDelegate();

    /*!
     * @details
     *   Gets the current user input dispatcher. Null by default.
     * @sa setDispatcher, activeTool
     */
    IInputDispatcher *dispatcher();

    /*!
     * @details
     *   Loads the geometry for top-level widgets and state of this mainwindow's
     *   toolbars and dockwidgets. The version number is compared with that
     *   is already stored (if any).
     *
     *   If they do not match, the mainwindow's state is left unchanged
     *
     *   It is after start up of the component to try to restore
     *   newly started component Ui.
     *
     * @sa saveUiState()
     */
    void loadUiState(int version = 0);

    /*!
     * @details
     *   Gets the application shell or main window.
     */
    QMainWindow &mainWindow();

    /*!
     * @details
     *   Uses IConfigurationDelegate to clear changes done by
     *   components (using IConfigurationDelegate::deconfigure())
     *   and configure components again.
     * @sa setConfigurationDelegate
     */
    void resetUi();

    /*!
     * @details
     *   Saves the current geometry for top-level widgets and state of this mainwindow's
     *   toolbars and dockwidgets. The version number is stored as part of the data.
     *
     *   It is called at least in the destructor of the service.
     *
     * @sa loadUiState()
     */
    void saveUiState(int version = 0);

    /*!
     * @details
     *   Deactivates current tool and sets the specified tool as active.
     * @sa activeTool
     */
    void setActiveTool(ITool *activeTool);

    /*!
     * @details
     *   Sets the configuration delegate responsible for the configuring
     *   started up component: IComponentConfigurationDelegate::configure() method
     *   will be binded to the IComponentManager::componentStarted() signal.
     *
     *   CarouselComponentConfigurationDelegate is used by default. Note, that
     *   CarouselInteractionService takes ownership of the configuration delegate.
     */
    void setConfigurationDelegate(IComponentConfigurationDelegate *configurationDelegate);

    /*!
     * @details
     *   Deletes the previous (if any) and sets the new input dispatcher in one of your GUI components.
     *   If you want user input would be sent to the active tool, use following snippet:
     * @code
     *   IInteractionService* interactionService = application->serviceLocator().locate<IInteractionService>();
     *   interactionService->setDispatcher(new InputDispatcher());
     *   interactionService->dispatcher()->setSender(interactionService->mainWindow.centralWidget());
     * @endcode
     *   @a Null by default. Note, that CarouselInteractionService takes ownership of the
     *   dispatcher.
     * @sa setDispatcher, activeTool
     */
    void setDispatcher(IInputDispatcher *dispatcher);

protected slots:
    /*!
     * @details
     *   Configures all started @a components using configuration delegate (if any).
     *   It also connects the onComponentStartedUp() slot to the manager's
     *   componentStarted() signal
     *   This slot is invoked when @a component manager started up.
     */
    void onComponentManagerStartedUp();

    /*!
     * @details
     *   Configures a @a component using configuration delegate (if any).
     *   This slot is invoked when @a component is started up.
     */
    void onComponentStartedUp(IComponent *component);

    /*!
     * @details
     *   Deconfigures a @a component using configuration delegate (if any).
     *   This slot is invoked when @a component is prepared for shut down.
     */
    void onComponentAboutToShutDown(IComponent *component);

    /*!
     * @details
     *   Saves UI state.
     *   This slot is invoked when @a component @a manager prepares for shut down.
     */
    void onComponentManagerAboutToShutDown();

    /*!
     * @details
     *   Sets active tool and receiver to nullptr to the current dispatcher (if any).
     *   This slot is invoked when @a active @a tool is stopped.
     */
    void onToolExecutingStopped();

    /*!
     * @details
     *   Sets active tool and receiver to nullptr to the current dispatcher (if any).
     *   This slot is invoked when @a active @a tool instance is deleted.
     */
    void onToolDeleted();

private:
    void makeConnections();
    bool configureComponent(IComponent *component);

private:
    IInputDispatcher *m_dispatcher;
    IComponentConfigurationDelegate *m_componentConfigurationDelegate;
    IComponentManager *m_componentManager;
    ITool *m_activeTool;
    Catalogs *m_catalogs;
    QMainWindow *m_mainWindow;
};

#endif // CAROUSELINTERACTIONSERVICE_H
