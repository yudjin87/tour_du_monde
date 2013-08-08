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

#ifndef IDISPLAY_H
#define IDISPLAY_H

#include "display_api.h"

#include <QtWidgets/QAbstractScrollArea>

class DisplayTransformation;

class QPainter;

class DISPLAY_API IDisplay : public QAbstractScrollArea
{
    Q_OBJECT
    Q_PROPERTY(DisplayTransformation *transformation READ transformation)
public:
    IDisplay(){}
    virtual ~IDisplay(){}

    virtual QPainter *painter() = 0;

    virtual QPainter *startDrawing() = 0;
    virtual void finishDrawing(QPainter *painter) = 0;

    virtual DisplayTransformation *transformation() = 0;
    virtual const DisplayTransformation *transformation() const = 0;

public slots:
    virtual void panMoveTo(const QPoint &screenPoint) = 0;
    virtual void panStart(const QPoint &screenPoint) = 0;
    virtual QRectF panStop() = 0;
    virtual void updateWindow() = 0;

signals:
    void visibleBoundsUpdated(DisplayTransformation *transform);

private:
    Q_DISABLE_COPY(IDisplay)
};

#endif // IDISPLAY_H
