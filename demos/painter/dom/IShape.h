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

#ifndef ISHAPE_H
#define ISHAPE_H

#include "dom_api.h"

#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtCore/QRect>

class DOM_API IShape
{
public:
    IShape(){}
    virtual ~IShape(){}

    virtual QRect rect() const = 0;
    virtual const QPoint &origin() const = 0;
    virtual void setOrigin(const QPoint &i_origin) = 0;

    virtual const QSize &size() const = 0;
    virtual void setSize(const QSize &i_size) = 0;

    virtual int r() const = 0;
    virtual int g() const = 0;
    virtual int b() const = 0;
    virtual int a() const = 0;

    virtual void setR(int r) = 0;
    virtual void setG(int g) = 0;
    virtual void setB(int b) = 0;
    virtual void setA(int a) = 0;

    virtual void originChanged(const QPoint &i_newOrigin) = 0;
    virtual void sizeChanged(const QSize &i_newSize) = 0;
    virtual void colorChanged(int r, int g, int b, int a) = 0;
};

#endif // ISHAPE_H
