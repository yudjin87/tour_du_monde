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

static int c = 0;
//------------------------------------------------------------------------------
SimpleDisplay::SimpleDisplay(QWidget *parent)
    : m_offset(0, 0)
    , m_pixmap(nullptr)
    , m_currentPainter(nullptr)
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

//------------------------------------------------------------------------------
QTransform SimpleDisplay::transform()
{
    if (m_visibleExtent.height() <= 0 || m_visibleExtent.width() <= 0)
        return QTransform();

    double _scale = scale();

    qreal dx = m_visibleExtent.left();
    qreal dy = m_visibleExtent.top();

    QTransform viewport;
    viewport.scale(_scale, _scale);
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


#ifndef NDEBUG
    QRectF r = visibleExtent().adjusted(10, 10, -50, -50);

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
    r = m_extent.adjusted(10, 10, -50, -50);
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
QRectF SimpleDisplay::visibleExtent() const
{
    return m_visibleExtent;
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

    if (m_visibleExtent.isEmpty())
        setVisibleExtent(expand(m_extent, 1));
}

//------------------------------------------------------------------------------
int SimpleDisplay::getDy(double scale)
{
    // Visible extent could be moved out the extent. We should expand extend
    // instead of those max/min calculations
    // int min_y = std::min(m_extent.top(), m_visibleExtent.top());
    // int max_y = std::max(m_extent.bottom(), m_visibleExtent.bottom());
    int dy = m_extent.height() * scale;
    dy = std::max(dy, height());
    dy -= height();
    return dy;
}

//------------------------------------------------------------------------------
int SimpleDisplay::getDx(double scale)
{
    int dx = (m_extent.width() * scale);
    dx = std::max(dx, width());
    dx -= width();
    return dx;
}

//------------------------------------------------------------------------------
double SimpleDisplay::scale() const
{
    double relY = height() / m_visibleExtent.height();
    double relX = width() / m_visibleExtent.width();

    return std::min(relY, relX);
}

//------------------------------------------------------------------------------
void SimpleDisplay::setVisibleExtent(const QRectF &extent)
{
    // Use fitted bounds (e.g. adjusted(-20, -20, 20, 20))
    m_visibleExtent = extent;

    double relY = height() / extent.height();
    double relX = width() / extent.width();

    if (relX > relY)
        m_visibleExtent.setWidth(width() / scale());
    else
        m_visibleExtent.setHeight(height() / scale());
}

static bool skip = false;

//------------------------------------------------------------------------------
void SimpleDisplay::scrollContentsBy(int dx, int dy)
{
    double _scale = scale();

    m_offset += QPointF(dx, dy);

    if (!skip) {
        m_visibleExtent.moveTopLeft(QPointF(m_visibleExtent.left() - dx / _scale, m_visibleExtent.top() - dy / _scale));
    } else {
        skip = false;
    }

    viewport()->update();
    emit needChange();
}

//------------------------------------------------------------------------------
void SimpleDisplay::adjustScrollBars()
{
    double _scale = scale();
    int dx = getDx(_scale);
    int dy = getDy(_scale);

    qreal verticalRelative = (m_visibleExtent.top() - m_extent.top()) * _scale;
    qreal horizontalRelative = (m_visibleExtent.left() - m_extent.left()) * _scale;

//    qDebug("[%d] dy: (%f -%f)*%f = %f (of %d)", ++c, m_visibleExtent.top(), m_extent.top(), _scale, verticalRelative, dy);

    skip = true;
    horizontalScrollBar()->setRange(0, dx);
    verticalScrollBar()->setRange(0, dy);

    skip = true;
    horizontalScrollBar()->setValue(horizontalRelative);

    skip = true;
    verticalScrollBar()->setValue(verticalRelative);
    //skip = false;
}

//------------------------------------------------------------------------------
QRectF SimpleDisplay::expand(const QRectF &extent, double scale)
{
    qreal new_left = extent.center().x() - extent.width() / 2 * scale;
    qreal left = std::max(m_extent.left(), new_left);
    qreal new_right = new_left + extent.width() * scale;


    qreal new_top = extent.center().y() - extent.height() / 2 * scale;
    qreal top = std::max(m_extent.top(), new_top);
    qreal new_bottom = new_top + extent.height() * scale;

    // TODO: adjust rect, if it is faced with full bounds
    QRectF rect(left, top, extent.width() * scale, extent.height() * scale);

    if (new_bottom > m_extent.bottom()) {
        if (new_top <  m_extent.top()) {
            // Move to the extent center, if visible heigh is greater then map extent
            qreal centerY = ((m_extent.bottom() - m_extent.top()) / 2) - rect.height() / 2;
            //qDebug("centerY %f = (%f - %f)/2 - %f/2", centerY, m_extent.bottom(), m_extent.top(), rect.height());
            rect.moveTop(m_extent.top() + centerY);
        } else {
            rect.moveBottom(m_extent.bottom());
        }
    }

    if (new_right > m_extent.right()) {
        if (new_left <  m_extent.left()) {
            // Move to the extent center, if visible width is greater then map extent
            qreal centerX = ((m_extent.right() - m_extent.left()) / 2) - rect.width() / 2;
            qDebug("centerX %f = (%f - %f)/2 - %f/2", centerX, m_extent.right(), m_extent.left(), rect.width());
            rect.moveLeft(m_extent.left() + centerX);
        } else {
            rect.moveRight(m_extent.right());
        }
    }

    return rect;
}

//------------------------------------------------------------------------------
void SimpleDisplay::setScale(double _scale)
{
    double scale2 =  scale() / _scale;

    setVisibleExtent(expand(m_visibleExtent, scale2));
    adjustScrollBars();

    emit needChange();
}

//------------------------------------------------------------------------------
void SimpleDisplay::mouseMoveEvent(QMouseEvent *event)
{
    QPointF p = event->pos();
    qreal x;
    qreal y;
    m_transform.map(p.x(), p.y(), &x, &y);
    qDebug("x:%f; y:%f", x, y);

    qDebug(QString("offset: %1").arg(verticalScrollBar()->value()).toLatin1());
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
    setVisibleExtent(m_visibleExtent);
    adjustScrollBars();
    emit needChange();
}

//------------------------------------------------------------------------------


