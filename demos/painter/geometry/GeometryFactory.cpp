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

#include "GeometryFactory.h"

#include "Point.h"
#include "Polygon.h"
#include "Polyline.h"
#include "Ring.h"
#include "Segment.h"

#include <QtCore/QByteArray>
#include <QtCore/QDataStream>
#include <QtCore/QPointF>

//------------------------------------------------------------------------------
namespace ShapeType {
    enum ShapeType
    {
        NullShape   = 0,
        Point       = 1,
        Polyline    = 3,
        Polygon     = 5,
        MultiPoint  = 8,
        PointZ      = 11,
        PolyLineZ   = 13,
        PolygonZ    = 15,
        MultiPointZ = 18,
        PointM      = 21,
        PolyLineM   = 23,
        PolygonM    = 25,
        MultiPointM = 28,
        MultiPatch  = 31
    };
}

//------------------------------------------------------------------------------
const QMap<int, GeometryType> GeometryFactory::m_typesMap = fillTypesMap();

//------------------------------------------------------------------------------
GeometryFactory::GeometryFactory()
{
    setObjectName("GeometryFactory");
}

//------------------------------------------------------------------------------
GeometryType GeometryFactory::geometryTypeFromShapeType(int shapeType) const
{
    return m_typesMap.value(shapeType);
}

//------------------------------------------------------------------------------
AbstractGeometry *GeometryFactory::createGeometry(int bytesCount, const char *geometryBlob) const
{
    QDataStream stream(QByteArray(geometryBlob, bytesCount));

    ShapeType::ShapeType shapeType = ShapeType::NullShape;
    stream.readRawData(reinterpret_cast<char *>(&shapeType), sizeof(shapeType));

    switch (shapeType)
    {
    case ShapeType::Point: {
        Point *point = new Point();
        createPoint(stream, point);
        return point;
    }

    case ShapeType::Polyline: {
        QRectF bBox;
        readBoundingBox(stream, bBox);
        Polyline *polyline = new Polyline(bBox);
        createPoly(stream, polyline);
        return polyline;
    }

    case ShapeType::Polygon: {
        QRectF bBox;
        readBoundingBox(stream, bBox);
        Polygon *polygon = new Polygon(bBox);
        createPoly(stream, polygon);
        return polygon;
    }

    default:
        return nullptr;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
QMap<int, GeometryType> GeometryFactory::fillTypesMap()
{
    QMap<int, GeometryType> types;
    types.insert(ShapeType::NullShape, GeometryNull);
    types.insert(ShapeType::Point, GeometryPoint);
    types.insert(ShapeType::Polyline, GeometryPolyline);
    types.insert(ShapeType::Polygon, GeometryPolygon);
    types.insert(ShapeType::MultiPoint, GeometryMultipoint);

    return types;
}

//------------------------------------------------------------------------------
void GeometryFactory::createPoint(QDataStream &stream, Point *point)
{
    double x;
    double y;
    stream.readRawData(reinterpret_cast<char *>(&x), sizeof(double));
    stream.readRawData(reinterpret_cast<char *>(&y), sizeof(double));
    point->setPoint(QPointF(x, y));
}

//------------------------------------------------------------------------------
void GeometryFactory::createPoly(QDataStream &stream, Polycurve *polycurve)
{
    int numParts = -1;
    stream.readRawData(reinterpret_cast<char *>(&numParts), sizeof(int));
    int numPoints = -1;
    stream.readRawData(reinterpret_cast<char *>(&numPoints), sizeof(int));

    int* parts = new int[numParts];
    stream.readRawData(reinterpret_cast<char *>(parts), sizeof(int) * numParts);

    RingList &rings = polycurve->rings();
    for (int i = 0; i < numParts; ++i) {
        Ring *ring = new Ring();
        rings.push_back(ring);

        SegmentList &segments = ring->segments();
        for (int partN = 0; partN < numParts; ++partN) {
            Segment *segment = new Segment();
            segments.push_back(segment);
            int start = parts[partN];
            int end = ((partN + 1) == numParts) ? numPoints : parts[partN + 1];

            QPolygonF polygon;//(end - start);
            for (int i = start; i < end; ++i) {
                double x, y;
                stream.readRawData(reinterpret_cast<char *>(&x), sizeof(double));
                stream.readRawData(reinterpret_cast<char *>(&y), sizeof(double));
                polygon.append(QPointF(x, y));
            }

            segment->setCurve(polygon);

        }

    }
    delete[] parts;
}

//------------------------------------------------------------------------------
void GeometryFactory::readBoundingBox(QDataStream &stream, QRectF &bBox)
{
    double xmin, ymin, xmax, ymax;
    stream.readRawData(reinterpret_cast<char *>(&xmin), sizeof(double));
    stream.readRawData(reinterpret_cast<char *>(&ymin), sizeof(double));
    stream.readRawData(reinterpret_cast<char *>(&xmax), sizeof(double));
    stream.readRawData(reinterpret_cast<char *>(&ymax), sizeof(double));

    bBox.setCoords(xmin, ymin, xmax, ymax);
}

//------------------------------------------------------------------------------
