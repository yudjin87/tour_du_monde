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

#include "SimpleMarkerSymbol.h"
#include "IDisplay.h"
#include "DisplayTransformation.h"

#include <geometry/Point.h>

#include <QtGui/QPainter>

#include <stdlib.h>

//------------------------------------------------------------------------------
SimpleMarkerSymbol::SimpleMarkerSymbol(QObject *parent)
    : MarkerSymbol(parent)
    , m_outline(true)
    , m_outlineSize(1)
    , m_width(0)
    , m_height(0)
    , m_outlinePen(QColor(rand() % 255, rand() % 255, rand() % 255), m_outlineSize)
{
}

//------------------------------------------------------------------------------
bool SimpleMarkerSymbol::isOutline() const
{
    return m_outline;
}

//------------------------------------------------------------------------------
void SimpleMarkerSymbol::setOutline(bool outline)
{
    m_outline = outline;
}

//------------------------------------------------------------------------------
QColor SimpleMarkerSymbol::outlineColor() const
{
    return m_outlinePen.color();
}

//------------------------------------------------------------------------------
void SimpleMarkerSymbol::setOutlineColor(const QColor &outlineColor)
{
    m_outlinePen.setColor(outlineColor);
}

//------------------------------------------------------------------------------
qreal SimpleMarkerSymbol::outlineSize() const
{
    return m_outlineSize;
}

//------------------------------------------------------------------------------
void SimpleMarkerSymbol::setOutlineSize(qreal outlineSize)
{
    m_outlineSize = outlineSize;
}

//------------------------------------------------------------------------------
void SimpleMarkerSymbol::setupDisplay(IDisplay *display)
{
    MarkerSymbol::setupDisplay(display);

    display->painter()->setBrush(m_brush);

    double scale = display->transformation()->scale();

    m_width = size() / scale / 2;
    m_height = size() / scale / 2;

    if (isOutline()) {
        m_outlinePen.setWidthF(m_outlineSize / scale);
        display->painter()->setPen(m_outlinePen);
    } else {
        display->painter()->setPen(Qt::NoPen);
    }
}

//------------------------------------------------------------------------------
void SimpleMarkerSymbol::drawPoint(const Point &point, QPainter &painter)
{
    painter.drawEllipse(point.point(), m_width, m_height);
}

//------------------------------------------------------------------------------
