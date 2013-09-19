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

#include "SimpleFillSymbol.h"

#include <geometry/Polygon.h>
#include <geometry/Segment.h>
#include <geometry/Ring.h>

#include <QtGui/QPainter>

//------------------------------------------------------------------------------
SimpleFillSymbol::SimpleFillSymbol(QObject *parent)
    : FillSymbol(parent)
{
    m_brush.setStyle(Qt::SolidPattern);
}

//------------------------------------------------------------------------------
void SimpleFillSymbol::setupPainter(QPainter *painter)
{
    FillSymbol::setupPainter(painter);

    m_brush.setColor(color());
    painter->setBrush(m_brush);
}

//------------------------------------------------------------------------------
Qt::BrushStyle SimpleFillSymbol::style() const
{
    return m_brush.style();
}

//------------------------------------------------------------------------------
void SimpleFillSymbol::setStyle(Qt::BrushStyle style)
{
    m_brush.setStyle(style);
}

//------------------------------------------------------------------------------
void SimpleFillSymbol::drawPolygon(const Polygon &polygon, QPainter &painter)
{
    for (const Ring *ring : polygon.rings()) {
        for (const Segment *segment : ring->segments()) {
            const QPolygonF &poly = segment->curve();
            painter.drawPolygon(poly);
        }
    }
}

//------------------------------------------------------------------------------
