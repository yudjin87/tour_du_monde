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

#pragma once
#include "interactivity_global.h"

class IOperationCatalog;
class IDockWidgetCatalog;
class IMenuCatalog;
class IToolBarCatalog;

/*!
 * @brief
 *   This interface provides methods to get catalogs that contain interactive components.
 * @details
 *   Use IInteractionService::catalogs() to get a reference to this object.
 */
class INTERACTIVITY_API ICatalogs
{
public:
    ICatalogs(){}
    virtual ~ICatalogs(){}

    /*!
     * @details
     *   Gets the operation catalog.
     */
    virtual IOperationCatalog &operationCatalog() = 0;

    /*!
     * @details
     *   Gets the immutable operation catalog.
     */
    virtual const IOperationCatalog &operationCatalog() const = 0;

    /*!
     * @details
     *   Gets the dockable widget catalog.
     */
    virtual IDockWidgetCatalog &dockWidgetCatalog() = 0;

    /*!
     * @details
     *   Gets the immutable dockable widget catalog.
     */
    virtual const IDockWidgetCatalog &dockWidgetCatalog() const = 0;

    /*!
     * @details
     *   Gets the menu catalog.
     */
    virtual IMenuCatalog &menuCatalog() = 0;

    /*!
     * @details
     *   Gets the immutable menu catalog.
     */
    virtual const IMenuCatalog &menuCatalog() const = 0;

    /*!
     * @details
     *   Gets the immutable toolbar catalog.
     */
    virtual IToolBarCatalog &toolBarCatalog() = 0;

    /*!
     * @details
     *   Gets the toolbar catalog.
     */
    virtual const IToolBarCatalog &toolBarCatalog() const = 0;

private:
    Q_DISABLE_COPY(ICatalogs)
};

