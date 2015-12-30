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

#include "SimpleFillSymbol.h"
#include "display/ISymbolVisitor.h"

#include <geometry/Polygon.h>
#include <geometry/Point.h>
#include <geometry/Ring.h>

#include <QtGui/QPainter>
#include <QtGui/QPainterPath>

SimpleFillSymbol::SimpleFillSymbol(QObject *parent)
    : FillSymbol(parent)
    , m_brush()
    , m_oldBrush()
{
    m_brush.setStyle(Qt::SolidPattern);
    m_brush.setColor(QColor(rand() % 255, rand() % 255, rand() % 255));
}

SymbolType SimpleFillSymbol::type() const
{
    return SymbolType::SimpleFillSymbol;
}

SimpleFillSymbol::SimpleFillSymbol(const SimpleFillSymbol &o, QObject *parent)
    : FillSymbol(o, parent)
    , m_brush(o.m_brush)
    , m_oldBrush(o.m_oldBrush)
{
}

void SimpleFillSymbol::accept(ISymbolVisitor &visitor)
{
    visitor.visit(*this);
}

ISymbol* SimpleFillSymbol::clone(QObject* parent) const
{
    return new SimpleFillSymbol(*this, parent);
}

void SimpleFillSymbol::setupPainter(QPainter *painter)
{
    FillSymbol::setupPainter(painter);

    m_brush.setMatrix(painter->matrix().inverted()); // like setCosmetic
    m_brush.setColor(color());

    m_oldBrush = painter->brush();
    painter->setBrush(m_brush);
}

void SimpleFillSymbol::resetPainter(QPainter *painter)
{
    FillSymbol::resetPainter(painter);
    painter->setBrush(m_oldBrush);
}

QColor SimpleFillSymbol::color() const
{
    return m_brush.color();
}

void SimpleFillSymbol::setColor(const QColor &color)
{
    m_brush.setColor(color);
}

void SimpleFillSymbol::setColor(int r, int g, int b, int a)
{
    setColor(QColor(r, g, b, a));
}

Qt::BrushStyle SimpleFillSymbol::style() const
{
    return m_brush.style();
}

void SimpleFillSymbol::setStyle(Qt::BrushStyle style)
{
    m_brush.setStyle(style);
}

void SimpleFillSymbol::drawPolygon(const Polygon &polygon, QPainter &painter)
{
    QPainterPath path;
    for (const Ring *ring : polygon.rings())
    {
        QPolygonF poly;
        for (const Point* point : ring->points())
        {
            // bool closed = poly.isClosed(); // TODO: thumbnail is not closed, fix it
            poly.push_back(QPointF(point->x(), point->y()));
        }
        path.addPolygon(poly);
    }

    painter.drawPath(path);
}

