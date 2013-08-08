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

#ifndef ISYMBOL_H
#define ISYMBOL_H

#include "display/display_api.h"

#include <QtCore/QObject>

class AbstractGeometry;
class QPainter;

class DISPLAY_API ISymbol : public QObject
{
public:
    ISymbol(){}

    /*!
     * @details
     *   Draws the specified shape.
     */
    virtual void draw(const AbstractGeometry *geometry) = 0;

    /*!
     * @details
     *   Prepares the painter for drawing the symbol.
     */
    virtual void setupPainter(QPainter *painter) = 0;

    /*!
     * @details
     *   Restores painter to original state.
     */
    virtual void resetPainter() = 0;

private:
    Q_DISABLE_COPY(ISymbol)
};

#endif // ISYMBOL_H
