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

#include "ShapeFileReaderTest.h"

#include <geodatabase/ShapeFileReader.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtTest/QTest>

//------------------------------------------------------------------------------
void verifyShapeHeaderNull(ShapeFileHeader &header);

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
ShapeFileReaderTest::ShapeFileReaderTest(QObject *parent)
    : QObject(parent)
    , m_pointsFileName("")
    , m_polylinesFileName("")
    , m_polygonesFileName("")
    , m_wrongFileCodeFileName("")
    , m_wrongFileVersionFileName("")
{
    QDir testDataDir(qApp->applicationDirPath());
    testDataDir.cd("../testData");

    m_pointsFileName = testDataDir.absoluteFilePath("points.shp");
    m_polylinesFileName = testDataDir.absoluteFilePath("polylines.shp");
    m_polygonesFileName = testDataDir.absoluteFilePath("polygones.shp");
    m_wrongFileCodeFileName = testDataDir.absoluteFilePath("wrong_file_code.shp");
    m_wrongFileVersionFileName = testDataDir.absoluteFilePath("wrong_file_version.shp");
}

//------------------------------------------------------------------------------
void ShapeFileReaderTest::shouldReadShapeFileHeader()
{
    QFile pointsFile(m_pointsFileName);
    pointsFile.open(QIODevice::ReadOnly);

    ShapeFileReader reader(&pointsFile);

    ShapeFileHeader header;
    bool result = reader.readHeader(header);

    QVERIFY(result);

    QCOMPARE(header.fileCode, 9994);
    QCOMPARE(header.unused1, 0);
    QCOMPARE(header.unused2, 0);
    QCOMPARE(header.unused3, 0);
    QCOMPARE(header.unused4, 0);
    QCOMPARE(header.unused5, 0);
    QCOMPARE(header.fileLength, 128);
    QCOMPARE(header.version, 1000);
    QCOMPARE(header.shapeType, (int)ShapeType::Point);
    QCOMPARE(header.bBox.left(),  13.087828);
    QCOMPARE(header.bBox.top(), 52.3375073);
    QCOMPARE(header.bBox.right(), 13.7561557);
    QCOMPARE(header.bBox.bottom(),   52.6366724);

    QCOMPARE(header.zmin, 0.0);
    QCOMPARE(header.zmax, 0.0);
    QCOMPARE(header.mmin, 0.0);
    QCOMPARE(header.mmax, 0.0);
}

//------------------------------------------------------------------------------
void ShapeFileReaderTest::shouldReturnFalseIfFileCodeIsWrong()
{
    QFile pointsFile(m_wrongFileCodeFileName);
    pointsFile.open(QIODevice::ReadOnly);

    ShapeFileReader reader(&pointsFile);

    ShapeFileHeader header;
    memset(reinterpret_cast<char *>(&header), 0, sizeof(header));
    bool result = reader.readHeader(header);

    QVERIFY(!result);

    verifyShapeHeaderNull(header);
}

//------------------------------------------------------------------------------
void ShapeFileReaderTest::shouldReturnFalseIfFileVersionIsWrong()
{
    QFile pointsFile(m_wrongFileVersionFileName);
    pointsFile.open(QIODevice::ReadOnly);

    ShapeFileReader reader(&pointsFile);

    ShapeFileHeader header;
    memset(reinterpret_cast<char *>(&header), 0, sizeof(header));
    bool result = reader.readHeader(header);

    QVERIFY(!result);

    verifyShapeHeaderNull(header);
}

//------------------------------------------------------------------------------
void ShapeFileReaderTest::shouldReadShapeRecord()
{
    QFile pointsFile(m_pointsFileName);
    pointsFile.open(QIODevice::ReadOnly);

    ShapeFileReader reader(&pointsFile);

    ShapeFileHeader header;
    reader.readHeader(header);

    Record point;
    reader.readShapeRecord(point);

    QCOMPARE(point.recordNumber, 1);
    QCOMPARE(point.contentLength, 20);
    int *shapeType = reinterpret_cast<int *>(&point.shapeBlob[0]);
    double *x = reinterpret_cast<double *>(&point.shapeBlob[4]);
    double *y = reinterpret_cast<double *>(&point.shapeBlob[12]);

    QCOMPARE(*shapeType, (int)ShapeType::Point);
    QCOMPARE(*x, 13.5233553);
    QCOMPARE(*y, 52.4837034);

    delete[] point.shapeBlob;
}

//------------------------------------------------------------------------------
void verifyShapeHeaderNull(ShapeFileHeader &header)
{
    QCOMPARE(header.fileCode, 0);
    QCOMPARE(header.unused1, 0);
    QCOMPARE(header.unused2, 0);
    QCOMPARE(header.unused3, 0);
    QCOMPARE(header.unused4, 0);
    QCOMPARE(header.unused5, 0);
    QCOMPARE(header.fileLength, 0);
    QCOMPARE(header.version, 0);
    QCOMPARE(header.shapeType, (int)ShapeType::NullShape);
    QCOMPARE(header.bBox.left(), 0.0);
    QCOMPARE(header.bBox.bottom(), 0.0);
    QCOMPARE(header.bBox.right(), 0.0);
    QCOMPARE(header.bBox.top(), 0.0);

    QCOMPARE(header.zmin, 0.0);
    QCOMPARE(header.zmax, 0.0);
    QCOMPARE(header.mmin, 0.0);
    QCOMPARE(header.mmax, 0.0);
}

//------------------------------------------------------------------------------
