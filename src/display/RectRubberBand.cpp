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

#include <display/RectRubberBand.h>
#include <display/IDisplay.h>

#include <QtCore/QtDebug>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QPen> // TODO: use ISymbol

RectRubberBand::RectRubberBand(QObject *parent)
    : QObject(parent)
    , m_result()
    , m_display(nullptr)
{
    setObjectName("RectRubberBand");
}

bool RectRubberBand::newRect(IDisplay *display, const QPoint &start, QRect *out)
{
    Q_ASSERT(m_dispatcher == nullptr && "Illegal state");
    Q_ASSERT(out != nullptr && "Null pointer is not allowed");

    m_start = start;
    m_display = display;
    m_dispatcher.reset(new InputDispatcher(this));
    m_dispatcher->setReceiver(this);
    m_dispatcher->setSender(m_display->viewport());
    m_dispatcher->activate();

    m_eventLoop.exec();

    *out = m_result.normalized();
    return true;
}

bool RectRubberBand::onMouseMove(QMouseEvent *event)
{
    m_display->startDrawing(DispayCache::Annotations);
    QPixmap& screen = m_display->lockPixmap(DispayCache::Annotations);

    QPainter painter(&screen);

    QPen b(Qt::SolidLine);
    b.setColor(Qt::red);

    painter.setPen(b);

    painter.drawRect(QRect(m_start, event->pos()));

    m_display->unlockPixmap(DispayCache::Annotations);
    m_display->finishDrawing(DispayCache::Annotations);

    // let's other objects to continue with this event
    return false;
}

bool RectRubberBand::onMouseUp(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return false;

    m_display->startDrawing(DispayCache::Annotations);
    m_display->lockPixmap(DispayCache::Annotations);
    m_display->unlockPixmap(DispayCache::Annotations);
    m_display->finishDrawing(DispayCache::Annotations);

    m_result.setTopLeft(m_start);
    m_result.setBottomRight(event->pos());
    m_eventLoop.exit();
    m_display = nullptr;
    m_dispatcher.reset();

    return true;
}

