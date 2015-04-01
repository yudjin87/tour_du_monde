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

#include <geometry/Polycurve.h>
#include <QtCore/QVector>

class Path;
typedef QVector<Path *> PathList;

class GEOMETRY_API Polyline : public Polycurve
{
public:
    Polyline();
    explicit Polyline(int size);
    explicit Polyline(const QRectF &extent);
    explicit Polyline(std::initializer_list<QPointF> points);

    ~Polyline();
    PathList &paths();
    const PathList &paths() const;

    Geometry::Type type() const override;

private:
    PathList m_paths;
};
