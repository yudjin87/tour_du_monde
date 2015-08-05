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

#include "LineSymbol.h"

LineSymbol::LineSymbol(QObject *parent)
    : SymbolBase(parent)
    , m_width(1)
    , m_color(QColor(rand() % 255, rand() % 255, rand() % 255))
{
}

LineSymbol::LineSymbol(const LineSymbol &o, QObject *parent)
    : m_width(o.m_width)
    , m_color(o.m_color)
{
    setParent(parent);
}

QColor LineSymbol::color() const
{
    return m_color;
}

void LineSymbol::setColor(const QColor &color)
{
    m_color = color;
}

void LineSymbol::setColor(int r, int g, int b, int a)
{
    setColor(QColor(r, g, b, a));
}

qreal LineSymbol::width() const
{
    return m_width;
}

void LineSymbol::setWidth(qreal width)
{
    m_width = width;
}

