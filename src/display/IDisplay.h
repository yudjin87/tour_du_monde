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
#include <display/IDrawingTask.h>
#include <display/ThreadSafeQueue.h>

#include <QtGui/QPixmap>
#include <QtWidgets/QAbstractScrollArea>

class DisplayTransformation;

//typedef std::unique_ptr<QPixmap> QPixmapPtr;
typedef QPixmap* QPixmapPtr;

enum class DispayCache
{
    Geometry = 0,
    Selection = 1,
    Annotations = 2
};

class DISPLAY_API IDisplay : public QAbstractScrollArea
{
    Q_OBJECT
    Q_PROPERTY(DisplayTransformation *transformation READ transformation)
public:
    IDisplay(){}
    virtual ~IDisplay(){}

    virtual void startDrawing(const DispayCache inCache) = 0;
    virtual void finishDrawing(const DispayCache inCache) = 0;

    virtual QPixmap &lockPixmap(const DispayCache inCache) = 0;
    virtual void unlockPixmap(const DispayCache inCache) = 0;

    virtual DisplayTransformation *transformation() = 0;
    virtual const DisplayTransformation *transformation() const = 0;

    virtual void postDrawingTask(IDrawingTaskPtr task) = 0;

    virtual QPixmapPtr createPixmap(const QColor &fillColor = Qt::transparent) const = 0;

public slots:
    virtual void panMoveTo(const QPoint &screenPoint) = 0;
    virtual void panStart(const QPoint &screenPoint) = 0;
    virtual QRectF panStop() = 0;
    virtual void updateWindow() = 0;

signals:
    /* from DisplayTransformation */
    void boundsChanged(const QRectF &bounds);
    void deviceFrameChanged(const QRectF &deviceFrame);
    void visibleBoundsChanged(const QRectF &visibleBounds);

private:
    Q_DISABLE_COPY(IDisplay)
};

typedef ThreadSafeQueue<IDrawingTaskPtr> DrawingTaskQueue;

