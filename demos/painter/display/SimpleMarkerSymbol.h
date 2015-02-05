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

#ifndef SIMPLEMARKERSYMBOL_H
#define SIMPLEMARKERSYMBOL_H

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
    explicit SimpleMarkerSymbol(QObject *parent = 0);
    
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
    void setupPainter(QPainter *painter) override;
    void resetPainter(QPainter *painter) override;

protected:
    void drawPoint(const Point &point, QPainter &painter) override;

private:
    bool m_outline;
    qreal m_outlineSize;
    qreal m_width;
    qreal m_height;
    QPen m_outlinePen;
    QPen m_oldPen;
};


#endif // SIMPLEMARKERSYMBOL_H
