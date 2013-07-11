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

#include "RectRubberBand.h"

#include <components/interactivity/InputDispatcher.h>

#include <QtDebug>

#include <QtGui/QMouseEvent>
#include <QtWidgets/QGraphicsView>

//------------------------------------------------------------------------------
RectRubberBand::RectRubberBand(QObject *parent)
    : QObject(parent)
{
    setObjectName("RectRubberBand");
}

//------------------------------------------------------------------------------
QRect RectRubberBand::newRect(QGraphicsView *fromSender)
{
    view = fromSender;
    InputDispatcher *dispatcher = new InputDispatcher(this);
    dispatcher->setReceiver(this);
    dispatcher->setSender(fromSender->viewport());
    dispatcher->activate();
    return QRect();
}

//------------------------------------------------------------------------------
bool RectRubberBand::onContextMenu(QContextMenuEvent *ip_event)
{
    Q_UNUSED(ip_event)
    return false;
}

//------------------------------------------------------------------------------
void RectRubberBand::onDoubleClick(QMouseEvent *ip_event)
{
    Q_UNUSED(ip_event)
}

//------------------------------------------------------------------------------
void RectRubberBand::onKeyDown(QKeyEvent *ip_event)
{
    Q_UNUSED(ip_event)
}

//------------------------------------------------------------------------------
void RectRubberBand::onKeyUp(QKeyEvent *ip_event)
{
    Q_UNUSED(ip_event)
}

//------------------------------------------------------------------------------
void RectRubberBand::onMouseDown(QMouseEvent *ip_event)
{
    m_start = ip_event->pos();
}

//------------------------------------------------------------------------------
void RectRubberBand::onMouseMove(QMouseEvent *ip_event)
{
    qDebug() << ip_event->x() << ip_event->y();
}

//------------------------------------------------------------------------------
void RectRubberBand::onMouseUp(QMouseEvent *ip_event)
{
    Q_UNUSED(ip_event)
}

//------------------------------------------------------------------------------
