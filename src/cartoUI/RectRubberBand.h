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

#pragma once
#include <display/display_api.h>
#include <components/interactivity/InputDispatcher.h>
#include <components/interactivity/BaseInputReceiver.h>

#include <QtCore/QObject>
#include <QtCore/QEventLoop>
#include <QtCore/QRect>

#include <memory>

class IDisplay;

class DISPLAY_API RectRubberBand : public QObject, public BaseInputReceiver
{
    Q_OBJECT
public:
    explicit RectRubberBand(QObject *parent = nullptr);

    bool newRect(IDisplay *display, const QPoint& start, QRect* out);

    // TODO: handle Escape key
    bool onMouseMove(QMouseEvent *event) override;

    bool onMouseUp(QMouseEvent *event) override;

private:
   QPoint m_start;
   QRect m_result;
   QEventLoop m_eventLoop;
   IDisplay *m_display;
   std::unique_ptr<InputDispatcher> m_dispatcher;
};

