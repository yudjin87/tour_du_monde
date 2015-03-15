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

#include "InputDispatcher.h"
#include "ITool.h"

#include <QtGui/QContextMenuEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

InputDispatcher::InputDispatcher(QObject *parent)
    : QObject(parent)
    , m_interceptedWidget(nullptr)
    , m_receiver(nullptr)
    , m_isActive(false)
    , m_isWorking(false)
{
    setObjectName("InputDispatcher");
}

InputDispatcher::~InputDispatcher()
{
    deactivate();
}

void InputDispatcher::activate()
{
    m_isActive = true;
    m_isWorking = invalidate(m_interceptedWidget);
}

void InputDispatcher::deactivate()
{
    m_isActive = false;
    m_isWorking = invalidate(m_interceptedWidget);
}

bool InputDispatcher::isActive() const
{
    return m_isActive;
}

bool InputDispatcher::isWorking() const
{
    return m_isWorking;
}

void InputDispatcher::setSender(QWidget *interceptedWidget)
{
    QWidget *old = m_interceptedWidget;
    m_interceptedWidget = interceptedWidget;
    if (m_interceptedWidget != nullptr)
        connect(m_interceptedWidget, &QObject::destroyed, this, &InputDispatcher::onSenderDeleted);

    m_isWorking = invalidate(old);
}

void InputDispatcher::setReceiver(IInputReceiver *receiver)
{
    m_receiver = receiver;
    if (m_receiver != nullptr)
        connect(dynamic_cast<QObject *>(m_receiver), &QObject::destroyed, this, &InputDispatcher::onReceiverDeleted);

    m_isWorking = invalidate(m_interceptedWidget);
}

QWidget *InputDispatcher::sender() const
{
    return m_interceptedWidget;
}

IInputReceiver *InputDispatcher::receiver() const
{
    return m_receiver;
}

bool InputDispatcher::eventFilter(QObject *sender, QEvent *event)
{
    Q_UNUSED(sender)
    bool result = false;
    switch (event->type())
    {
    case QEvent::KeyRelease:
        result = m_receiver->onKeyUp(static_cast<QKeyEvent *>(event));
        break;

    case QEvent::KeyPress:
        result = m_receiver->onKeyDown(static_cast<QKeyEvent *>(event));
        break;

    case QEvent::ContextMenu:
        result = m_receiver->onContextMenu(static_cast<QContextMenuEvent *>(event));
        break;

    case QEvent::MouseMove:
        result = m_receiver->onMouseMove(static_cast<QMouseEvent *>(event));
        break;

    case QEvent::MouseButtonPress:
        result = m_receiver->onMouseDown(static_cast<QMouseEvent *>(event));
        break;

    case QEvent::MouseButtonRelease:
        result = m_receiver->onMouseUp(static_cast<QMouseEvent *>(event));
        break;

    case QEvent::MouseButtonDblClick:
        result = m_receiver->onDoubleClick(static_cast<QMouseEvent *>(event));
        break;

    default:
        break;
    }

    if (!result)
        return QObject::eventFilter(sender, event);

    return true;
}

bool InputDispatcher::canStartWorking()
{
    if (!isActive())
        return false;

    if (m_interceptedWidget == nullptr)
        return false;

    if (m_receiver == nullptr)
        return false;

    return true;
}

bool InputDispatcher::invalidate(QWidget *interceptedWidget)
{
    bool result = canStartWorking();

    if (result) {
        // m_interceptedWidget is not null in this case:
        m_interceptedWidget->installEventFilter(this);
    } else if (interceptedWidget != nullptr){
        interceptedWidget->removeEventFilter(this);
    }

    return result;
}

void InputDispatcher::onSenderDeleted()
{
    m_interceptedWidget = nullptr;
    m_isWorking = invalidate(m_interceptedWidget);
}

void InputDispatcher::onReceiverDeleted()
{
    m_receiver = nullptr;
    m_isWorking = invalidate(m_interceptedWidget);
}

