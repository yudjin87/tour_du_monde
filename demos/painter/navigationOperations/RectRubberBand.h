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

#ifndef RECTRUBBERBAND_H
#define RECTRUBBERBAND_H

#include <components/interactivity/IInputReceiver.h>

#include <QtCore/QObject>
#include <QtCore/QRect>

class QGraphicsView;

class RectRubberBand : public QObject, public IInputReceiver
{
    Q_OBJECT
public:
    explicit RectRubberBand(QObject *parent = nullptr);

    QRect newRect(QGraphicsView *fromSender);

    bool onContextMenu(QContextMenuEvent *ip_event);

    void onDoubleClick(QMouseEvent *ip_event);

    void onKeyDown(QKeyEvent *ip_event);

    void onKeyUp(QKeyEvent *ip_event);

    void onMouseDown(QMouseEvent *ip_event);

    void onMouseMove(QMouseEvent *ip_event);

    void onMouseUp(QMouseEvent *ip_event);

private:
   QPoint m_start;
   QGraphicsView *view;
};

#endif // RECTRUBBERBAND_H
