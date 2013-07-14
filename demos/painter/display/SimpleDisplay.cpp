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

#include "Throttle.h"

#include <QtGui/QShowEvent>
#include <QtGui/QPaintDevice>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

#include <QtWidgets/QScrollBar>

//------------------------------------------------------------------------------
SimpleDisplay::SimpleDisplay(QWidget *parent)    
    : m_offset(0, 0)
    //, m_scale(0.0025)
    , m_scale(5000)
    , m_pixmap(nullptr)
    , m_currentPainter(nullptr)
    , m_dx(0)
    , m_dy(0)
{
    setParent(parent);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    Throttle* throttle = new Throttle(this);
    //connect(this, SIGNAL(needChange()), throttle, SLOT(start()));
    //connect(throttle, SIGNAL(elapsed()), this, SLOT(emitChanged()));

    connect(this, SIGNAL(needChange()), this, SLOT(emitChanged()));
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

QTransform SimpleDisplay::transform()
{
    qreal dx = m_extent.left() - m_dx / m_scale;
    qreal dy = m_extent.top() - m_dy / m_scale;


    QTransform viewport;
//    viewport.translate(width() / 2, height() / 2);
  //  viewport.translate(-width()/ 2 / m_scale, -height()/ 2 / m_scale);

    viewport.scale(m_scale, m_scale);

    viewport.translate(-dx, -dy);

    return viewport;
}

//------------------------------------------------------------------------------
QPainter *SimpleDisplay::startDrawing()
{
    if (m_pixmap != nullptr) {
        delete m_pixmap;
        m_pixmap = nullptr;
    }
    m_pixmap = new QPixmap(this->width(), this->height());
    m_pixmap->fill(Qt::lightGray);

    m_currentPainter = new QPainter(m_pixmap);

    QTransform viewport = transform();

    m_currentPainter->setTransform(viewport, false);

    m_transform = viewport.inverted();

    QRectF r = visibleExtent().adjusted(10, 10, -30, -10);
    //m_currentPainter->drawRect(r);
    //m_currentPainter->drawRect(extent());

    qreal dx = (-m_extent.left()/ 1 - m_dx) / m_scale;
    qreal dy = (-m_extent.top()/ 1 - m_dy / m_scale);
    //m_currentPainter->drawEllipse(QPointF(-dx + width() / 2/ m_scale, -dy + height() / 2/ m_scale), 5, 5);

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
QRectF SimpleDisplay::visibleExtent() const
{
    QRectF visibleExtent(0, 0, width(), height());
    visibleExtent = m_transform.mapRect(visibleExtent);
    return visibleExtent;
}

//------------------------------------------------------------------------------
QRectF SimpleDisplay::extent() const
{
    return m_extent;
}

int SimpleDisplay::getDy()
{
    int dy = (m_extent.height() * m_scale);
    dy = std::max(dy, height());
    dy -= height();
    return dy;
}

int SimpleDisplay::getDx()
{
    int dx = (m_extent.width() * m_scale);
    dx = std::max(dx, width());
    dx -= width();
    return dx;
}

//------------------------------------------------------------------------------
void SimpleDisplay::setExtent(const QRectF &extent)
{
    m_extent = extent;

    int dy = getDy();
    int dx = getDx();


    qDebug(QString("dy(%1)= %2-%3. Off: %4").arg(dy).arg(m_extent.height() * m_scale).arg(height()).arg(m_dy).toLatin1());

    verticalScrollBar()->setRange(-0/ 1, dy);
    horizontalScrollBar()->setRange(-0 / 1, dx);
}

//------------------------------------------------------------------------------
double SimpleDisplay::scale() const
{
    return m_scale;
}

//------------------------------------------------------------------------------
void SimpleDisplay::setScale(double scale)
{
    m_scale = scale;
    //int dy = m_dy;
    setExtent(extent());
    qDebug(QString("scale: %1;").arg(scale).toLatin1());
    //m_dy = m_dy / m_scale;
    //qDebug(QString("m_dy: %1").arg(m_dy).toLatin1());
    emit needChange();
    qDebug("---------------------------");
}

//------------------------------------------------------------------------------
void SimpleDisplay::mouseMoveEvent(QMouseEvent *event)
{
    QPointF p = event->pos();
    qreal x;
    qreal y;
    m_transform.map(p.x(), p.y(), &x, &y);
    //qDebug(QString("x: %1 (%2)").arg(x).toLatin1());
    qDebug(QString("y: %1 (%2)").arg(y).arg(p.y()).toLatin1());

    qDebug(QString("offset: %1").arg(verticalScrollBar()->value()).toLatin1());
}

//------------------------------------------------------------------------------
void SimpleDisplay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    if (m_pixmap == nullptr)
        return;

    QPainter painter(viewport());

    // qDebug(QString("paint").toLatin1());
    //qDebug(QString("m_y_offset: %1").arg(m_offset.y()).toLatin1());

    painter.drawPixmap(m_offset.x(), m_offset.y(), m_pixmap->width(), m_pixmap->height(), *m_pixmap);
}

//------------------------------------------------------------------------------
void SimpleDisplay::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    emitChanged();
}

//------------------------------------------------------------------------------
void SimpleDisplay::scrollContentsBy(int dx, int dy)
{
    m_offset += QPointF(dx, dy);
    m_dy += dy;
    m_dx += dx;

    qDebug(QString("dx: %1; dy: %2").arg(dx).arg(dy).toLatin1());

    viewport()->update();
    emit needChange();
}

//------------------------------------------------------------------------------
void SimpleDisplay::emitChanged()
{
    m_offset = QPointF(0, 0);
    emit changed();

    viewport()->update();
}

//------------------------------------------------------------------------------
void SimpleDisplay::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    setExtent(m_extent);
    emit needChange();
}

//------------------------------------------------------------------------------


