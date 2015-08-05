/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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

#include <display/CoordsTracker.h>
#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <components/interactivity/InputDispatcher.h>

#include <QtGui/QMouseEvent>
#include <QtWidgets/QStatusBar>

CoordsTracker::CoordsTracker(const IDisplay *display, QStatusBar *statusBar, QObject *parent)
    : QObject(parent)
    , BaseInputReceiver()
    , m_display(display)
    , m_statusBar(statusBar)
    , m_dispatcher(new InputDispatcher())
{
    m_dispatcher->setReceiver(this);
    m_dispatcher->setSender(m_display->viewport());
    m_dispatcher->activate();
}

bool CoordsTracker::onMouseMove(QMouseEvent *event)
{
    const DisplayTransformation* transform = m_display->transformation();
    QPointF mapPoint = transform->toMapPoint(event->pos());

    m_statusBar->showMessage(QString("x: %1, y: %2").arg(mapPoint.x()).arg(mapPoint.y()), 2000);

    // let's other objects to continue with this event
    return false;
}




