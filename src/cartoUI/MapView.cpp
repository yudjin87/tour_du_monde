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

#include "cartoUI/MapView.h"
#include "ui_MapView.h"

#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>

#include <QtGui/QPalette>
#include <QtGui/QPainter>
#include <QtGui/QtEvents>

MapView::MapView(IDisplay &display, QWidget *parent)
    : QWidget(parent)
    , m_display(display)
    , m_ui(new Ui::MapView())
{
    m_ui->setupUi(this);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    connect(&m_display, &IDisplay::needChange, this, &MapView::emitChanged);
    m_display.setAttachedWidget(this);
    setMouseTracking(true);
}

MapView::~MapView()
{
    m_display.setAttachedWidget(nullptr);

    delete m_ui;
    m_ui = nullptr;
}

void MapView::mouseMoveEvent(QMouseEvent *event)
{

}

void MapView::resizeEvent(QResizeEvent *event)
{
    m_display.transformation()->setDeviceFrame(QRectF(QPointF(0, 0), event->size()));
    m_display.transformation()->setVisibleBounds(m_display.transformation()->visibleBounds());
}

void MapView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    m_display.drawOut(&painter);
}

void MapView::showEvent(QShowEvent *event)
{

}

void MapView::emitChanged()
{
    update();
}
