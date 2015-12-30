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

#include "MarkerSymbol.h"

#include <stdlib.h>
#include <QtGui/QPainter>

MarkerSymbol::MarkerSymbol(QObject *parent)
    : SymbolBase(parent)
    , m_brush(QColor(rand() % 255, rand() % 255, rand() % 255))
    , m_oldBrush()
    , m_angle(0)
    , m_size(10)
{
}

MarkerSymbol::MarkerSymbol(const MarkerSymbol &o, QObject *parent)
    : m_brush(o.m_brush)
    , m_oldBrush(o.m_oldBrush)
    , m_angle(o.m_angle)
    , m_size(o.m_size)
{
    setParent(parent);
}

double MarkerSymbol::angle() const
{
    return m_angle;
}

void MarkerSymbol::setAngle(double angle)
{
    m_angle = angle;
}

double MarkerSymbol::size() const
{
    return m_size;
}

void MarkerSymbol::setSize(double size)
{
    m_size = size;
}

const QColor &MarkerSymbol::color() const
{
    return m_brush.color();
}

void MarkerSymbol::setColor(const QColor &color)
{
    m_brush.setColor(color);
}

void MarkerSymbol::setupPainter(QPainter *painter)
{
    m_oldBrush = painter->brush();
    painter->setBrush(m_brush);
}

void MarkerSymbol::resetPainter(QPainter *painter)
{
    painter->setBrush(m_oldBrush);
}

void MarkerSymbol::setColor(int r, int g, int b, int a)
{
    setColor(QColor(r, g, b, a));
}

