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

#ifndef COMPONENTINITIALISER_H
#define COMPONENTINITIALISER_H

#include "componentsystem/IComponentInitialiser.h"

#include <QtCore/QObject>

class ILogger;

/*!
 * @brief
 *   It is a default implementation of the component initialisation.
 * @details
 *   It is used by IComponentManager to initialise component to delegate start up
 *   or shut down the bundle of components.
 */
class COMP_API ComponentInitialiser : public QObject, public IComponentInitialiser
{
    Q_OBJECT
public:
    ComponentInitialiser(ILogger &log, QObject *parent = nullptr);
    ~ComponentInitialiser();

    /*!
     * @details
     *   Shuts down specified component.
     *
     *   Note, that components should have descending order,
     *   e.g. parents should stay before children, because
     *   children should shut down first.
     */
    void shutdownComponent(IComponent *component);

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
    bool startupComponent(IComponent *component, QObject *ip_initializationData);

protected:
    ILogger &m_log;
};

#endif // COMPONENTINITIALISER_H
