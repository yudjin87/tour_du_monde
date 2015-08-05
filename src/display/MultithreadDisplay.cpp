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

#include <display/MultithreadDisplay.h>
#include <display/StartDrawingTask.h>
#include <display/UpdateTask.h>
#include <display/RenderThread.h>
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QMutexLocker>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("MT Display");
}

static const int flipY = -1;
static const size_t QUEUE_LIMIT = 100;

MultithreadDisplay::MultithreadDisplay(QWidget *parent)
    : SimpleDisplay(parent)
    , m_taskQueue(QUEUE_LIMIT)
    , m_renderer(new RenderThread(*this, m_taskQueue, this))
    , m_mutex(QMutex::Recursive) // TODO
{
    m_renderer->start();
}

DisplayTransformation *MultithreadDisplay::transformation()
{
    QMutexLocker guard(&m_mutex);
    return SimpleDisplay::transformation();
}

const DisplayTransformation *MultithreadDisplay::transformation() const
{
    QMutexLocker guard(&m_mutex);
    return SimpleDisplay::transformation();
}

MultithreadDisplay::~MultithreadDisplay()
{
    m_taskQueue.push(IDrawingTaskPtr(nullptr));
    m_renderer->wait(); // join
}

void MultithreadDisplay::startDrawing(const DispayCache inCache)
{
    if (inCache == DispayCache::Geometry) {
        // TODO: abort drawings and crear queue, when new "startDrawing" is called before finishing
        Log.d("Start drawing: create StartDrawingTask");
        m_taskQueue.push(IDrawingTaskPtr(new StartDrawingTask(this)));
        return;
    }

    SimpleDisplay::startDrawing(inCache);
}

void MultithreadDisplay::finishDrawing(const DispayCache inCache)
{    
    if (inCache == DispayCache::Geometry) {
        Log.d("Finish drawing: create UpdateTask");
        m_taskQueue.push(IDrawingTaskPtr(new UpdateTask(this)));
        return;
    }

    SimpleDisplay::finishDrawing(inCache);
}

QPixmap &MultithreadDisplay::lockPixmap(const DispayCache inCache)
{
    if (inCache == DispayCache::Geometry) {
        m_mutex.lock();
        return SimpleDisplay::lockPixmap(inCache);
    }

    return SimpleDisplay::lockPixmap(inCache);
}

void MultithreadDisplay::unlockPixmap(const DispayCache inCache)
{
    if (inCache == DispayCache::Geometry) {
        m_mutex.unlock();
        SimpleDisplay::unlockPixmap(inCache);
        return;
    }

    SimpleDisplay::unlockPixmap(inCache);
}

void MultithreadDisplay::postDrawingTask(IDrawingTaskPtr task)
{
    Q_ASSERT(task != nullptr && "Null pointer is not allowed");
    m_taskQueue.push(std::move(task));
}

void MultithreadDisplay::callCreatePixmap() // TODO: rename
{
    QMutexLocker guard(&m_mutex);
    SimpleDisplay::startDrawing(DispayCache::Geometry);
}

void MultithreadDisplay::callCopyAndUpdate() // TODO: rename
{
    QMutexLocker guard(&m_mutex);
    SimpleDisplay::finishDrawing(DispayCache::Geometry);
}


