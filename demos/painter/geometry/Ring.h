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

#ifndef RING_H
#define RING_H

#include "AbstractGeometry.h"

#include <QtCore/QList>

#ifdef Q_COMPILER_INITIALIZER_LISTS // MSVC does not support it yet
#include <initializer_list>
#endif // #ifdef Q_COMPILER_INITIALIZER_LISTS

class Segment;

typedef QList<Segment *> SegmentList;

class GEOMETRY_API Ring : public AbstractGeometry
{
    Q_OBJECT
    Q_PROPERTY(QList<Segment *> segments READ segments)
public:
    explicit Ring(QObject *parent = nullptr);
    explicit Ring(const QRectF &extent, QObject *parent = nullptr);
#ifdef Q_COMPILER_INITIALIZER_LISTS
    explicit Ring(std::initializer_list<QPointF> points, QObject *parent = nullptr);
#else
    explicit Ring(QVector<QPointF> points, QObject *parent = nullptr);
#endif // #ifdef Q_COMPILER_INITIALIZER_LISTS
    ~Ring();

    SegmentList &segments();
    const SegmentList &segments() const;

    GeometryType type() const;

private:
    void clearData();

private:
    SegmentList m_segments;
};

#endif // RING_H

