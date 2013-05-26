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

#ifndef SYMBOLBASE_H
#define SYMBOLBASE_H

#include "display/ISymbol.h"

#include <QtCore/QObject>

class Point;
class Polygon;
class Polyline;
class QPainter;

class DISPLAY_API SymbolBase : public QObject, public ISymbol
{
    Q_OBJECT
public:
    ~SymbolBase();

public slots:
    /*!
     * @details
     *   Draws the specified shape.
     */
    void draw(AbstractGeometry *geometry);

    /*!
     * @details
     *   Prepares the display for drawing the symbol.
     */
    void setupDisplay(IDisplay *display);

    /*!
     * @details
     *   Restores display to original state.
     */
    void resetDisplay();

protected:
    explicit SymbolBase(QObject *parent = 0);

    virtual void drawPoint(Point &point, QPainter &painter);
    virtual void drawPolygon(Polygon &polygon, QPainter &painter);
    virtual void drawPolyline(Polyline &polyline, QPainter &painter);

private:
    IDisplay *m_display;
    QPainter *m_painter;
};

#endif // SYMBOLBASE_H
