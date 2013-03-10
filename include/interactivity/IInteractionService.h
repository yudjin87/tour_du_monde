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

#ifndef IINTERACTIVITYSERVICE_H
#define IINTERACTIVITYSERVICE_H

#include "interactivity_global.h"

#include <QtCore/QObject>

class ICatalogs;
class IComponentConfigurationDelegate;
class IInputInterceptor;
class ITool;
class QMainWindow;

/*!
 * @brief
 *   This service provides methods to configure application GUI
 *   like menus, commands, toolbars and other, and it is registered
 *   into the application services by the InteractionServiceComponent.
 * @details
 *   The IInteractionService interface is a starting point for many tasks
 *   one does with a application GUI. For example, use IInteractionService
 *   to obtain catalogs to add menus or commands; access the main window (eg,
 *   for getting central widget); specify active application tool to intercept
 *   the user actions (mouse move, mouse clicks, keys pressed).
 *
 *   The IInteractionService has a reference to the IComponentManager object,
 *   and it asks added components (if they register IInteractiveExtension) to register
 *   new menus, commands and toolbars into the catalogs. The IComponentConfigurationDelegate
 *   is used for it.
 *
 *   InteractiveServiceComponent registers this service in the application services,
 *   so you can get reference to IInteractionService the next way:
 * @code
 *   IInteractionService* interactiveService = application->serviceLocator().locate<IInteractionService>();
 * @endcode
 *   but make sure, that your component that used IInteractionService is a @a child for the
 *   InteractiveServiceComponent.
 * @sa IComponentDefinition::parents()
 */
class INTERACTIVITY_API IInteractionService : public QObject
{
    Q_OBJECT
public:
    IInteractionService(){}
    virtual ~IInteractionService(){}

    /*!
     * @details
     *   The currently selected tool in application. When not null,
     *   user's mouse and keyboard events from the central widget are
     *   sent to this tool by IInputInterceptor.
     * @sa setInputInterceptor, inputInterceptor
     */
    virtual ITool *activeTool() = 0;

    /*!
     * @details
     *   Gets the catalog collection.
     */
    virtual ICatalogs &catalogs() = 0;

    /*!
     * @details
     *   Gets the immutable catalog collection.
     */
    virtual const ICatalogs &catalogs() const = 0;

    /*!
     * @details
     *   Gets the current user input interceptor. Null by default.
     * @sa setInputInterceptor, activeTool
     */
    virtual IInputInterceptor *inputInterceptor() = 0;

    /*!
     * @details
     *   Gets the application shell or main window.
     */
    virtual QMainWindow &mainWindow() = 0;

    /*!
     * @details
     *   Uses IConfigurationDelegate to clear changes done by
     *   components (using IConfigurationDelegate::deconfigure())
     *   and configure components again.
     * @sa setConfigurationDelegate
     */
    virtual void resetUi() = 0;

    /*!
     * @details
     *   Deactivates current tool and sets the specified tool as active.
     * @sa activeTool
     */
    virtual void setActiveTool(ITool *ip_activeTool) = 0;

    /*!
     * @details
     *   Sets the configuration delegate responsible for the configuring
     *   started up component: IComponentConfigurationDelegate::configure() method
     *   will be binded to the IComponentManager::componentStarted() signal.
     *
     *   CarouselComponentConfigurationDelegate is used by default. Note, that
     *   IInteractionService takes ownership of the configuration delegate.
     */
    virtual void setConfigurationDelegate(IComponentConfigurationDelegate *ip_configurationDelegate) = 0;

    /*!
     * @details
     *   Deletes the previous (if any) and sets the new input interceptor in one of your GUI components.
     *   If you want user input would be sent to the active tool, use following snippet:
     * @code
     *   IInteractionService* interactionService = application->serviceLocator().locate<IInteractionService>();
     *   interactionService->setInputInterceptor(new InputInterceptor());
     *   interactionService->inputInterceptor()->setSender(interactionService->mainWindow.centralWidget());
     * @endcode
     *   @a Null by default. Note, that IInteractionService takes ownership of the
     *   interceptor.
     * @sa setInputInterceptor, activeTool
     */
    virtual void setInputInterceptor(IInputInterceptor *ip_inputInterceptor) = 0;

private:
    Q_DISABLE_COPY(IInteractionService)
};

#endif // IINTERACTIVITYSERVICE_H
