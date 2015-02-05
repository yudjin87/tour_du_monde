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

#include <display/MultithreadDisplay.h>
#include <display/RenderThread.h>

//------------------------------------------------------------------------------
static const int flipY = -1;
static const size_t QUEUE_LIMIT = 100;

//------------------------------------------------------------------------------
MultithreadDisplay::MultithreadDisplay(QWidget *parent)
    : SimpleDisplay(parent)
    , m_taskQueue(QUEUE_LIMIT)
    , m_renderer(new RenderThread(*this, m_taskQueue, this))
    , m_mutex(QMutex::Recursive) // TODO
{
    m_renderer->start();
}

//------------------------------------------------------------------------------
MultithreadDisplay::~MultithreadDisplay()
{
    m_taskQueue.push(IDrawingTaskPtr(nullptr));
    m_renderer->wait(); // join
}

//------------------------------------------------------------------------------
QPixmap *MultithreadDisplay::lockPixmap()
{
    m_mutex.lock();
    return SimpleDisplay::lockPixmap();
}

//------------------------------------------------------------------------------
void MultithreadDisplay::unlockPixmap()
{
    m_mutex.unlock();
}

//------------------------------------------------------------------------------
void MultithreadDisplay::postDrawingTask(IDrawingTaskPtr task)
{
    Q_ASSERT(task != nullptr && "Null pointer is not allowed");
    m_taskQueue.push(std::move(task));
}

//------------------------------------------------------------------------------

