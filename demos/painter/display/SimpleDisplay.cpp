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

#include "SimpleDisplay.h"
#include "DisplayTransformation.h"

#include "Throttle.h"

#include <QtGui/QShowEvent>
#include <QtGui/QPaintDevice>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

#include <QtWidgets/QScrollBar>

//------------------------------------------------------------------------------
static const int flipY = -1;

//------------------------------------------------------------------------------
SimpleDisplay::SimpleDisplay(QWidget *parent)
    : m_moveVisibleBound(true)
    , m_conn()
    , m_offset(0, 0)
    , m_startPan(0, 0)
    , m_pixmap(nullptr)
    , m_currentPainter(nullptr)
    , m_transform(new DisplayTransformation())
{
    setMouseTracking(true);
    setParent(parent);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    Throttle* throttle = new Throttle(this);
    //connect(this, SIGNAL(needChange()), throttle, SLOT(start()));
    //connect(throttle, SIGNAL(elapsed()), this, SLOT(emitChanged()));

    connect(this, SIGNAL(needChange()), this, SLOT(emitChanged()));

    m_conn = connect(m_transform, &DisplayTransformation::visibleBoundsChanged, this, &SimpleDisplay::onVisibleBoundChanged);

    m_transform->setDeviceFrame(QRectF(0, 0, width(), height()));
}

//------------------------------------------------------------------------------
SimpleDisplay::~SimpleDisplay()
{
    delete m_pixmap;
    m_pixmap = nullptr;

    delete m_currentPainter;
    m_currentPainter = nullptr;
}

//------------------------------------------------------------------------------
QPainter *SimpleDisplay::painter()
{
    return m_currentPainter;
}

//------------------------------------------------------------------------------
QPainter *SimpleDisplay::startDrawing()
{
    if (m_pixmap != nullptr) {
        delete m_pixmap;
        m_pixmap = nullptr;
    }
    m_pixmap = new QPixmap(this->width(), this->height());
    m_pixmap->fill(Qt::white);

    m_currentPainter = new QPainter(m_pixmap);

    const QTransform &viewport = m_transform->transform();
    m_currentPainter->setTransform(viewport, false);

#ifndef NDEBUG
    double scale = m_transform->scale();
    QRectF r = m_transform->visibleBounds().adjusted(3 / scale, 20 / scale, -20 / scale, -3 / scale);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);
    pen.setCosmetic(true);
    m_currentPainter->setPen(pen);
    m_currentPainter->drawRect(r);

    pen.setStyle(Qt::DashLine);
    pen.setWidth(3);
    pen.setColor(Qt::red);
    m_currentPainter->setPen(pen);
    r = m_transform->bounds().adjusted(3 / scale, 20 / scale, -20 / scale, -3 / scale);
    m_currentPainter->drawRect(r);
#endif

    return m_currentPainter;
}

//------------------------------------------------------------------------------
void SimpleDisplay::finishDrawing(QPainter *painter)
{
    Q_UNUSED(painter)

    delete m_currentPainter;
    m_currentPainter = nullptr;
}

//------------------------------------------------------------------------------
DisplayTransformation *SimpleDisplay::transformation()
{
    return m_transform;
}

//------------------------------------------------------------------------------
const DisplayTransformation *SimpleDisplay::transformation() const
{
    return m_transform;
}

//------------------------------------------------------------------------------
void SimpleDisplay::panMoveTo(const QPoint &screenPoint)
{
    m_offset = (screenPoint - m_startPan);
    qDebug("panMoveTo: x: %f, y:%f", m_offset.x(), m_offset.y());
    viewport()->update();
}

//------------------------------------------------------------------------------
void SimpleDisplay::panStart(const QPoint &screenPoint)
{
    m_startPan = screenPoint;
    qDebug("panStart: x: %d, y:%d", screenPoint.x(), screenPoint.y());
}

