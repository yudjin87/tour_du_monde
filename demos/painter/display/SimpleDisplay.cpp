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
    , m_scale(1)
    , m_pixmap(nullptr)
    , m_currentPainter(nullptr)

{
    setParent(parent);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Throttle* throttle = new Throttle(this);
//    connect(this, SIGNAL(needChange()), throttle, SLOT(start()));
//    connect(throttle, SIGNAL(elapsed()), this, SLOT(emitChanged()));

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

QTransform SimpleDisplay::transform() const
{
    QTransform viewport;
    qreal dx = (-m_extent.left()/ 1 - horizontalScrollBar()->value());
    qreal dy = (-m_extent.top() / 1 - verticalScrollBar()->value());

    viewport.translate((width()) / 2, (height()) / 2);
    viewport.scale(m_scale, m_scale);
    viewport.translate((-width()) / 2, (-height()) / 2);

    viewport.translate(dx, dy);

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
    //m_currentPainter->setRenderHint(QPainter::NonCosmeticDefaultPen);

    m_transform = m_currentPainter->transform().inverted();

    QRectF r = visibleExtent().adjusted(10, 10, -30, -30);
    m_currentPainter->drawRect(r);

    qreal dx = (-m_extent.left()/ 1 - horizontalScrollBar()->value());
    qreal dy = (-m_extent.top() / 1 - verticalScrollBar()->value());
    m_currentPainter->drawEllipse(QPointF(-dx + width()  / 2, -dy + height() / 2), 5, 5);

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
    QTransform viewport = transform();

    QTransform transform = viewport.inverted();

    QRectF visibleExtent(0, 0, width(), height());
    visibleExtent = transform.mapRect(visibleExtent);
    return visibleExtent;
}

//------------------------------------------------------------------------------
QRectF SimpleDisplay::extent() const
{
    return m_extent;
}

//------------------------------------------------------------------------------
void SimpleDisplay::setExtent(const QRectF &extent)
{
    m_extent = extent;

    int dx = (m_extent.width() * m_scale);
    int dy = (m_extent.height() * m_scale);

    dx = std::max(dx, width());
    dy = std::max(dy, height());

    dx -= width();
    dy -= height();

//    dx *= m_scale;
//    dy *= m_scale;

    int dy_min = visibleExtent().top() - m_extent.top();
    int dy_max = m_extent.bottom() - visibleExtent().bottom();

    qDebug(QString("dy: %1; top: %2; h: %3/%4(%5)").arg(dy).arg(m_extent.top()).arg(height()).arg(m_extent.height())
           .arg(m_extent.height() * m_scale).toLatin1());
    //qDebug(QString("left: %1; top: %2").arg(m_extent.left()).arg(m_extent.top()).toLatin1());

    horizontalScrollBar()->setRange(0, dx);
    verticalScrollBar()->setRange(dy_min, dy_max);
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
    setExtent(extent());
    qDebug(QString("scale: %1;").arg(scale).toLatin1());
    emit needChange();
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

   // qDebug(QString("dx: %1; dy: %2").arg(dx).arg(dy).toLatin1());

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

