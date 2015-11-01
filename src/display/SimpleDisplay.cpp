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

#include <display/SimpleDisplay.h>
#include <display/DisplayTransformation.h>
#include <carousel/logging/LoggerFacade.h>

#include <QtGui/QShowEvent>
#include <QtGui/QPaintDevice>
#include <QtGui/QPainter>


namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("SimpleDisplay");
}

static const int flipY = -1;

SimpleDisplay::SimpleDisplay(QObject *parent)
    : IDisplay()
    , m_initialized(false)
    , m_moveVisibleBound(true)
    , m_wasDrawing(false)
    , m_conn()
    , m_offset(0, 0)
    , m_startPan(0, 0)
    , m_transform(new DisplayTransformation())
    , m_pixmap(createPixmap())
    , m_draftPixmaps(3)
    , m_attachedWidget(nullptr)
{
    setParent(parent);

    m_conn = connect(m_transform, &DisplayTransformation::visibleBoundsChanged, this, &SimpleDisplay::onVisibleBoundChanged);
    connect(m_transform, &DisplayTransformation::deviceFrameChanged, this, &SimpleDisplay::onDeviceFrameChanged);

    // retransmission to clients
    connect(m_transform, &DisplayTransformation::boundsChanged, this, &SimpleDisplay::boundsChanged);
    connect(m_transform, &DisplayTransformation::deviceFrameChanged, this, &SimpleDisplay::deviceFrameChanged);
    connect(m_transform, &DisplayTransformation::visibleBoundsChanged, this, &SimpleDisplay::visibleBoundsChanged);
}

SimpleDisplay::~SimpleDisplay()
{
}

void SimpleDisplay::drawOut(QPainter *toPainter) const
{
    QMutexLocker guard(&m_pixmapMutex);
    toPainter->drawPixmap(m_offset.x(), m_offset.y(), m_pixmap->width(), m_pixmap->height(), *m_pixmap);
}

QObject *SimpleDisplay::attachedWidget() const
{
    return m_attachedWidget;
}

void SimpleDisplay::setAttachedWidget(QObject *attachedWidget)
{
    if (m_attachedWidget == attachedWidget)
        return;

    m_attachedWidget = attachedWidget;
    emit attachedWidgetChanged(attachedWidget);
}

bool SimpleDisplay::isReady() const
{
    return !m_transform->deviceFrame().isEmpty();
}

void SimpleDisplay::dumpDraft(const DispayCache inCache)
{
    Q_UNUSED(inCache)
    m_offset = QPointF(0, 0);

    m_pixmapMutex.lock();
    QPainter painter(m_pixmap);

    for (QPixmapPtr& pixmap : m_draftPixmaps)
    {
        if (pixmap != nullptr)
            painter.drawPixmap(0, 0, *pixmap);
    }

    m_pixmapMutex.unlock();
    emit needChange();
    m_wasDrawing = true;
}

void SimpleDisplay::startDrawing(const DispayCache inCache)
{
    if (!isReady())
    {
        return;
    }

    m_wasDrawing = false;

    delete m_draftPixmaps[(int)inCache];
    m_draftPixmaps[(int)inCache] = nullptr;

    if (inCache == DispayCache::Geometry)
    {
        m_draftPixmaps[(int)inCache] = createPixmap(Qt::white);
    }
    else
    {
        m_draftPixmaps[(int)inCache] = createPixmap(Qt::transparent);
    }

    /*
#ifndef NDEBUG
    double scale = transformation()->scale();
    QRectF r = transformation()->visibleBounds().adjusted(3 / scale, 20 / scale, -20 / scale, -3 / scale);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);
    pen.setCosmetic(true);
    m_currentTourDuMonde->setPen(pen);
    m_currentTourDuMonde->drawRect(r);

    pen.setStyle(Qt::DashLine);
    pen.setWidth(3);
    pen.setColor(Qt::red);
    m_currentTourDuMonde->setPen(pen);
    r = transformation()->bounds().adjusted(3 / scale, 20 / scale, -20 / scale, -3 / scale);
    m_currentTourDuMonde->drawRect(r);
#endif

    return m_currentTourDuMonde;
    */
}

void SimpleDisplay::finishDrawing(const DispayCache inCache)
{
    if (!isReady())
    {
        return;
    }

    if (!m_wasDrawing) // there wasn't any drawing between "start" and "finish" - because all layers were removed. So, clear background
    {
        dumpDraft(inCache);
    }

    m_offset = QPointF(0, 0);
}

QPixmap& SimpleDisplay::lockPixmap(const DispayCache inCache)
{
    QPixmapPtr& pixmap = m_draftPixmaps[(int)inCache];
    return *pixmap;
}

void SimpleDisplay::unlockPixmap(const DispayCache inCache)
{
    dumpDraft(inCache);
}

DisplayTransformation *SimpleDisplay::transformation()
{
    return m_transform;
}

const DisplayTransformation *SimpleDisplay::transformation() const
{
    return m_transform;
}

void SimpleDisplay::panMoveTo(const QPoint &screenPoint)
{
    m_offset = (screenPoint - m_startPan);
    emit needChange();
}

void SimpleDisplay::panStart(const QPoint &screenPoint)
{
    m_startPan = screenPoint;
}

QRectF SimpleDisplay::panStop()
{
    moveVisibleBounds(m_offset.x(), m_offset.y());
    emit needChange(); // TODO: don't neet this signal
    return QRectF();
}

void SimpleDisplay::postDrawingTask(IDrawingTaskPtr task)
{
    Q_ASSERT(task != nullptr && "Null pointer is not allowed");
    if (!isReady())
    {
        return;
    }

    task->draw(*this);
}

QPixmapPtr SimpleDisplay::createPixmap(const QColor &fillColor) const
{
    QPixmapPtr pixmap(new QPixmap(transformation()->deviceFrame().width(), transformation()->deviceFrame().height()));
    pixmap->fill(fillColor);
    return pixmap;
}

void SimpleDisplay::onVisibleBoundChanged(const QRectF &visibleBounds)
{
    Q_UNUSED(visibleBounds)
    emit needChange();
}

void SimpleDisplay::onDeviceFrameChanged(const QRectF &deviceFrame)
{
    m_pixmap = createPixmap();
}

void SimpleDisplay::moveVisibleBounds(int dx, int dy)
{
    if (!m_moveVisibleBound)
        return;

    QObject::disconnect(m_conn);

    double scale = transformation()->scale();
    QRectF visibleBounds = transformation()->visibleBounds();
    visibleBounds.moveTopLeft(QPointF(visibleBounds.left() - dx / scale, visibleBounds.top() - dy / scale * flipY));
    transformation()->setVisibleBounds(visibleBounds);

    m_conn = connect(transformation(), &DisplayTransformation::visibleBoundsChanged, this, &SimpleDisplay::onVisibleBoundChanged);
}

int SimpleDisplay::getDy(double scale)
{
    // Visible extent could be moved out the extent. We should expand extend
    // instead of those max/min calculations
    // int min_y = std::min(m_extent.top(), m_visibleExtent.top());
    // int max_y = std::max(m_extent.bottom(), m_visibleExtent.bottom());
    qreal dy = transformation()->bounds().height() * scale;
    dy = std::max(dy, transformation()->deviceFrame().height());
    dy -= transformation()->deviceFrame().height();
    return dy;
}

int SimpleDisplay::getDx(double scale)
{
    qreal dx = (transformation()->bounds().width() * scale);
    dx = std::max(dx, transformation()->deviceFrame().width());
    dx -= transformation()->deviceFrame().width();
    return dx;
}


