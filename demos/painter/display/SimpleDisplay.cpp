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

#include <QtGui/QScrollBar>
#include <QtGui/QPaintDevice>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

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
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    Throttle* throttle = new Throttle(this);
    connect(this, SIGNAL(needChange()), throttle, SLOT(start()));
    connect(throttle, SIGNAL(elapsed()), this, SLOT(emitChanged()));
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
QPainter *SimpleDisplay::startDrawing()
{
    if (m_pixmap != nullptr) {
        delete m_pixmap;
        m_pixmap = nullptr;
    }

    m_pixmap = new QPixmap(this->width(), this->height());
    m_pixmap->fill(Qt::lightGray);

    m_currentPainter = new QPainter(m_pixmap);
    m_currentPainter->setWindow(0, 0, width() * m_scale, height() * m_scale);
    m_currentPainter->setViewport(0, 0, width(), height());

    QTransform viewport(1.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        -m_extent.left() - horizontalScrollBar()->value(), -m_extent.top() - verticalScrollBar()->value(), 1.0f);

    m_currentPainter->setTransform(viewport, false);

    m_transform = m_currentPainter->deviceTransform().inverted();
    qDebug(QString("dx: %1").arg(m_transform.dx()).toLatin1());

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
QRectF SimpleDisplay::extent() const
{
    return m_extent;
}

//------------------------------------------------------------------------------
void SimpleDisplay::setExtent(const QRectF &extent)
{
    m_extent = extent;

    double dy = (m_extent.height() / m_scale - height());
    double dx = (m_extent.width() / m_scale - width());

    verticalScrollBar()->setRange(0, dy);
    horizontalScrollBar()->setRange(0, dx);

    //verticalScrollBar()->setSingleStep(100);
    //horizontalScrollBar()->setSingleStep(m_scale);
    qDebug(QString("height: %1").arg(dy).toLatin1());
    qDebug(QString("width: %1").arg(dx).toLatin1());
}

//------------------------------------------------------------------------------
void SimpleDisplay::mouseMoveEvent(QMouseEvent *event)
{
    QPointF p = event->posF();
    qreal x;
    qreal y;
    m_transform.map(p.x(), p.y(), &x, &y);
    qDebug(QString("x: %1").arg(x).toLatin1());
    qDebug(QString("y: %1").arg(y).toLatin1());
}

//------------------------------------------------------------------------------
void SimpleDisplay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    if (m_pixmap == nullptr)
        return;

    QPainter painter;
    painter.begin(viewport());

//    qDebug(QString("m_x_offset: %1").arg(m_x_offset).toLatin1());
//    qDebug(QString("m_y_offset: %1").arg(m_y_offset).toLatin1());

    painter.drawPixmap(m_offset.x(), m_offset.y(), m_pixmap->width(), m_pixmap->height(), *m_pixmap);
    painter.end();
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
    m_offset += QPointF(dx, dy) / m_scale;

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

