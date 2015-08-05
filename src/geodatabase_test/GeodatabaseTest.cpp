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

#include "GeodatabaseTest.h"

#include <geodatabase/IFeature.h>
#include <geodatabase/ShapeFileFeatureWorkspace.h>
#include <geodatabase/IFeatureClass.h>
#include <geodatabase/ITable.h>
#include <geodatabase/IFields.h>
#include <geodatabase/IField.h>
#include <geodatabase/IRecord.h>
#include <geodatabase/ColumnClassificator.h>

#include <geometry/Point.h>
#include <geometry/Polygon.h>
#include <geometry/Polyline.h>
#include <geometry/Ring.h>
#include <geometry/Segment.h>

#include <QtCore/QByteArray>
#include <QtCore/QCoreApplication>
#include <QtGui/QPolygonF>
#include <QtTest/QTest>

GeodatabaseTest::GeodatabaseTest(QObject *parent)
    : QObject(parent)
    , m_workspace(QCoreApplication::applicationDirPath() + "/geodatabase_data")
    , m_pointShp("points")
    , m_lineShp("roads")
    , m_polygonShp("polygons")
{
}

GeodatabaseTest::~GeodatabaseTest()
{
}

void GeodatabaseTest::shouldLoadPointShapes()
{
    ShapeFileFeatureWorkspace workspace(m_workspace);
    IFeatureClassUPtr pointsClass(workspace.openFeatureClass(m_pointShp));
    QVERIFY(pointsClass->shapeType() == Geometry::Type::Point);
    QCOMPARE(pointsClass->featuresCount(), 54);
    QCOMPARE(pointsClass->extent().topLeft().x(), -0.7035498);
    QCOMPARE(pointsClass->extent().bottomRight().y(), 52.153908);

    const int FEATURE_ID = 47;
    const IFeature* feature = pointsClass->featureById(FEATURE_ID);
    const IFeature* feature1 = pointsClass->featureByIndex(FEATURE_ID);
    QCOMPARE(feature, feature1);
    QCOMPARE(feature->id(), FEATURE_ID);
    QCOMPARE(feature->record()->value(0).toString(), QString("1666355140"));

    const Point* point = static_cast<const Point*>(feature->geometry());
    QCOMPARE(point->x(), -0.7023426);
    QCOMPARE(point->y(), 52.1532809);
}

void GeodatabaseTest::shouldLoadLineShapes()
{
    ShapeFileFeatureWorkspace workspace(m_workspace);
    IFeatureClassUPtr polylinesClass(workspace.openFeatureClass(m_lineShp));
    QVERIFY(polylinesClass->shapeType() == Geometry::Type::Polyline);
    QCOMPARE(polylinesClass->featuresCount(), 41);
    QCOMPARE(polylinesClass->extent().topLeft().x(), -0.7035622);
    QCOMPARE(polylinesClass->extent().bottomRight().y(), 52.154232);

    const int FEATURE_ID = 7;
    const IFeature* feature = polylinesClass->featureById(FEATURE_ID);
    const IFeature* feature1 = polylinesClass->featureByIndex(FEATURE_ID);
    QCOMPARE(feature, feature1);
    QCOMPARE(feature->id(), FEATURE_ID);
    QCOMPARE(feature->record()->value("name").toString(), QString("Freemans Gardens"));

    const Polyline* line = static_cast<const Polyline*>(feature->geometry());
    QCOMPARE(line->paths().size(), 1);                 // paths
    //QCOMPARE(line->paths()[0]->segments().size(), 5);  // segments // TODO

    PointList &points = line->paths()[0]->points();
    QCOMPARE(points.size(), 6);

    const Point* point = points[3];
    QCOMPARE(point->x(), -0.7002893);
    QCOMPARE(point->y(), 52.1521591);
}

void GeodatabaseTest::shouldLoadPolygonShapes()
{
    ShapeFileFeatureWorkspace workspace(m_workspace);
    IFeatureClassUPtr polygonClass(workspace.openFeatureClass(m_polygonShp));
    QVERIFY(polygonClass->shapeType() == Geometry::Type::Polygon);
    QCOMPARE(polygonClass->featuresCount(), 149);
    QCOMPARE(polygonClass->extent().topLeft().x(), -0.7034284);
    QCOMPARE(polygonClass->extent().bottomRight().y(), 52.1553076);

    const int FEATURE_ID = 148;
    const IFeature* feature = polygonClass->featureById(FEATURE_ID);
    const IFeature* feature1 = polygonClass->featureByIndex(FEATURE_ID);
    QCOMPARE(feature, feature1);
    QCOMPARE(feature->id(), FEATURE_ID);
    QCOMPARE(feature->record()->value("name").toString(), QString("With ring"));

    const Polygon * poly = static_cast<const Polygon*>(feature->geometry());
    QCOMPARE(poly->rings().size(), 2);

    const Ring* outerRing = poly->rings()[0];
    const Ring* innerRing = poly->rings()[1];

    //    QCOMPARE(outerRing->segments().size(), 1);
    QCOMPARE(outerRing->points().size(), 5);

//    QCOMPARE(outerRing->segments().size(), 1);
    QCOMPARE(innerRing->points().size(), 5);


//    const Segment* segment = ring->segments()[0];
//    QCOMPARE(segment->curve().size(), 6);

    const Point* point = outerRing->points()[3];
    QCOMPARE(point->x(), -0.702548287583833);
    QCOMPARE(point->y(), 52.1548340837575);
}

void GeodatabaseTest::shouldProvideFieldsInfo()
{
    ShapeFileFeatureWorkspace workspace(m_workspace);
    IFeatureClassUPtr polygonClass(workspace.openFeatureClass(m_polygonShp));
    const ITable* table = polygonClass->table();
    QCOMPARE(table->fields()->fieldCount(), 3);

    QCOMPARE(table->fields()->field(0)->name(), QString("osm_id"));
    QCOMPARE(table->fields()->field(1)->name(), QString("name"));
    QCOMPARE(table->fields()->field(2)->name(), QString("type"));
}

void GeodatabaseTest::shouldClassifyColumnValues()
{
    ShapeFileFeatureWorkspace workspace(m_workspace);
    IFeatureClassUPtr polygonClass(workspace.openFeatureClass(m_polygonShp));
    const ITable* table = polygonClass->table();

    ColumnClassificator categorizer(*table);
    const QStringList actual = categorizer.classify("type");
    const QStringList expected{"", "museum", "pub", "restaurant"};
    QCOMPARE(actual.size(), expected.size());

    for (int i = 0; i < expected.size(); ++i)
    {
        QCOMPARE(expected[i], actual[i]);
    }
}


