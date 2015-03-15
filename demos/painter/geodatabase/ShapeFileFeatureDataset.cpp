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

#include "ShapeFileFeatureDataset.h"
#include "IFeature.h"
#include "IShapeFileReader.h"
#include "IWorkspace.h"
#include "FeatureClass.h"
#include "ShapeFileReader.h"

#include <geometry/AbstractGeometry.h>
#include <geometry/GeometryFactory.h>

#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

#include <chrono>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("FeatureDataset");
}

const QString ShapeFileFeatureDataset::m_shapeFileExt = ".shp";

ShapeFileFeatureDataset::ShapeFileFeatureDataset(IWorkspace &workspace, const QString &name)
    : m_workspace(workspace)
    , m_fileReader(new ShapeFileReader())
    , m_factory(new GeometryFactory())
    , m_name(name)
    , m_file(nullptr)
    , m_isOpen(false)
{
}

ShapeFileFeatureDataset::~ShapeFileFeatureDataset()
{
    delete m_file;
    m_file = nullptr;
}

QString ShapeFileFeatureDataset::name() const
{
    return m_name;
}

IWorkspace *ShapeFileFeatureDataset::workspace() const
{
    return &m_workspace;
}

QRectF ShapeFileFeatureDataset::extent()
{
    if (!prepareToReading(name()))
        return QRectF();

    ShapeFileHeader header;
    m_fileReader->readHeader(header);

    finishReading();

    return header.bBox;
}

IFeatureClass *ShapeFileFeatureDataset::classById(int id)
{
    // Standalone file dataset could work only with single feature class;
    if (id != 0)
        return nullptr;

    return classByName();
}

IFeatureClass *ShapeFileFeatureDataset::classByName(const QString &className)
{
    QString clName = className.isEmpty() ? name() : className;
    if (clName !=  name() && clName != name() + ".shp")
        return nullptr;

    if (!prepareToReading(clName))
        return nullptr;

    typedef std::chrono::system_clock Clock;
    typedef std::chrono::milliseconds milliseconds;

    const Clock::time_point started = Clock::now();

    ShapeFileHeader header;
    m_fileReader->readHeader(header);

    Geometry::Type type = m_factory->geometryTypeFromShapeType(header.shapeType);
    IFeatureClass *featureClass = createFeatureClass(type, header.bBox, absoluteFilePath(className));

    while (!m_file->atEnd()) {
        Record record;
        memset(reinterpret_cast<char *>(&record), 0, sizeof(Record));
        m_fileReader->readShapeRecord(record);

        AbstractGeometry *geometry = m_factory->createGeometry(record.contentLength, record.shapeBlob);
        geometry->setId(record.recordNumber);
        IFeature *feature = featureClass->createFeature();
        feature->setGeometry(geometry);

        delete[] record.shapeBlob;
    }


    finishReading();

    Clock::time_point finished = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(finished - started);

    Log.d(QString("Reading %1 file: %2 ms").arg(className).arg(ms.count()));

    return featureClass;
}

QList<IFeatureClass *> ShapeFileFeatureDataset::classes()
{
    QList<IFeatureClass *> features;
    features.push_back(classByName(name()));
    return features;
}

Geometry::Type ShapeFileFeatureDataset::geometryType()
{
    Geometry::Type type = Geometry::Type::Null;
    if (!prepareToReading(name()))
        return type;

    ShapeFileHeader header;
    m_fileReader->readHeader(header);

    finishReading();

    return m_factory->geometryTypeFromShapeType(header.shapeType);
}

IFeatureClass *ShapeFileFeatureDataset::createFeatureClass(Geometry::Type geometryType, const QRectF &extent, const QString &source)
{
    return new FeatureClass(geometryType, extent, source);
}

bool ShapeFileFeatureDataset::prepareToReading(const QString &name)
{
    if (m_isOpen)
        return true;

    QString shapeFileName = absoluteFilePath(name);
    QFileInfo fileInfo(shapeFileName);
    if (!fileInfo.exists())
        return false;

    if (!fileInfo.isReadable())
        return false;

    m_file = new QFile(fileInfo.absoluteFilePath());
    m_file->open(QIODevice::ReadOnly);
    m_fileReader->setInputDevice(m_file);

    m_isOpen = true;

    return true;
}

void ShapeFileFeatureDataset::finishReading()
{
    if (!m_isOpen)
        return;

    m_isOpen = false;

    delete m_file;
    m_file = nullptr;
}

QString ShapeFileFeatureDataset::absoluteFilePath(const QString &name)
{
    QDir dir(m_workspace.pathName());

    QString shapeFileName = dir.absoluteFilePath(name);
    QFileInfo fileInfo(shapeFileName);
    if (fileInfo.suffix() == "")
        fileInfo = shapeFileName + ShapeFileFeatureDataset::m_shapeFileExt;

    return fileInfo.absoluteFilePath();
}

