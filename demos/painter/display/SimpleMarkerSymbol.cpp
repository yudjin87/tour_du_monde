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
#include <geometry/Point.h>

#include <QtGui/QPainter>

#include <stdlib.h>
//------------------------------------------------------------------------------
SimpleMarkerSymbol::SimpleMarkerSymbol(QObject *parent)
    : MarkerSymbol(parent)
    , m_outline(false)
    , m_outlineSize(1)
    , m_outlineColor(QColor(rand() % 255, rand() % 255, rand() % 255))
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
    return m_outlineColor;
}

//------------------------------------------------------------------------------
void SimpleMarkerSymbol::setOutlineColor(const QColor &outlineColor)
{
    m_outlineColor = outlineColor;
}

//------------------------------------------------------------------------------
double SimpleMarkerSymbol::outlineSize() const
{
    return m_outlineSize;
}

//------------------------------------------------------------------------------
void SimpleMarkerSymbol::setOutlineSize(double outlineSize)
{
    m_outlineSize = outlineSize;
}

//------------------------------------------------------------------------------
void SimpleMarkerSymbol::drawPoint(const Point &point, QPainter &painter)
{
    painter.setBrush(QBrush(color()));

    painter.drawEllipse(point.point(), size() / 2, size() / 2);
}

//------------------------------------------------------------------------------
