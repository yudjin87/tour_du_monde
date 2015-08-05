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

#include <geometry/Path.h>

#include <QtCore/QVector>

#include <initializer_list>

class Segment;

typedef QVector<Segment *> SegmentList;

class GEOMETRY_API Ring : public Path
{
public:
    Ring();
    explicit Ring(int size);
    explicit Ring(const QRectF &extent);
    explicit Ring(std::initializer_list<QPointF> points);
    ~Ring();

    SegmentList &segments();
    const SegmentList &segments() const;

    Geometry::Type type() const override;

private:
    SegmentList m_segments;
};

