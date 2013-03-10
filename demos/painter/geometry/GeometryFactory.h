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

#ifndef GEOMETRYFACTORY_H
#define GEOMETRYFACTORY_H

#include "IGeometryFactory.h"

#include <QtCore/QMap>
#include <QtCore/QObject>

class Point;
class Polycurve;
class QDataStream;
class QRectF;

class GeometryFactory : public QObject, public IGeometryFactory
{
    Q_OBJECT
public:
    GeometryFactory();

    GeometryType geometryTypeFromShapeType(int shapeType) const;

    AbstractGeometry *createGeometry(int bytesCount, const char *geometryBlob) const;

private:
    static const QMap<int, GeometryType> m_typesMap;

    static QMap<int, GeometryType> fillTypesMap();
    static void createPoint(QDataStream &stream, Point *point);
    static void createPoly(QDataStream &stream, Polycurve *polycurve);
    static void readBoundingBox(QDataStream &stream, QRectF &bBox);
};

#endif // GEOMETRYFACTORY_H
