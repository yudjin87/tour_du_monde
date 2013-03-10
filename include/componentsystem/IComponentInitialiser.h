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

#ifndef ICOMPONENTINITIALISER_H
#define ICOMPONENTINITIALISER_H

#include "componentsystem/componentsystem_global.h"

class IComponent;
class QObject;

/*!
 * @brief
 *   This abstract class provides interface for the component initialization.
 * @details
 *   It is used by IComponentManager to initialise component to delegate start up
 *   or shut down the bundle of components.
 */
class COMP_API IComponentInitialiser
{
public:
    IComponentInitialiser(){}
    virtual ~IComponentInitialiser(){}

    /*!
     * @details
     *   Shuts down specified component.
     *
     *   Note, that components should have descending order,
     *   e.g. parents should stay before children, because
     *   children should shut down first.
     */
    virtual void shutdownComponent(IComponent *component) = 0;

    /*!
     * @details
     *   Starts specified component if it is possible (if component
     *   is enabled) and passes the initialization data to it.
     *
     *   Note, that components should have descending order,
     *   e.g. parents should stay before children, because
     *   parents should start first.
     *
     * @return @a true, if component was started. If component is
     *   disabled or unavailabled, returns @a false. Also returns
     *   @a false if component start was failed.
     */
    virtual bool startupComponent(IComponent *component, QObject *ip_initializationData) = 0;

private:
    Q_DISABLE_COPY(IComponentInitialiser)
};

#endif // ICOMPONENTINITIALISER_H
