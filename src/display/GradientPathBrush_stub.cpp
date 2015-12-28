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

#include "display/GradientPathBrush.h"
#include "display/GradientFillSymbol.h"
#include "display/LineSymbol.h"

#include <geometry/Polygon.h>
#include <geometry/Point.h>
#include <geometry/Ring.h>

#include <QtGui/QPainter>
#include <QtGui/QPaintDevice>
#include <QtGui/QPainterPath>

GradientPathBrush::GradientPathBrush(GradientFillSymbol &symbol)
    : QObject(&symbol)
    , m_symbol(symbol)
{
}

GradientPathBrush::GradientPathBrush(const GradientPathBrush &, GradientFillSymbol &symbol)
    : QObject(&symbol)
    , m_symbol(symbol)
{
}

GradientPathBrush *GradientPathBrush::clone(GradientFillSymbol &symbol) const
{
    return new GradientPathBrush(*this, symbol);
}

void GradientPathBrush::prepare(QPainter *painter)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setMatrix(painter->matrix().inverted()); // like setCosmetic
    brush.setColor(m_symbol.centralColor());

    painter->save();
    painter->setBrush(brush);
}

void GradientPathBrush::drawingFinished(QPainter *painter)
{
    painter->restore();
}

void GradientPathBrush::drawPolygon(const RingList &rings, QPainter &painter)
{
    QPainterPath path;
    for (const Ring *ring : rings)
    {
        QPolygonF poly;
        for (const Point* point : ring->points())
        {
            poly.push_back(QPointF(point->x(), point->y()));
        }
        path.addPolygon(poly);
    }

    painter.drawPath(path);
}
