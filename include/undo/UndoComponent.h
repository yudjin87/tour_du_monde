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

#ifndef UNDOCOMPONENT_H
#define UNDOCOMPONENT_H

#include "undo/undo_global.h"

#include <componentsystem/BaseComponent.h>

class QUndoStack;

/*!
 * @brief
 *   This class represents a component, that provides undo facilities.
 * @details
 *   The UndoComponent creates and registers QUndoStack as a service in the service locator.
 *   It is also has an IInteractiveExtension extension, that adds undo buttons to the menu and toolbar.
 *
 *   Registered services:
 * @li QUndoStack;
 *
 * @sa UndoInteractiveExtension
 */
class UNDO_API UndoComponent : public BaseComponent
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{UndoComponent} and also registers UndoInteractiveExtension.
     */
    UndoComponent(QObject *parent = nullptr);
    ~UndoComponent();

protected:
    /*!
     * @details
     *   Shuts down the component.
     */
    void onShutdown(IServiceLocator *serviceLocator);

    /*!
     * @details
     *   Registers undo dialog in the dialog service.
     * @param serviceLocator should be a reference to AbstractApplication object.
     * @return @a false, if serviceLocator is not a reference to AbstractApplication object.
     *   Otherwise, return @a true.
     */
    bool onStartup(IServiceLocator *serviceLocator);

private:
    Q_DISABLE_COPY(UndoComponent)

private:
    QUndoStack *m_undoStack;
};

#endif // UNDOCOMPONENT_H
