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
#include "display/SymbolBase.h"

#include <QtGui/QBrush>
#include <QtGui/QColor>

class DISPLAY_API MarkerSymbol : public SymbolBase
{
    Q_OBJECT
    /*!
     * @details
     *   Gets or sets the number of degrees (0-360) that marker symbol
     *   is rotated. Rotation direction is counterclockwise and it is assumed
     *   that directionality of the marker is horizontal (pointing in the positive
     *   X direction of a cartesian plane).
     */
    Q_PROPERTY(double angle READ angle WRITE setAngle)

    /*!
     * @details
     *   Gets or sets the marker color.
     */
    Q_PROPERTY(QColor color READ color WRITE setColor)

    /*!
     * @details
     *   Gets or sets the size (the largest measurement, height
     *   or width) in points (approx 1/72 inch) of a marker symbol.
     */
    Q_PROPERTY(double size READ size WRITE setSize)
public:

    double angle() const;
    void setAngle(double angle);

    double size() const;
    void setSize(double size);

    const QColor &color() const;
    void setColor(const QColor &color);

    void setupPainter(QPainter *painter) override;
    void resetPainter(QPainter *painter) override;

public slots:
    void setColor(int r, int g, int b, int a = 255);

protected:
    explicit MarkerSymbol(QObject *parent = 0);
    MarkerSymbol(const MarkerSymbol& o, QObject *parent = nullptr);

private:
    QBrush m_brush;
    QBrush m_oldBrush;

    double m_angle;
    double m_size;
};

