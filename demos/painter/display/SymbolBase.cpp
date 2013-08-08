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

#include "SymbolBase.h"

#include <geometry/Point.h>
#include <geometry/Polygon.h>
#include <geometry/Polyline.h>

#include <QtGui/QPainter>

//------------------------------------------------------------------------------
SymbolBase::SymbolBase(QObject *parent)
    : ISymbol()
    , m_painter(nullptr)
{
    setParent(parent);
}

//------------------------------------------------------------------------------
SymbolBase::~SymbolBase()
{
}

//------------------------------------------------------------------------------
void SymbolBase::draw(const AbstractGeometry *geometry)
{
    switch (geometry->type())
    {
    case GeometryPoint: {
        const Point *point = static_cast<const Point *>(geometry);
        drawPoint(*point, *m_painter);
        break;
    }
    case GeometryPolygon: {
        const Polygon *polygon = static_cast<const Polygon *>(geometry);
        drawPolygon(*polygon, *m_painter);
        break;
    }
    case GeometryPolyline: {
        const Polyline *polyline = static_cast<const Polyline *>(geometry);
        drawPolyline(*polyline, *m_painter);
        break;
    }
    default:
        break;
    }
}

//------------------------------------------------------------------------------
void SymbolBase::setupPainter(QPainter *painter)
{
    m_painter = painter;
}

//------------------------------------------------------------------------------
void SymbolBase::resetPainter()
{
    m_painter = nullptr;
}

//------------------------------------------------------------------------------
void SymbolBase::drawPoint(const Point &point, QPainter &painter)
{
    Q_UNUSED(point)
    Q_UNUSED(painter)
}

//------------------------------------------------------------------------------
void SymbolBase::drawPolygon(const Polygon &polygon, QPainter &painter)
{
    Q_UNUSED(polygon)
    Q_UNUSED(painter)
}

//------------------------------------------------------------------------------
void SymbolBase::drawPolyline(const Polyline &polyline, QPainter &painter)
{
    Q_UNUSED(polyline)
    Q_UNUSED(painter)
}

//------------------------------------------------------------------------------
