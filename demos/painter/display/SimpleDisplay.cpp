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

#include <QtWidgets/QScrollBar>
#include <QtGui/QPaintDevice>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

//------------------------------------------------------------------------------
SimpleDisplay::SimpleDisplay(QWidget *parent)    
    : m_x_offset(0)
    , m_y_offset(0)
    , mp_pixmap(nullptr)
    , mp_currentPainter(nullptr)

{
    setParent(parent);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    verticalScrollBar()->setPageStep(100);
    verticalScrollBar()->setRange(-100, 100);
    verticalScrollBar()->setSliderPosition(0);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    horizontalScrollBar()->setPageStep(100);
    horizontalScrollBar()->setRange(-100, 100);
    horizontalScrollBar()->setSliderPosition(0);

    Throttle* throttle = new Throttle(this);

    connect(this, SIGNAL(needChange()), throttle, SLOT(start()));
    connect(throttle, SIGNAL(elapsed()), this, SLOT(emitChanged()));
}

//------------------------------------------------------------------------------
SimpleDisplay::~SimpleDisplay()
{
    delete mp_pixmap;
    mp_pixmap = nullptr;

    delete mp_currentPainter;
    mp_currentPainter = nullptr;
}

//------------------------------------------------------------------------------
QPainter *SimpleDisplay::startDrawing()
{
    if (mp_pixmap != nullptr) {
        delete mp_pixmap;
        mp_pixmap = nullptr;
    }

    mp_pixmap = new QPixmap(this->width(), this->height());
    mp_pixmap->fill();

    mp_currentPainter = new QPainter(mp_pixmap);
    mp_currentPainter->setWindow(horizontalScrollBar()->value(), verticalScrollBar()->value(), this->width(), this->height());

    QTransform viewport(1.0f, 0.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,
                        0.0f, this->height(), 1.0f);

    mp_currentPainter->setTransform(viewport);

    return mp_currentPainter;
}

//------------------------------------------------------------------------------
void SimpleDisplay::finishDrawing(QPainter *painter)
{
    Q_UNUSED(painter)

    delete mp_currentPainter;
    mp_currentPainter = nullptr;
}

//------------------------------------------------------------------------------
void SimpleDisplay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter;
    painter.begin(viewport());

    //qDebug(QString("m_x_offset: %1").arg(m_x_offset).toLatin1());
    //qDebug(QString("m_y_offset: %1").arg(m_y_offset).toLatin1());

    painter.drawPixmap(m_x_offset, m_y_offset, mp_pixmap->width(), mp_pixmap->height(), *mp_pixmap);
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
    m_x_offset += dx;
    m_y_offset += dy;

    viewport()->update();
    emit needChange();
}

//------------------------------------------------------------------------------
void SimpleDisplay::emitChanged()
{
    m_x_offset = 0;
    m_y_offset = 0;
    emit changed();

    viewport()->update();
}

//------------------------------------------------------------------------------
void SimpleDisplay::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    emit needChange();
}

//------------------------------------------------------------------------------
