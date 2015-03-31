/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include "GeodatabaseTest.h"

#include <geodatabase/IFeature.h>
#include <geodatabase/ShapeFileFeatureWorkspace.h>
#include <geodatabase/IFeatureClass.h>

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
    , m_polygonShp("buildings")
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

    const int FEATURE_ID = 48;
    const IFeature* feature = pointsClass->featureById(FEATURE_ID);
    const IFeature* feature1 = pointsClass->featureByIndex(FEATURE_ID - 1);
    QCOMPARE(feature, feature1);
    QCOMPARE(feature->id(), FEATURE_ID);
    //QCOMPARE(feature->record()->at(0), "1666355140");

    const Point* point = static_cast<const Point*>(feature->geometry());
    QCOMPARE(point->point().x(), -0.7023426);
    QCOMPARE(point->point().y(), 52.1532809);
}

void GeodatabaseTest::shouldLoadLineShapes()
{
    ShapeFileFeatureWorkspace workspace(m_workspace);
    IFeatureClassUPtr pointsClass(workspace.openFeatureClass(m_lineShp));
    QVERIFY(pointsClass->shapeType() == Geometry::Type::Polyline);
    QCOMPARE(pointsClass->featuresCount(), 41);
    QCOMPARE(pointsClass->extent().topLeft().x(), -0.7035622);
    QCOMPARE(pointsClass->extent().bottomRight().y(), 52.154232);

    const int FEATURE_ID = 8;
    const IFeature* feature = pointsClass->featureById(FEATURE_ID);
    const IFeature* feature1 = pointsClass->featureByIndex(FEATURE_ID - 1);
    QCOMPARE(feature, feature1);
    QCOMPARE(feature->id(), FEATURE_ID);
    //QCOMPARE(feature->record()->at("name"), "Freemans Gardens");

    const Polyline* line = static_cast<const Polyline*>(feature->geometry());
    QCOMPARE(line->rings().size(), 1);

    const Ring* ring = line->rings()[0];
    QCOMPARE(ring->segments().size(), 1);

    const Segment* segment = ring->segments()[0];
    QCOMPARE(segment->curve().size(), 6);

    const QPointF point = segment->curve()[3];
    QCOMPARE(point.x(), -0.7002893);
    QCOMPARE(point.y(), 52.1521591);
}

void GeodatabaseTest::shouldLoadPolygonShapes()
{
    ShapeFileFeatureWorkspace workspace(m_workspace);
    IFeatureClassUPtr pointsClass(workspace.openFeatureClass(m_polygonShp));
    QVERIFY(pointsClass->shapeType() == Geometry::Type::Polygon);
    QCOMPARE(pointsClass->featuresCount(), 149);
    QCOMPARE(pointsClass->extent().topLeft().x(), -0.7034284);
    QCOMPARE(pointsClass->extent().bottomRight().y(), 52.1553076);

    const int FEATURE_ID = 149;
    const IFeature* feature = pointsClass->featureById(FEATURE_ID);
    const IFeature* feature1 = pointsClass->featureByIndex(FEATURE_ID - 1);
    QCOMPARE(feature, feature1);
    QCOMPARE(feature->id(), FEATURE_ID);
    //QCOMPARE(feature->record()->at("name"), "With rings");

    const Polygon * line = static_cast<const Polygon*>(feature->geometry());
    QCOMPARE(line->rings().size(), 2);

//    const Ring* ring = line->rings()[0];
//    QCOMPARE(ring->segments().size(), 1);

//    const Segment* segment = ring->segments()[0];
//    QCOMPARE(segment->curve().size(), 6);

//    const QPointF point = segment->curve()[3];
//    QCOMPARE(point.x(), -0.7002893);
//    QCOMPARE(point.y(), 52.1521591);
}

