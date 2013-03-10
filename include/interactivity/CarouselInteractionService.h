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

class AbstractApplication;
class IComponent;
class IComponentManager;
class Catalogs;
class QMainWindow;

/*!
 * @brief
 *   This class is registered into the application services
 *   by the InteractionServiceComponent.
 * @sa IInteractionService.
 */
class INTERACTIVITY_API CarouselInteractionService : public IInteractionService
{
    Q_OBJECT
public:
    CarouselInteractionService(AbstractApplication &i_application, QObject *parent = nullptr);
    ~CarouselInteractionService();

    /*!
     * @details
     *   The currently selected tool in application. When not null,
     *   user's mouse and keyboard events from the central widget are
     *   sent to this tool by IInputInterceptor.
     * @sa setInputInterceptor, inputInterceptor
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
     *   Gets the current user input interceptor. Null by default.
     * @sa setInputInterceptor, activeTool
     */
    IInputInterceptor *inputInterceptor();

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
     *   Deactivates current tool and sets the specified tool as active.
     * @sa activeTool
     */
    void setActiveTool(ITool *ip_activeTool);

    /*!
     * @details
     *   Sets the configuration delegate responsible for the configuring
     *   started up component: IComponentConfigurationDelegate::configure() method
     *   will be binded to the AbstractApplication::componentStarted() signal.
     *
     *   CarouselComponentConfigurationDelegate is used by default. Note, that
     *   CarouselInteractionService takes ownership of the configuration delegate.
     */
    void setConfigurationDelegate(IComponentConfigurationDelegate *ip_configurationDelegate);

    /*!
     * @details
     *   Deletes the previous (if any) and sets the new input interceptor in one of your GUI components.
     *   If you want user input would be sent to the active tool, use following snippet:
     * @code
     *   IInteractionService* interactionService = application->serviceLocator().locate<IInteractionService>();
     *   interactionService->setInputInterceptor(new InputInterceptor());
     *   interactionService->inputInterceptor()->setSender(interactionService->mainWindow.centralWidget());
     * @endcode
     *   @a Null by default. Note, that CarouselInteractionService takes ownership of the
     *   interceptor.
     * @sa setInputInterceptor, activeTool
     */
    void setInputInterceptor(IInputInterceptor *ip_inputInterceptor);

protected slots:
    void onComponentStartedUp(IComponent *ip_component);
    void onComponentShutedDown(IComponent *ip_component);
    void onToolExecutingStopped();

private:
    AbstractApplication &m_app;
    IInputInterceptor *mp_inputInterceptor;
    IComponentConfigurationDelegate *mp_componentConfigurationDelegate;
    IComponentManager *mp_componentManager;
    ITool *mp_activeTool;
    Catalogs *mp_catalogs;
    QMainWindow *mp_mainWindow;
};

#endif // CAROUSELINTERACTIONSERVICE_H
