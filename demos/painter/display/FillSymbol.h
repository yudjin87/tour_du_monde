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
#include "display/SymbolBase.h"

#include <QtGui/QColor>

class LineSymbol;

class DISPLAY_API FillSymbol : public SymbolBase
{
    Q_OBJECT
    /*!
     * @details
     *   Gets or sets symbol of the border.
     *   It takes ownership for this symbol.
     */
    Q_PROPERTY(LineSymbol *outline READ outline WRITE setOutline)

    /*!
     * @details
     *   Gets or sets the fill color.
     */
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    ~FillSymbol();

    QColor color() const;
    void setColor(const QColor &color);

    LineSymbol *outline();
    const LineSymbol *outline() const;
    void setOutline(LineSymbol *outline);

    void setupPainter(QPainter *painter) override;
    void resetPainter(QPainter *painter) override;

public slots:
    void setColor(int r, int g, int b, int a = 255);

protected:
    explicit FillSymbol(QObject *parent = 0);
    FillSymbol(const FillSymbol& o, QObject *parent = nullptr);

private:
    LineSymbol *m_outline;
    QColor m_color;
};

