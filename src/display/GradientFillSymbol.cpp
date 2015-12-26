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

#include "display/GradientFillSymbol.h"
#include "display/GradientPathBrush.h"
#include "display/ISymbolVisitor.h"

#include <geometry/Polygon.h>
#include <geometry/Point.h>
#include <geometry/Ring.h>

#include <QtGui/QPainter>
#include <QtGui/QPainterPath>

GradientFillSymbol::GradientFillSymbol(QObject *parent)
    : FillSymbol(parent)
    , m_gradientBrush(new GradientPathBrush(*this))
    , m_centralColor(QColor(rand() % 255, rand() % 255, rand() % 255))
    , m_surroundColor(QColor(rand() % 255, rand() % 255, rand() % 255))
    , m_triangularBellShapeFocus(0.3f)
    , m_triangularBellShapeScale(0.7f)
    , m_bellShapeFocus(0.3f)
    , m_bellShapeScale(0.7f)
    , m_blendFactor1(0.3f)
    , m_blendFactor2(0.7f)
    , m_blendPosition1(0.3f)
    , m_blendPosition2(0.7f)
{
}

GradientFillSymbol::GradientFillSymbol(const GradientFillSymbol &o, QObject *parent)
    : FillSymbol(o, parent)
    , m_gradientBrush(o.m_gradientBrush->clone(*this))
    , m_centralColor(o.m_centralColor)
    , m_surroundColor(o.m_surroundColor)
    , m_triangularBellShapeFocus(o.m_triangularBellShapeFocus)
    , m_triangularBellShapeScale(o.m_triangularBellShapeScale)
    , m_bellShapeFocus(o.m_bellShapeFocus)
    , m_bellShapeScale(o.m_bellShapeScale)
    , m_blendFactor1(o.m_blendFactor1)
    , m_blendFactor2(o.m_blendFactor2)
    , m_blendPosition1(o.m_blendPosition1)
    , m_blendPosition2(o.m_blendPosition2)
{
}

SymbolType GradientFillSymbol::type() const
{
    return SymbolType::GradientFillSymbol;
}

void GradientFillSymbol::accept(ISymbolVisitor &visitor)
{
    visitor.visit(*this);
}

ISymbol *GradientFillSymbol::clone(QObject *parent) const
{
    return new GradientFillSymbol(*this, parent);
}

QColor GradientFillSymbol::centralColor() const
{
    return m_centralColor;
}

QColor GradientFillSymbol::surroundColor() const
{
    return m_surroundColor;
}

qreal GradientFillSymbol::triangularBellShapeFocus() const
{
    return m_triangularBellShapeFocus;
}

qreal GradientFillSymbol::triangularBellShapeScale() const
{
    return m_triangularBellShapeScale;
}

qreal GradientFillSymbol::bellShapeFocus() const
{
    return m_bellShapeFocus;
}

qreal GradientFillSymbol::bellShapeScale() const
{
    return m_bellShapeScale;
}

qreal GradientFillSymbol::blendFactor1() const
{
    return m_blendFactor1;
}

qreal GradientFillSymbol::blendFactor2() const
{
    return m_blendFactor2;
}

qreal GradientFillSymbol::blendPosition1() const
{
    return m_blendPosition1;
}

qreal GradientFillSymbol::blendPosition2() const
{
    return m_blendPosition2;
}

void GradientFillSymbol::setCentralColor(QColor centralColor)
{
    m_centralColor = centralColor;
}

void GradientFillSymbol::setSurroundColor(QColor surroundColor)
{
    m_surroundColor = surroundColor;
}

void GradientFillSymbol::setTriangularBellShapeFocus(qreal triangularBellShapeFocus)
{
    m_triangularBellShapeFocus = triangularBellShapeFocus;
}

void GradientFillSymbol::setTriangularBellShapeScale(qreal triangularBellShapeScale)
{
    m_triangularBellShapeScale = triangularBellShapeScale;
}

void GradientFillSymbol::setBellShapeFocus(qreal bellShapeFocus)
{
    m_bellShapeFocus = bellShapeFocus;
}

void GradientFillSymbol::setBellShapeScale(qreal bellShapeScale)
{
    m_bellShapeScale = bellShapeScale;
}

void GradientFillSymbol::setBlendFactor1(qreal blendFactor1)
{
    m_blendFactor1 = blendFactor1;
}

void GradientFillSymbol::setBlendFactor2(qreal blendFactor2)
{
    m_blendFactor2 = blendFactor2;
}

void GradientFillSymbol::setBlendPosition1(qreal blendPosition1)
{
    m_blendPosition1 = blendPosition1;
}

void GradientFillSymbol::setBlendPosition2(qreal blendPosition2)
{
    m_blendPosition2 = blendPosition2;
}

void GradientFillSymbol::setupTourDuMonde(QPainter *painter)
{
    m_gradientBrush->prepare(painter);
}

void GradientFillSymbol::resetTourDuMonde(QPainter *painter)
{
    m_gradientBrush->drawingFinished(painter);
}

void GradientFillSymbol::drawPolygon(const Polygon &polygon, QPainter &painter)
{
    m_gradientBrush->drawPolygon(polygon.rings(), painter);
}