//------------------------------------------------------------------------------
QRectF SimpleDisplay::panStop()
{
    moveVisibleBounds(m_offset.x(), m_offset.y());
    adjustScrollBars();
    viewport()->update();
    m_offset = QPointF(0, 0);
    emit needChange();
    return QRectF();
}

//------------------------------------------------------------------------------
void SimpleDisplay::scrollContentsBy(int dx, int dy)
{
    m_offset += QPointF(dx, dy);
    moveVisibleBounds(dx, dy);

    viewport()->update();
    emit needChange();
}

//------------------------------------------------------------------------------
void SimpleDisplay::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();

    // QPointF mapPoint = m_transform->toMapPoint(point.x(), point.y());
    // qDebug("x:%f; y:%f", mapPoint.x(), mapPoint.y());
}

//------------------------------------------------------------------------------
void SimpleDisplay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    if (m_pixmap == nullptr)
        return;

    QPainter painter(viewport());
    painter.drawPixmap(m_offset.x(), m_offset.y(), m_pixmap->width(), m_pixmap->height(), *m_pixmap);
}

//------------------------------------------------------------------------------
void SimpleDisplay::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    emitChanged();
}

//------------------------------------------------------------------------------
void SimpleDisplay::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    m_transform->setDeviceFrame(QRectF(0, 0, width(), height()));
    m_transform->setVisibleBounds(m_transform->visibleBounds());
}

//------------------------------------------------------------------------------
void SimpleDisplay::emitChanged()
{
    m_offset = QPointF(0, 0);
    emit visibleBoundsUpdated(m_transform);
    viewport()->update();
}

//------------------------------------------------------------------------------
void SimpleDisplay::onVisibleBoundChanged(const QRectF &visibleBounds)
{
    Q_UNUSED(visibleBounds)
    adjustScrollBars();
    emit needChange();
}

//------------------------------------------------------------------------------
void SimpleDisplay::adjustScrollBars()
{
    double scale = m_transform->scale();
    int dx = getDx(scale);
    int dy = getDy(scale);

    QRectF visibleBounds = m_transform->visibleBounds();
    QRectF bounds = m_transform->bounds();

    qreal verticalRelative = (visibleBounds.bottom() * flipY - bounds.bottom() * flipY) * scale; // top for flipping
    qreal horizontalRelative = (visibleBounds.left() - bounds.left()) * scale;

    // Do not move visible bounds during scroll changing
    m_moveVisibleBound = false;

    horizontalScrollBar()->setRange(0, dx);
    verticalScrollBar()->setRange(0, dy);

    horizontalScrollBar()->setValue(horizontalRelative);
    verticalScrollBar()->setValue(verticalRelative);

    m_moveVisibleBound = true;
}

//------------------------------------------------------------------------------
void SimpleDisplay::moveVisibleBounds(int dx, int dy)
{
    if (!m_moveVisibleBound)
        return;

    QObject::disconnect(m_conn);

    double scale = m_transform->scale();
    QRectF visibleBounds = m_transform->visibleBounds();
    visibleBounds.moveTopLeft(QPointF(visibleBounds.left() - dx / scale, visibleBounds.top() - dy / scale * flipY));
    m_transform->setVisibleBounds(visibleBounds);

    m_conn = connect(m_transform, &DisplayTransformation::visibleBoundsChanged, this, &SimpleDisplay::onVisibleBoundChanged);
}

//------------------------------------------------------------------------------
int SimpleDisplay::getDy(double scale)
{
    // Visible extent could be moved out the extent. We should expand extend
    // instead of those max/min calculations
    // int min_y = std::min(m_extent.top(), m_visibleExtent.top());
    // int max_y = std::max(m_extent.bottom(), m_visibleExtent.bottom());
    int dy = m_transform->bounds().height() * scale;
    dy = std::max(dy, height());
    dy -= height();
    return dy;
}

//------------------------------------------------------------------------------
int SimpleDisplay::getDx(double scale)
{
    int dx = (m_transform->bounds().width() * scale);
    dx = std::max(dx, width());
    dx -= width();
    return dx;
}

//------------------------------------------------------------------------------
