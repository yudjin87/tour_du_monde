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

#ifndef IINPUTRECEIVER_H
#define IINPUTRECEIVER_H

#include "interactivity_global.h"

#include "IOperation.h"

class QContextMenuEvent;
class QKeyEvent;
class QMouseEvent;

/*!
 * @brief
 *   With the IInputReceiver interface you can define what occurs on events such
 *   as mouse move, mouse button press/release, keyboard key press/release,
 *   double-click, and right click (context menu).
 * @details
 *   Use IInputInterceptor to obtain user input events.
 */
class INTERACTIVITY_API IInputReceiver
{
public:
    IInputReceiver(){}
    virtual ~IInputReceiver(){}

    /*!
     * @details
     *   Context menu event occured at the given in @a ip_event location.
     *
     *   When create a custom receiver, write code to display a
     *   custom context menu the right mouse button is pressed.
     *
     *   If your receiver displays a custom context menu, it should let the application
     *   know that it handled the onContextMenu event by returning true. If you
     *   don't do this, the standard context menu will be displayed.
     */
    virtual bool onContextMenu(QContextMenuEvent *ip_event) = 0;

    /*!
     * @details
     *   Occurs when a mouse button is double clicked.
     */
    virtual void onDoubleClick(QMouseEvent *ip_event) = 0;

    /*!
     * @details
     *   Occurs when a key on the keyboard is pressed.
     */
    virtual void onKeyDown(QKeyEvent *ip_event) = 0;

    /*!
     * @details
     *   Occurs when a key on the keyboard is released.
     */
    virtual void onKeyUp(QKeyEvent *ip_event) = 0;

    /*!
     * @details
     *   Occurs when a mouse button is pressed.
     */
    virtual void onMouseDown(QMouseEvent *ip_event) = 0;

    /*!
     * @details
     *   Occurs when the mouse is moved.
     */
    virtual void onMouseMove(QMouseEvent *ip_event) = 0;

    /*!
     * @details
     *   Occurs when a mouse button is released.
     */
    virtual void onMouseUp(QMouseEvent *ip_event) = 0;
};

#endif // IINPUTRECEIVER_H
