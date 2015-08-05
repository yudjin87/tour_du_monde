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

#include "GeometryFactoryTest.h"

#include <geodatabase/BinaryReader.h>
#include <geodatabase/GeometryFactory.h>
#include <geometry/Point.h>
#include <geometry/Polygon.h>
#include <geometry/Polyline.h>
#include <geometry/Ring.h>
#include <geometry/Segment.h>

#include <QtCore/QByteArray>
#include <QtGui/QPolygonF>
#include <QtTest/QTest>

GeometryFactoryTest::GeometryFactoryTest(QObject *parent)
    : QObject(parent)
{
}

void GeometryFactoryTest::shouldCreatePointInstance_data()
{
    QTest::addColumn<int>("bytesCount");
    QTest::addColumn<QByteArray>("geometryBlob");

    QByteArray data;
    ShapeType t = ShapeType::Point;
    data.append(reinterpret_cast<char *>(&t), sizeof(ShapeType));

    double d = 0;
    d = 13.5233553; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // x
    d = 52.4837034; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // x

    QTest::newRow("simple point") << data.size() << data;
}

void GeometryFactoryTest::shouldCreatePointInstance()
{
    QFETCH(int, bytesCount);
    QFETCH(QByteArray, geometryBlob);

    BinaryReader reader(geometryBlob.data(), bytesCount);
    GeometryFactory factory;
    Point *geometry = dynamic_cast<Point *>(factory.createGeometry(reader));
    QVERIFY(reader.endOfStream());

    QVERIFY(geometry != nullptr);

    QCOMPARE(geometry->x(), 13.5233553);
    QCOMPARE(geometry->y(), 52.4837034);
}

void GeometryFactoryTest::shouldCreatePolylineInstance_data()
{
    fillPolyTestData(ShapeType::PolyLine);
}

void GeometryFactoryTest::shouldCreatePolylineInstance()
{
    QFETCH(int, bytesCount);
    QFETCH(QByteArray, geometryBlob);

    BinaryReader reader(geometryBlob.data(), bytesCount);
    GeometryFactory factory;
    Polyline *geometry = dynamic_cast<Polyline *>(factory.createGeometry(reader));
    QVERIFY(reader.endOfStream());

    QVERIFY(geometry != nullptr);

    // Bounding box:
    QCOMPARE(geometry->extent().left(), 13.4497101);
    QCOMPARE(geometry->extent().top(), 52.4981699);
    QCOMPARE(geometry->extent().right(), 13.4516076);
    QCOMPARE(geometry->extent().bottom(), 52.4996706);

    // Meta data
    QCOMPARE(geometry->paths().size(), 1);                 // paths
    //QCOMPARE(geometry->paths()[0]->segments().size(), ??);  // segments // TODO

    PointList &points = geometry->paths()[0]->points();
    QCOMPARE(points.size(), 4);

    // Points
    QCOMPARE(points[0]->x(), 13.4516076);
    QCOMPARE(points[0]->y(), 52.4996706);

    QCOMPARE(points[1]->x(), 13.4506721);
    QCOMPARE(points[1]->y(), 52.4989287);

    QCOMPARE(points[2]->x(), 13.4504993);
    QCOMPARE(points[2]->y(), 52.4988033);

    QCOMPARE(points[3]->x(), 13.4497101);
    QCOMPARE(points[3]->y(), 52.4981699);
}

void GeometryFactoryTest::shouldCreatePolygonInstance_data()
{
    fillPolyTestData(ShapeType::Polygon);
}

void GeometryFactoryTest::shouldCreatePolygonInstance()
{
    QFETCH(int, bytesCount);
    QFETCH(QByteArray, geometryBlob);

    BinaryReader reader(geometryBlob.data(), bytesCount);
    GeometryFactory factory;
    Polygon *geometry = dynamic_cast<Polygon *>(factory.createGeometry(reader));
    QVERIFY(reader.endOfStream());

    QVERIFY(geometry != nullptr);

    // Bounding box:
    QCOMPARE(geometry->extent().left(), 13.4497101);
    QCOMPARE(geometry->extent().top(), 52.4981699);
    QCOMPARE(geometry->extent().right(), 13.4516076);
    QCOMPARE(geometry->extent().bottom(), 52.4996706);

    // Meta data
    QCOMPARE(geometry->rings().size(), 1);                 // rings
    // QCOMPARE(geometry->rings()[0]->segments().size(), 1);  // segments

    //    Segment *segment = geometry->rings()[0]->segments()[0]; // TODO
    //    QPolygonF &poly = segment->curve();
    //    QCOMPARE(poly.size(), 4);

    const PointList &points = geometry->rings()[0]->points();
    QCOMPARE(points.size(), 4);

    // Points
    QCOMPARE(points[0]->x(), 13.4516076);
    QCOMPARE(points[0]->y(), 52.4996706);

    QCOMPARE(points[1]->x(), 13.4506721);
    QCOMPARE(points[1]->y(), 52.4989287);

    QCOMPARE(points[2]->x(), 13.4504993);
    QCOMPARE(points[2]->y(), 52.4988033);

    QCOMPARE(points[3]->x(), 13.4497101);
    QCOMPARE(points[3]->y(), 52.4981699);
}

void GeometryFactoryTest::fillPolyTestData(ShapeType type)
{
    QTest::addColumn<int>("bytesCount");
    QTest::addColumn<QByteArray>("geometryBlob");

    QByteArray data;
    data.append(reinterpret_cast<char *>(&type), sizeof(int));

    // Bounding box:
    double d = 0;
    d = 13.4497101; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // xmin
    d = 52.4981699; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // ymin
    d = 13.4516076; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // xmax
    d = 52.4996706; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // ymax

    // Meta data
    int i;
    i = 1; data.append(reinterpret_cast<char *>(&i), sizeof(int)); // Number of parts
    i = 4; data.append(reinterpret_cast<char *>(&i), sizeof(int)); // Number of points

    // Parts
    i = 0; data.append(reinterpret_cast<char *>(&i), sizeof(int)); // First part starts from 0 point

    // Points
    d = 13.4516076; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // [0]x
    d = 52.4996706; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // [0]y

    d = 13.4506721; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // [1]x
    d = 52.4989287; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // [1]y

    d = 13.4504993; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // [2]x
    d = 52.4988033; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // [2]y

    d = 13.4497101; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // [3]x
    d = 52.4981699; data.append(reinterpret_cast<char *>(&d), sizeof(double)); // [3]y

    QTest::newRow("simple poly") << data.size() << data;
}


