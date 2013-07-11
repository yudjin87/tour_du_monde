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

#ifndef IINPUTDISPATCHER_H
#define IINPUTDISPATCHER_H

#include "interactivity_global.h"

#include <functional>

class IInputReceiver;
class QWidget;

/*!
 * @brief
 *   This abstract class provides interface to application widget events'
 *   manipulating and transfering them to the active application's tool.
 * @details
 *   You can also use instance of this interface to handle user inputs
 *
 *   After activating events from the widget will be sent to the
 *   selected tool by InteracionService.
 *   There are following events, that will be intercepted from the widget:
 *    @li Context menu event;
 *    @li Key pressed event;
 *    @li Key released event;
 *    @li Mouse move event;
 *    @li Left button down event;
 *    @li Left button up event;
 *    @li Right button down event;
 *    @li Right button up event;
 *    @li Double click event;
 *
 *    All these events (except context menu event) will pass to the widget if
 *    dispatcher @a isActive(), and right after they will be handled by receiver.
 *    Also, if your receiver displays a custom context menu, it should let the
 *    application know that it handled the context menu event by returning @a true from
 *    the IInputReceiver::contextMenuFired() function. If you don't do this, the
 *    standard context menu will be displayed.
 */
class INTERACTIVITY_API IInputDispatcher
{
public:
    IInputDispatcher(){}
    virtual ~IInputDispatcher(){}

    /*!
     * @details
     *   Starts intercept the @a widget events and passes them to the selected
     *   receiver if any.
     *
     *   Events will not be intercepted until @a sender or @a receiver is null.
     *   @a Deactivating by default.
     */
    virtual void activate() = 0;

    /*!
     * @details
     *   Stops invokes appropriate registered handlers by the @a widget events
     *   intercepting.
     *   It is a default state.
     */
    virtual void deactivate() = 0;

    /*!
     * @details
     *   Gets the value determinig whether events passed to receiver or not.
     *
     * @note IInputDispatcher might be active, but is not working. It is mean,
     *   than receiver or sender is null. As soon as they be set, it will start
     *   working.
     */
    virtual bool isActive() const = 0;

    /*!
     * @details
     *   Gets the value determinig whether events passed to receiver or not.
     *
     *   Returns @a true if @a active and @a widget events are intercepted and passed
     *   to the receiver.
     *   Returns @a false if is not active, or @a widget or @a receiver is null.
     */
    virtual bool isWorking() const = 0;

    /*!
     * @details
     *   Sets the reference to widget events will be intercepted from.
     */
    virtual void setSender(QWidget *interceptedWidget) = 0;

    /*!
     * @details
     *   Sets the receiver events form widget will be sended to.
     */
    virtual void setReceiver(IInputReceiver *receiver) = 0;

    /*!
     * @details
     *   Returns watched widget.
     */
    virtual QWidget *sender() const = 0;

    /*!
     * @details
     *   Returns the received events object.
     */
    virtual IInputReceiver *receiver() const = 0;

private:
    Q_DISABLE_COPY(IInputDispatcher)
};

#endif // IINPUTDISPATCHER_H
