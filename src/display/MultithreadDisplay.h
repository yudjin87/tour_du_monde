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
#include <display/SimpleDisplay.h>

#include <QtCore/QMutex>

class RenderThread;

class MultithreadDisplay : public SimpleDisplay
{
    Q_OBJECT
public:
    MultithreadDisplay(QWidget *parent = nullptr);
    ~MultithreadDisplay();

    void startDrawing(const DispayCache inCache) override;
    void finishDrawing(const DispayCache inCache) override;

    QPixmap &lockPixmap(const DispayCache inCache) override;
    void unlockPixmap(const DispayCache inCache) override;

    void postDrawingTask(IDrawingTaskPtr task) override;
    DisplayTransformation *transformation() override;
    const DisplayTransformation *transformation() const override;

private:
    Q_DISABLE_COPY(MultithreadDisplay)
    friend class StartDrawingTask;
    friend class UpdateTask;

    void callCreatePixmap();
    void callCopyAndUpdate();

private:
    DrawingTaskQueue m_taskQueue;
    RenderThread* m_renderer;
    mutable QMutex m_mutex;
};


