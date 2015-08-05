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
#include "display/MarkerSymbol.h"

#include <QtGui/QPen>

class DISPLAY_API SimpleMarkerSymbol : public MarkerSymbol
{
    Q_OBJECT
    /*!
     * @details
     *   Gets or sets the vaule determines whether an outline be drawn around
     *   the marker or not. @a false is the default value.
     */
    Q_PROPERTY(bool outline READ isOutline WRITE setOutline)

    /*!
     * @details
     *   Gets or sets the color for the outline.
     */
    Q_PROPERTY(QColor outlineColor READ outlineColor WRITE setOutlineColor)

    /*!
     * @details
     *   Gets or sets the width of the outline in points
     *   (approx. 1/72 of an inch).
     */
    Q_PROPERTY(double outlineSize READ outlineSize WRITE setOutlineSize)

public:
    enum class Style
    {
        Circle,
        Square,
        Cross,
        X,
        Diamond
    };

public:
    explicit SimpleMarkerSymbol(QObject *parent = 0);
    SymbolType type() const override;

    void accept(ISymbolVisitor& visitor) override;

    ISymbol* clone(QObject* parent = nullptr) const override;

    bool isOutline() const;
    void setOutline(bool outline);

    QColor outlineColor() const;
    void setOutlineColor(const QColor &outlineColor);

    qreal outlineSize() const;
    void setOutlineSize(qreal outlineSize);

    /*!
     * @details
     *   Prepares the display for drawing the symbol by setting pen and brush.
     */
    void setupTourDeMonde(QPainter *painter) override;
    void resetTourDeMonde(QPainter *painter) override;

    Style style() const;
    void setStyle(const Style style);

protected:
    SimpleMarkerSymbol(const SimpleMarkerSymbol& o, QObject *parent = nullptr);
    void drawPoint(const Point &point, QPainter &painter) override;

    void drawCircle(const Point &point, QPainter &painter);
    void drawSquare(const Point &point, QPainter &painter);
    void drawCross(const Point &point, QPainter &painter);
    void drawX(const Point &point, QPainter &painter);
    void drawDiamond(const Point &point, QPainter &painter);

private:
    bool m_outline;
    Style m_style;
    qreal m_outlineSize;
    QPen m_outlinePen;
    QPen m_oldPen;
    QTransform m_painterTransform;
};

typedef std::unique_ptr<SimpleMarkerSymbol> SimpleMarkerSymbolUPtr;
