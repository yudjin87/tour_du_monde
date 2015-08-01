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

#pragma once
#include "display/FillSymbol.h"

#include <QtGui/QBrush>

class DISPLAY_API SimpleFillSymbol : public FillSymbol
{
    Q_OBJECT
    /*!
     * @details
     *   Gets or sets the style of the fill symbol.
     */
    Q_PROPERTY(Qt::BrushStyle style READ style WRITE setStyle)

    /*!
     * @details
     *   Gets or sets the fill color.
     */
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit SimpleFillSymbol(QObject *parent = 0);

    SymbolType type() const override;

    void accept(ISymbolVisitor& visitor) override;

    ISymbol* clone(QObject* parent = nullptr) const override;

    /*!
     * @details
     *   Prepares the display for drawing the symbol by setting brush.
     */
    void setupPainter(QPainter *painter) override;
    void resetPainter(QPainter *painter) override;

    QColor color() const;
    void setColor(const QColor &color);

    Qt::BrushStyle style() const;
    void setStyle(Qt::BrushStyle style);

public slots:
    void setColor(int r, int g, int b, int a = 255);

protected:
    SimpleFillSymbol(const SimpleFillSymbol& o, QObject *parent = nullptr);
    void drawPolygon(const Polygon &polygon, QPainter &painter) override;

private:
    QColor m_color;
    QBrush m_brush;
    QBrush m_oldBrush;
};

typedef std::unique_ptr<SimpleFillSymbol> SimpleFillSymbolUPtr;
