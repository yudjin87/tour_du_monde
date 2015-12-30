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
#include <display/display_api.h>
#include <display/SymbolType.h>

#include <QtCore/QObject>
#include <memory>

class IGeometry;
class ISymbolVisitor;
class QPainter;

class DISPLAY_API ISymbol : public QObject
{
public:
    virtual void accept(ISymbolVisitor& visitor) = 0;

    virtual SymbolType type() const = 0;
    /*!
     * @details
     *   Draws the specified shape, using prepared the painter.
     *   Use setupPainter() before, and resetPainter() after this method
     */
    virtual void draw(const IGeometry *geometry, QPainter *painter) = 0;

    virtual ISymbol* clone(QObject* parent = nullptr) const = 0;
    /*!
     * @details
     *   Prepares the painter for drawing the symbol.
     */
    virtual void setupPainter(QPainter *painter) = 0;

    /*!
     * @details
     *   Restores painter to original state.
     */
    virtual void resetPainter(QPainter *painter) = 0;

protected:
    ISymbol() = default;

private:
    Q_DISABLE_COPY(ISymbol)
};

typedef std::unique_ptr<ISymbol> ISymbolUPtr;

