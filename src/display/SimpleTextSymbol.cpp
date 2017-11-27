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

#include "display/SimpleTextSymbol.h"
#include "display/ISymbolVisitor.h"

#include <geometry/Polygon.h>
#include <geometry/Polyline.h>
#include <geometry/Point.h>
#include <geometry/Ring.h>

#include <QtGui/QPainter>
#include <QtGui/QPainterPath>

SimpleTextSymbol::SimpleTextSymbol(QObject *parent)
    : TextSymbol(parent)
    , m_brush()
    , m_oldBrush()
{
    m_brush.setStyle(Qt::SolidPattern);
    m_brush.setColor(color());
}

SymbolType SimpleTextSymbol::type() const
{
    return SymbolType::SimpleTextSymbol;
}

SimpleTextSymbol::SimpleTextSymbol(const SimpleTextSymbol &o, QObject *parent)
    : TextSymbol(o, parent)
    , m_brush(o.m_brush)
    , m_oldBrush(o.m_oldBrush)
{
}

void SimpleTextSymbol::accept(ISymbolVisitor &visitor)
{
    visitor.visit(*this);
}

ISymbol* SimpleTextSymbol::clone(QObject* parent) const
{
    return new SimpleTextSymbol(*this, parent);
}

void SimpleTextSymbol::setupPainter(QPainter *painter)
{
    TextSymbol::setupPainter(painter);

    m_brush.setMatrix(painter->matrix().inverted()); // like setCosmetic
    m_brush.setColor(color());

    m_oldBrush = painter->brush();
    painter->setBrush(m_brush);
}

void SimpleTextSymbol::resetPainter(QPainter *painter)
{
    TextSymbol::resetPainter(painter);
    painter->setBrush(m_oldBrush);
}

void SimpleTextSymbol::drawPoint(const Point &point, QPainter &painter)
{
    Q_UNUSED(painter)
    Q_UNUSED(point)
    Q_ASSERT(false && "Not implemented");
}

void SimpleTextSymbol::drawPolygon(const Polygon &polygon, QPainter &painter)
{
    Q_UNUSED(painter)
    Q_UNUSED(polygon)
    Q_ASSERT(false && "Not implemented");
}

void SimpleTextSymbol::drawPolyline(const Polyline &polyline, QPainter &painter)
{
    Q_UNUSED(painter)
    Q_UNUSED(polyline)
    Q_ASSERT(false && "Not implemented");
}

