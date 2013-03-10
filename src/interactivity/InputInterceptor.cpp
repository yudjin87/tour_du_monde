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

#include "InputInterceptor.h"
#include "ITool.h"

#include <QtGui/QApplication>
#include <QtGui/QContextMenuEvent>
#include <QtGui/QWidget>

//------------------------------------------------------------------------------
InputInterceptor::InputInterceptor(QObject *parent)
    : QObject(parent)
    , mp_interceptedWidget(nullptr)
    , mp_receiver(nullptr)
    , m_isActive(false)
    , m_isWorking(false)
{
    setObjectName("InputInterceptor");
}

//------------------------------------------------------------------------------
InputInterceptor::~InputInterceptor()
{
    deactivate();
}

//------------------------------------------------------------------------------
void InputInterceptor::activate()
{
    m_isActive = true;
    m_isWorking = invalidate(mp_interceptedWidget);
}

//------------------------------------------------------------------------------
void InputInterceptor::deactivate()
{
    m_isActive = false;
    m_isWorking = invalidate(mp_interceptedWidget);
}

//------------------------------------------------------------------------------
bool InputInterceptor::isActive() const
{
    return m_isActive;
}

//------------------------------------------------------------------------------
bool InputInterceptor::isWorking() const
{
    return m_isWorking;
}

//------------------------------------------------------------------------------
void InputInterceptor::setSender(QWidget *ip_interceptedWidget)
{
    QWidget *old = mp_interceptedWidget;
    mp_interceptedWidget = ip_interceptedWidget;

    m_isWorking = invalidate(old);
}

//------------------------------------------------------------------------------
void InputInterceptor::setReceiver(IInputReceiver *ip_receiver)
{
    mp_receiver = ip_receiver;
    m_isWorking = invalidate(mp_interceptedWidget);
}

//------------------------------------------------------------------------------
QWidget *InputInterceptor::sender() const
{
    return mp_interceptedWidget;
}

//------------------------------------------------------------------------------
IInputReceiver *InputInterceptor::receiver() const
{
    return mp_receiver;
}

//------------------------------------------------------------------------------
bool InputInterceptor::eventFilter(QObject *ip_sender, QEvent *ip_event)
{
    Q_UNUSED(ip_sender)
    switch (ip_event->type())
    {
    case QEvent::KeyRelease:
        mp_receiver->onKeyUp(static_cast<QKeyEvent *>(ip_event));
        break;

    case QEvent::KeyPress:
        mp_receiver->onKeyDown(static_cast<QKeyEvent *>(ip_event));
        break;

    case QEvent::ContextMenu:
        return mp_receiver->onContextMenu(static_cast<QContextMenuEvent *>(ip_event));

    case QEvent::MouseMove:
        mp_receiver->onMouseMove(static_cast<QMouseEvent *>(ip_event));
        break;

    case QEvent::MouseButtonPress:
        mp_receiver->onMouseDown(static_cast<QMouseEvent *>(ip_event));
        break;

    case QEvent::MouseButtonRelease:
        mp_receiver->onMouseUp(static_cast<QMouseEvent *>(ip_event));
        break;

    case QEvent::MouseButtonDblClick:
        mp_receiver->onDoubleClick(static_cast<QMouseEvent *>(ip_event));
        break;

    default:
        break;
    }

    // standard event processing
    return QObject::eventFilter(ip_sender, ip_event);
}

//------------------------------------------------------------------------------
bool InputInterceptor::canStartWorking()
{
    if (!isActive())
        return false;

    if (mp_interceptedWidget == nullptr)
        return false;

    if (mp_receiver == nullptr)
        return false;

    return true;
}

//------------------------------------------------------------------------------
bool InputInterceptor::invalidate(QWidget *interceptedWidget)
{
    bool result = canStartWorking();

    if (result) {
        // mp_interceptedWidget is not null in this case:
        mp_interceptedWidget->installEventFilter(this);
    } else if (interceptedWidget != nullptr){
        interceptedWidget->removeEventFilter(this);
    }

    return result;
}

//------------------------------------------------------------------------------
