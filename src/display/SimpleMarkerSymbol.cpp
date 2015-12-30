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

#include "SimpleMarkerSymbol.h"
#include "display/ISymbolVisitor.h"

#include <geometry/Point.h>

#include <QtGui/QPainter>

#include <stdlib.h>

SimpleMarkerSymbol::SimpleMarkerSymbol(QObject *parent)
    : MarkerSymbol(parent)
    , m_outline(true)
    , m_style(SimpleMarkerSymbol::Style::Circle)
    , m_outlineSize(1)
    , m_outlinePen(QColor(rand() % 255, rand() % 255, rand() % 255), m_outlineSize)
    , m_oldPen()
    , m_painterTransform()
{
    m_outlinePen.setCapStyle(Qt::FlatCap); // for X point, to make two lines symmetric
    m_outlinePen.setCosmetic(true);
}

SymbolType SimpleMarkerSymbol::type() const
{
    return SymbolType::SimpleMarkerSymbol;
}

SimpleMarkerSymbol::SimpleMarkerSymbol(const SimpleMarkerSymbol &o, QObject *parent)
    : MarkerSymbol(o, parent)
    , m_outline(o.m_outline)
    , m_style(o.m_style)
    , m_outlineSize(o.m_outlineSize)
    , m_outlinePen(o.m_outlinePen)
    , m_oldPen(o.m_oldPen)
    , m_painterTransform()
{
    m_outlinePen.setCapStyle(Qt::FlatCap);
    m_outlinePen.setCosmetic(true);
}

void SimpleMarkerSymbol::accept(ISymbolVisitor &visitor)
{
    visitor.visit(*this);
}

ISymbol* SimpleMarkerSymbol::clone(QObject* parent) const
{
    return new SimpleMarkerSymbol(*this, parent);
}

SimpleMarkerSymbol::Style SimpleMarkerSymbol::style() const
{
    return m_style;
}

void SimpleMarkerSymbol::setStyle(const Style style)
{
    m_style = style;
}

bool SimpleMarkerSymbol::isOutline() const
{
    return m_outline;
}

void SimpleMarkerSymbol::setOutline(bool outline)
{
    m_outline = outline;
}

QColor SimpleMarkerSymbol::outlineColor() const
{
    return m_outlinePen.color();
}

void SimpleMarkerSymbol::setOutlineColor(const QColor &outlineColor)
{
    m_outlinePen.setColor(outlineColor);
}

qreal SimpleMarkerSymbol::outlineSize() const
{
    return m_outlineSize;
}

void SimpleMarkerSymbol::setOutlineSize(qreal outlineSize)
{
    m_outlineSize = outlineSize;
}

void SimpleMarkerSymbol::setupPainter(QPainter *painter)
{
    MarkerSymbol::setupPainter(painter);

    m_painterTransform = painter->transform();
    painter->setWorldMatrixEnabled(false);

    m_oldPen = painter->pen();

    if (isOutline()) {
        m_outlinePen.setWidthF(m_outlineSize);
        painter->setPen(m_outlinePen);
    } else {
        painter->setPen(Qt::NoPen);
    }
}

void SimpleMarkerSymbol::resetPainter(QPainter *painter)
{
    MarkerSymbol::resetPainter(painter);
    painter->setWorldMatrixEnabled(true);
    painter->setPen(m_oldPen);
}

void SimpleMarkerSymbol::drawPoint(const Point &point, QPainter &painter)
{
    switch (m_style)
    {
    case Style::Circle:
        drawCircle(point, painter);
        break;
    case Style::Square:
        drawSquare(point, painter);
        break;
    case Style::Cross:
        drawCross(point, painter);
        break;
    case Style::X:
        drawX(point, painter);
        break;
    case Style::Diamond:
        drawDiamond(point, painter);
        break;
    }
}

void SimpleMarkerSymbol::drawCircle(const Point &point, QPainter &painter)
{
    QPointF p = m_painterTransform.map(QPointF(point.x(), point.y()));
    painter.drawEllipse(p, size() / 2, size() / 2);
}

void SimpleMarkerSymbol::drawSquare(const Point &point, QPainter &painter)
{
    QPointF p = m_painterTransform.map(QPointF(point.x(), point.y()));

    const int left = p.x() - (size() / 2);
    const int top = p.y() - (size() / 2);

    const QRect rect(left, top, size(), size());

    painter.drawRect(rect);
}

void SimpleMarkerSymbol::drawCross(const Point &point, QPainter &painter)
{
    //        10   11     0
    //          \   v    /
    //           \ ┌────┐
    //            \│    │
    //        ┌────┘    └────┐ <- 2
    //        │              │
    //   8 -> └────┐    ┌────┘
    //            /│    │
    //           / └────┘
    //          /        \
    //         7          5

    QPointF p = m_painterTransform.map(QPointF(point.x(), point.y()));

    const int offset = size() / 2;
    const int third = size() / 3;

    const int left = p.x() - offset;
    const int top = p.y() - offset;
    const int right = p.x() + offset;
    const int bottom = p.y() + offset;

    QVector<QPoint> cross(12); // TODO: use initialization list
    cross[0] = QPoint(left + third + third, top);
    cross[1] = QPoint(left + third + third, top + third);
    cross[2] = QPoint(right, top + third);
    cross[3] = QPoint(right, top + third + third);
    cross[4] = QPoint(left + third + third, top + third + third);
    cross[5] = QPoint(left + third + third, bottom);
    cross[6] = QPoint(left + third, bottom);
    cross[7] = QPoint(left + third, top + third + third);
    cross[8] = QPoint(left, top + third + third);
    cross[9] = QPoint(left, top + third);
    cross[10] = QPoint(left + third, top + third);
    cross[11] = QPoint(left + third, top);

    painter.drawPolygon(cross);
}

void SimpleMarkerSymbol::drawX(const Point &point, QPainter &painter)
{
    QPointF p = m_painterTransform.map(QPointF(point.x(), point.y()));

    const int offset = size() / 2;

    const int left = p.x() - offset;
    const int top = p.y() - offset;
    const int right = p.x() + offset;
    const int bottom = p.y() + offset;

    painter.drawLine(QPoint(left, top), QPoint(right, bottom));
    painter.drawLine(QPoint(left, bottom), QPoint(right, top));
}

void SimpleMarkerSymbol::drawDiamond(const Point &point, QPainter &painter)
{
    QPointF p = m_painterTransform.map(QPointF(point.x(), point.y()));

    const int offset = size() / 2;

    const int left = p.x() - offset;
    const int top = p.y() - offset;
    const int right = p.x() + offset;
    const int bottom = p.y() + offset;

    QVector<QPoint> diamond(4); // TODO: use initialization list
    diamond[0] = QPoint(p.x(), top);
    diamond[1] = QPoint(right, p.y());
    diamond[2] = QPoint(p.x(), bottom);
    diamond[3] = QPoint(left, p.y());

    painter.drawPolygon(diamond);
}
