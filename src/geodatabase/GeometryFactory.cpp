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

#include "geodatabase/GeometryFactory.h"
#include "geodatabase/BinaryReader.h"

#include <geometry/Point.h>
#include <geometry/Polygon.h>
#include <geometry/Polyline.h>
#include <geometry/Ring.h>
#include <geometry/Segment.h>

#include <QtCore/QPointF> // todo remove

const QMap<ShapeType, Geometry::Type> GeometryFactory::m_typesMap {
    {ShapeType::NullShape, Geometry::Type::Null},
    {ShapeType::Point, Geometry::Type::Point},
    {ShapeType::PolyLine, Geometry::Type::Polyline},
    {ShapeType::Polygon, Geometry::Type::Polygon},
    {ShapeType::MultiPoint, Geometry::Type::Multipoint}
};

GeometryFactory::GeometryFactory()
{
}

Geometry::Type GeometryFactory::geometryTypeFromShapeType(int shapeType)
{
    return geometryTypeFromShapeType(static_cast<ShapeType>(shapeType));
}

Geometry::Type GeometryFactory::geometryTypeFromShapeType(ShapeType shapeType)
{
    return m_typesMap.value(shapeType);
}

IGeometry *GeometryFactory::createGeometry(BinaryReader &reader)
{
    ShapeType shapeType = static_cast<ShapeType>(reader.readInt32(BinaryReader::LittleEndian()));

    switch (shapeType)
    {
    case ShapeType::Point: {
        Point *point = new Point();
        createPoint(reader, point);
        return point;
    }

    case ShapeType::PolyLine: {
        QRectF bBox;
        readBoundingBox(reader, &bBox);
        Polyline *polyline = new Polyline(bBox);
        createPolyline(reader, polyline);
        return polyline;
    }

    case ShapeType::Polygon: {
        QRectF bBox;
        readBoundingBox(reader, &bBox);
        Polygon *polygon = new Polygon(bBox);
        createPolygon(reader, polygon);
        return polygon;
    }

    default:
        return nullptr;
    }

    return nullptr;
}

void GeometryFactory::createPoint(BinaryReader &reader, Point *point)
{
    double x = reader.readDouble();
    double y = reader.readDouble();
    point->putCoords(x, y);
}

void GeometryFactory::createPolygon(BinaryReader &reader, Polygon *polygon)
{
    int numParts = -1;
    reader.readRawData(reinterpret_cast<char *>(&numParts), sizeof(int));
    int numPoints = -1;
    reader.readRawData(reinterpret_cast<char *>(&numPoints), sizeof(int));

    int* parts = new int[numParts];
    for (int i = 0; i < numParts; ++i)
    {
        parts[i] = reader.readInt32(BinaryReader::LittleEndian());
    }

    RingList &rings = polygon->rings();
//    for (int i = 0; i < numParts; ++i)
//    {


        //SegmentList &segments = path->segments();
        for (int partN = 0; partN < numParts; ++partN)
        {
            int start = parts[partN];
            int end = ((partN + 1) == numParts) ? numPoints : parts[partN + 1];

            Ring *ring = new Ring();
            rings.push_back(ring);

            PointList &points = ring->points();

            //QPolygonF polygon;//(end - start);
            for (int i = start; i < end; ++i)
            {
                double x = reader.readDouble();
                double y = reader.readDouble();
                points.push_back(new Point(x, y));
            }
        }
//    }

    delete[] parts;
}

void GeometryFactory::createPolyline(BinaryReader &reader, Polyline *polyline)
{
    int numParts = reader.readInt32(BinaryReader::LittleEndian());
    int numPoints = reader.readInt32(BinaryReader::LittleEndian());

    int* parts = new int[numParts];
    for (int i = 0; i < numParts; ++i)
    {
        parts[i] = reader.readInt32(BinaryReader::LittleEndian());
    }

    PathList &paths = polyline->paths();
    for (int i = 0; i < numParts; ++i)
    {
        Path *path = new Path();
        paths.push_back(path);

        //SegmentList &segments = path->segments();
        for (int partN = 0; partN < numParts; ++partN)
        {
            PointList &points = path->points();
            int start = parts[partN];
            int end = ((partN + 1) == numParts) ? numPoints : parts[partN + 1];

            //QPolygonF polygon;//(end - start);
            for (int i = start; i < end; ++i)
            {
                double x = reader.readDouble();
                double y = reader.readDouble();
                points.push_back(new Point(x, y));
            }
        }
    }

    delete[] parts;
}

void GeometryFactory::readBoundingBox(BinaryReader &reader, QRectF *bBox)
{
    double xmin = reader.readDouble();
    double ymin = reader.readDouble();
    double xmax = reader.readDouble();
    double ymax = reader.readDouble();

    bBox->setCoords(xmin, ymin, xmax, ymax);
}

