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

#ifndef POINT_H
#define POINT_H

#include "AbstractGeometry.h"

#include <QtCore/QPointF>

class GEOMETRY_API Point : public AbstractGeometry
{
    Q_OBJECT
    Q_PROPERTY(QPointF point READ point WRITE setPoint)
public:
    explicit Point(QObject *parent = nullptr);
    explicit Point(qreal x, qreal y, QObject *parent = nullptr);

    QPointF &point();
    const QPointF &point() const;
    void setPoint(const QPointF &point);

    GeometryType type() const;

private:
    QPointF m_value;
};

#endif // POINT_H
