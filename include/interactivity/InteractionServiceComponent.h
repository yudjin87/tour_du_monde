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

#ifndef INTERACTIONSERVICECOMPONENT_H
#define INTERACTIONSERVICECOMPONENT_H

#include "interactivity_global.h"

#include <componentsystem/BaseComponent.h>

/*!
 * @brief
 *   This class represents a component, that creates and registers
 *   interactive services in the service locator.
 * @details
 *   The InteractionServiceComponent is a main @a component of GUI based
 *   application due to the IInteractionService. If your components
 *   add new operations or menus, or dockable widgets - they should be a
 *   @a child to InteractionServiceComponent component. This mean a
 *   dependency of component parent name:
 *   @a "Interactivity"
 *
 *   Registered services:
 * @li IDialogService;
 * @li IInteractionService;
 */
class INTERACTIVITY_API InteractionServiceComponent : public BaseComponent
{
    Q_OBJECT
public:
    InteractionServiceComponent(QObject *parent = nullptr);
    ~InteractionServiceComponent();

protected:
    /*!
     * @details
     *   Shuts down the component.
     */
    void _onShutdown();

    /*!
     * @details
     *   Registers IInteractionService in the service locator and initializes
     *   it with @a ip_initData.
     * @param ip_initData should be a reference to AbstractApplication object.
     * @return @a false, if ip_initData is not a reference to AbstractApplication object.
     *   Otherwise, return @a true.
     */
    bool _onStartup(QObject *ip_initData);

private:
    class InteractionServiceComponentPrivate;
    InteractionServiceComponentPrivate *d;
};

#endif // INTERACTIONSERVICECOMPONENT_H
