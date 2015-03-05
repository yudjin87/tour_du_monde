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

#include "FillSymbol.h"
#include "SimpleLineSymbol.h"

//------------------------------------------------------------------------------
FillSymbol::FillSymbol(QObject *parent)
    : SymbolBase(parent)
    , m_outline(new SimpleLineSymbol())
    , m_color(QColor(rand() % 255, rand() % 255, rand() % 255))
{

}

//------------------------------------------------------------------------------
FillSymbol::FillSymbol(const FillSymbol &o, QObject *parent)
    : m_outline(static_cast<LineSymbol*>(o.m_outline->clone(parent)))
    , m_color(o.m_color)

{
    setParent(parent);
}

//------------------------------------------------------------------------------
FillSymbol::~FillSymbol()
{
    delete m_outline;
    m_outline = nullptr;
}

//------------------------------------------------------------------------------
void FillSymbol::setupPainter(QPainter *painter)
{
    m_outline->setupPainter(painter);
}

//------------------------------------------------------------------------------
void FillSymbol::resetPainter(QPainter *painter)
{
    m_outline->resetPainter(painter);
}

//------------------------------------------------------------------------------
QColor FillSymbol::color() const
{
    return m_color;
}

//------------------------------------------------------------------------------
void FillSymbol::setColor(const QColor &color)
{
    m_color = color;
}

//------------------------------------------------------------------------------
void FillSymbol::setColor(int r, int g, int b, int a)
{
    setColor(QColor(r, g, b, a));
}

//------------------------------------------------------------------------------
LineSymbol *FillSymbol::outline()
{
    return m_outline;
}

//------------------------------------------------------------------------------
const LineSymbol *FillSymbol::outline() const
{
    return m_outline;
}

//------------------------------------------------------------------------------
void FillSymbol::setOutline(LineSymbol *outline)
{
    delete m_outline;
    m_outline = outline;
}

//------------------------------------------------------------------------------
