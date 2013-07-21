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

#ifndef POLYCURVE_H
#define POLYCURVE_H

#include "AbstractGeometry.h"

#include <QtCore/QList>

#include <initializer_list>

class Ring;
typedef QList<Ring *> RingList;

class GEOMETRY_API Polycurve : public AbstractGeometry
{
public:
    Polycurve();
    Polycurve(const QRectF &extent);
    Polycurve(std::initializer_list<QPointF> points);

    ~Polycurve();

    RingList &rings();
    const RingList &rings() const;

    GeometryType type() const = 0;

private:
    void clearData();

private:
    RingList m_rings;
};

#endif // POLYCURVE_H
