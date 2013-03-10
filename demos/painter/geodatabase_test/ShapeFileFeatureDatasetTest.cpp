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

#include "ShapeFileFeatureDatasetTest.h"
#include "fakes/FakeWorkspace.h"
#include "fakes/FakeShapeFileFeatureDataset.h"
#include "fakes/FakeGeometryFactory.h"
#include "fakes/FakeShapeFileReader.h"
#include "fakes/FakeFeatureClass.h"

#include <geodatabase/IFeatureClass.h>
#include <geodatabase/ShapeFileFeatureDataset.h>
#include <utils/ServiceLocator.h>

#include <QtCore/QScopedPointer>
#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

#include <functional>

#define INSTANTIANTE_FAKES() shapeFileReader = new FakeShapeFileReader(); geometryFactory = new FakeGeometryFactory();

static FakeShapeFileReader* shapeFileReader;
static FakeGeometryFactory* geometryFactory;

typedef QScopedPointer<IFeatureClass> IFeatureClassPtr;

//------------------------------------------------------------------------------
void *getReaderInstance()
{
    return shapeFileReader;
}

//------------------------------------------------------------------------------
void *getFactoryInstance()
{
    return geometryFactory;
}

//------------------------------------------------------------------------------
ShapeFileFeatureDatasetTest::ShapeFileFeatureDatasetTest(QObject *parent)
    : QObject(parent)
    , m_testDataDir(qApp->applicationDirPath())
    , mp_locator(new ServiceLocator())
{

    m_testDataDir.cd("../testData");

    mp_locator->registerType<IShapeFileReader>(&getReaderInstance);
    mp_locator->registerType<IGeometryFactory>(&getFactoryInstance);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::classByName_shouldSetupFileWithCorrectFileNameToReader()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    QSignalSpy spy(shapeFileReader, SIGNAL(deviceIsSet(QString,qint64,bool)));
    ShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClassPtr fc(dataSet.classByName("points.shp"));

    QList<QVariant> signal = spy.takeFirst();
    QCOMPARE(signal.at(0).toString(), m_testDataDir.absoluteFilePath("points.shp"));
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::classByName_shouldReturnNullIfClassNameIsWrong()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    ShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClass *fc = dataSet.classByName("points.doc");

    QVERIFY(fc == nullptr);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::classByName_shouldReturnNullIfShapeFileDoesNotExist()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    ShapeFileFeatureDataset dataSet(workspace, "points123", *mp_locator);

    IFeatureClass *fc = dataSet.classByName();

    QVERIFY(fc == nullptr);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::classByName_shouldSetupFileWithCorrectFileNameToReaderIfExtensionIsAbsent()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    QSignalSpy spy(shapeFileReader, SIGNAL(deviceIsSet(QString,qint64,bool)));
    ShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClassPtr fc(dataSet.classByName("points"));

    QList<QVariant> signal = spy.takeFirst();
    QCOMPARE(signal.at(0).toString(), m_testDataDir.absoluteFilePath("points.shp"));
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::classByName_shouldSetupFileWithCorrectFileNameIfEmptyNameIsPassed()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    QSignalSpy spy(shapeFileReader, SIGNAL(deviceIsSet(QString,qint64,bool)));
    ShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClassPtr fc(dataSet.classByName());

    QList<QVariant> signal = spy.takeFirst();
    QCOMPARE(signal.at(0).toString(), m_testDataDir.absoluteFilePath("points.shp"));
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::classByName_shouldSetupFileWithZeroOffset()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    QSignalSpy spy(shapeFileReader, SIGNAL(deviceIsSet(QString,qint64,bool)));
    ShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClassPtr fc(dataSet.classByName());

    QList<QVariant> signal = spy.takeFirst();
    QVERIFY(signal.at(0).toInt() == 0);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::classById_shouldOnlyWorksWithZeroId()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    ShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClass *fc = dataSet.classById(-1);
    QVERIFY(fc == nullptr);

    fc = dataSet.classById(1);
    QVERIFY(fc == nullptr);

    fc = dataSet.classById(0);
    QVERIFY(fc != nullptr);

    delete fc;
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::shouldReturnCorrectExtentFromTheFile()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    shapeFileReader->header.bBox.setCoords(3.33, 5.11, 7.777777, 11.1111111);
    ShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    QRectF extent = dataSet.extent();

    QCOMPARE(extent, shapeFileReader->header.bBox);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::shouldReturnCorrectGeometryType()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    shapeFileReader->header.shapeType = 3;// Polyline;
    ShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    GeometryType type = dataSet.geometryType();

    QCOMPARE(type, GeometryPolyline);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::classByName_shoudSetupOpenedFileToReader()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    QSignalSpy spy(shapeFileReader, SIGNAL(deviceIsSet(QString,qint64,bool)));
    ShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClassPtr fc(dataSet.classByName());

    QList<QVariant> signal = spy.takeFirst();
    QCOMPARE(signal.at(0).toBool(), true);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::shouldCreateFeatureClassWithCorrectParameters()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    geometryFactory->type = GeometryPoint;
    shapeFileReader->header.bBox.setCoords(13.087828, 52.3375073, 13.7561557, 52.6366724);
    FakeShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClassPtr fc(dataSet.classByName());

    QCOMPARE(dataSet.passedShapeType, GeometryPoint);
    QCOMPARE(dataSet.passedExtent.left(), 13.087828);
    QCOMPARE(dataSet.passedExtent.top(), 52.3375073);
    QCOMPARE(dataSet.passedExtent.right(), 13.7561557);
    QCOMPARE(dataSet.passedExtent.bottom(), 52.6366724);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::shouldCallReadShapeRecordUntilEndOfFile()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    geometryFactory->type = GeometryPoint;
    shapeFileReader->readRecordsLimit = 10;
    FakeShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClassPtr fc(dataSet.classByName());

    QCOMPARE(shapeFileReader->readRecords, 10);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::shouldCallCreateGeometryFromBlobForEachRecord()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    geometryFactory->type = GeometryPoint;
    shapeFileReader->readRecordsLimit = 10;
    FakeShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClassPtr fc(dataSet.classByName());

    QCOMPARE(geometryFactory->createdGeometries, 10);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::shouldCallCreateFeatureForEachRecord()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    geometryFactory->type = GeometryPoint;
    shapeFileReader->readRecordsLimit = 10;
    FakeShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClassPtr fc(dataSet.classByName());

    QCOMPARE(dataSet.featureClass->createdFeatures, 10);
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDatasetTest::shouldSetupGeometryToEveryCreatedFeature()
{
    FakeWorkspace workspace(m_testDataDir.absolutePath());
    INSTANTIANTE_FAKES() // we should not delete them, because ShapeFileFeatureDataset does it
    geometryFactory->type = GeometryPoint;
    shapeFileReader->readRecordsLimit = 10;
    FakeShapeFileFeatureDataset dataSet(workspace, "points", *mp_locator);

    IFeatureClassPtr fc(dataSet.classByName());

    foreach(FakeFeature *feature, dataSet.featureClass->features)
        QVERIFY(feature->geometryWasSet);
}

//------------------------------------------------------------------------------
