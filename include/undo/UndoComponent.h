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
 * @details
 *   Registered services:
 * @li QUndoStack;
 */
class UNDO_API UndoComponent : public BaseComponent
{
    Q_OBJECT
public:
    UndoComponent(QObject *parent = nullptr);
    ~UndoComponent();

protected:
    /*!
     * @details
     *   Shuts down the component.
     */
    void _onShutdown();

    /*!
     * @details
     *   Registers undo dialog in the dialog service.
     * @param ip_initData should be a reference to AbstractApplication object.
     * @return @a false, if ip_initData is not a reference to AbstractApplication object.
     *   Otherwise, return @a true.
     */
    bool _onStartup(QObject *ip_initData);

private:
    QUndoStack *m_undoStack;
};

#endif // UNDOCOMPONENT_H
