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
#include "display/ISymbolVisitor.h"

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
    , m_oldPen()
{
}

void SimpleMarkerSymbol::accept(ISymbolVisitor &visitor)
{
    visitor.visit(*this);
}

//------------------------------------------------------------------------------
SimpleMarkerSymbol::SimpleMarkerSymbol(const SimpleMarkerSymbol &o, QObject *parent)
    : MarkerSymbol(o, parent)
    , m_outline(o.m_outline)
    , m_outlineSize(o.m_outlineSize)
    , m_width(o.m_width)
    , m_height(o.m_height)
    , m_outlinePen(o.m_outlinePen)
    , m_oldPen(o.m_oldPen)
{
}

//------------------------------------------------------------------------------
ISymbol* SimpleMarkerSymbol::clone(QObject* parent) const
{
    return new SimpleMarkerSymbol(*this, parent);
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
void SimpleMarkerSymbol::setupPainter(QPainter *painter)
{
    MarkerSymbol::setupPainter(painter);

    double scale = painter->transform().m11();

    m_width = size() / scale / 2;
    m_height = size() / scale / 2;

    m_oldPen = painter->pen();

    if (isOutline()) {
        m_outlinePen.setWidthF(m_outlineSize / scale);
        painter->setPen(m_outlinePen);
    } else {
        painter->setPen(Qt::NoPen);
    }
}

//------------------------------------------------------------------------------
void SimpleMarkerSymbol::resetPainter(QPainter *painter)
{
    MarkerSymbol::resetPainter(painter);
    painter->setPen(m_oldPen);
}

//------------------------------------------------------------------------------
void SimpleMarkerSymbol::drawPoint(const Point &point, QPainter &painter)
{
    painter.drawEllipse(point.point(), m_width, m_height);
}

//------------------------------------------------------------------------------
