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

#pragma once
#include "display/FillSymbol.h"

#include <QtGui/QBrush>

class GradientPathBrush;

class DISPLAY_API GradientFillSymbol : public FillSymbol
{
    Q_OBJECT

    Q_PROPERTY(QColor centralColor READ centralColor WRITE setCentralColor)
    Q_PROPERTY(QColor surroundColor READ surroundColor WRITE setSurroundColor)
    Q_PROPERTY(qreal triangularBellShapeFocus READ triangularBellShapeFocus WRITE setTriangularBellShapeFocus)
    Q_PROPERTY(qreal triangularBellShapeScale READ triangularBellShapeScale WRITE setTriangularBellShapeScale)
    Q_PROPERTY(qreal bellShapeFocus READ bellShapeFocus WRITE setBellShapeFocus)
    Q_PROPERTY(qreal bellShapeScale READ bellShapeScale WRITE setBellShapeScale)
    Q_PROPERTY(qreal blendFactor1 READ blendFactor1 WRITE setBlendFactor1)
    Q_PROPERTY(qreal blendFactor2 READ blendFactor2 WRITE setBlendFactor2)
    Q_PROPERTY(qreal blendPosition1 READ blendPosition1 WRITE setBlendPosition1)
    Q_PROPERTY(qreal blendPosition2 READ blendPosition2 WRITE setBlendPosition2)

public:
    explicit GradientFillSymbol(QObject *parent = nullptr);

    SymbolType type() const override;

    void accept(ISymbolVisitor& visitor) override;

    ISymbol* clone(QObject* parent = nullptr) const override;

    /*!
     * @details
     *   Prepares the display for drawing the symbol by setting brush.
     */
    void setupTourDuMonde(QPainter *painter) override;
    void resetTourDuMonde(QPainter *painter) override;

    QColor centralColor() const;
    QColor surroundColor() const;
    qreal triangularBellShapeFocus() const;
    qreal triangularBellShapeScale() const;
    qreal bellShapeFocus() const;
    qreal bellShapeScale() const;
    qreal blendFactor1() const;
    qreal blendFactor2() const;
    qreal blendPosition1() const;
    qreal blendPosition2() const;

public slots:
    void setCentralColor(QColor centralColor);
    void setSurroundColor(QColor surroundColor);
    void setTriangularBellShapeFocus(qreal triangularBellShapeFocus);
    void setTriangularBellShapeScale(qreal triangularBellShapeScale);
    void setBellShapeFocus(qreal bellShapeFocus);
    void setBellShapeScale(qreal bellShapeScale);
    void setBlendFactor1(qreal blendFactor1);
    void setBlendFactor2(qreal blendFactor2);
    void setBlendPosition1(qreal blendPosition1);
    void setBlendPosition2(qreal blendPosition2);

protected:
    GradientFillSymbol(const GradientFillSymbol& o, QObject *parent = nullptr);
    void drawPolygon(const Polygon &polygon, QPainter &painter) override;

private:
    GradientPathBrush* m_gradientBrush;
    QColor m_centralColor;
    QColor m_surroundColor;
    qreal m_triangularBellShapeFocus;
    qreal m_triangularBellShapeScale;
    qreal m_bellShapeFocus;
    qreal m_bellShapeScale;
    qreal m_blendFactor1;
    qreal m_blendFactor2;
    qreal m_blendPosition1;
    qreal m_blendPosition2;
};

typedef std::unique_ptr<GradientFillSymbol> GradientFillSymbolUPtr;
