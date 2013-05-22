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

#include <geometry/AbstractGeometry.h>
#include <geometry/IGeometryFactory.h>

#include <utils/IServiceLocator.h>

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QScopedPointer>

typedef QScopedPointer<IShapeFileReader> ReaderPtr;
typedef QScopedPointer<IGeometryFactory> GeometryFactoryPtr;
//------------------------------------------------------------------------------
const QString ShapeFileFeatureDataset::m_shapeFileExt = ".shp";

//------------------------------------------------------------------------------
ShapeFileFeatureDataset::ShapeFileFeatureDataset(IWorkspace &workspace, const QString &name, IServiceLocator *locator)
    : m_workspace(workspace)
    , m_name(name)
    , m_locator(locator)
    , mp_file(nullptr)
    , m_isOpen(false)
{
}

//------------------------------------------------------------------------------
ShapeFileFeatureDataset::~ShapeFileFeatureDataset()
{
    delete mp_file;
    mp_file = nullptr;
}

//------------------------------------------------------------------------------
QString ShapeFileFeatureDataset::name() const
{
    return m_name;
}

//------------------------------------------------------------------------------
IWorkspace &ShapeFileFeatureDataset::workspace() const
{
    return m_workspace;
}

//------------------------------------------------------------------------------
QRectF ShapeFileFeatureDataset::extent()
{
    QRectF rect;
    if (!prepareToReading(name()))
        return rect;

    ReaderPtr reader(m_locator->buildInstance<IShapeFileReader>());
    reader->setInputDevice(mp_file);

    ShapeFileHeader header;
    reader->readHeader(header);

    finishReading();

    return header.bBox;
}

//------------------------------------------------------------------------------
IFeatureClass *ShapeFileFeatureDataset::classById(int id)
{
    // Standalone file dataset could work only with single feature class;
    if (id != 0)
        return nullptr;

    return classByName();
}

//------------------------------------------------------------------------------
IFeatureClass *ShapeFileFeatureDataset::classByName(const QString &className)
{
    QString clName = className.isEmpty() ? name() : className;
    if (clName !=  name() && clName != name() + ".shp")
        return nullptr;

    if (!prepareToReading(clName))
        return nullptr;

    ReaderPtr reader(m_locator->buildInstance<IShapeFileReader>());
    reader->setInputDevice(mp_file);

    ShapeFileHeader header;
    reader->readHeader(header);

    GeometryFactoryPtr geometryFactory(m_locator->buildInstance<IGeometryFactory>());
    GeometryType type = geometryFactory->geometryTypeFromShapeType(header.shapeType);
    IFeatureClass *featureClass = createFeatureClass(type, header.bBox);

    while (!mp_file->atEnd()) {
        Record record;
        memset(reinterpret_cast<char *>(&record), 0, sizeof(Record));
        reader->readShapeRecord(record);

        AbstractGeometry *geometry = geometryFactory->createGeometry(record.contentLength, record.shapeBlob);
        IFeature &feature = featureClass->createFeature();
        feature.setGeometry(geometry);

        delete[] record.shapeBlob;
    }


    finishReading();

    return featureClass;
}

//------------------------------------------------------------------------------
QList<IFeatureClass *> ShapeFileFeatureDataset::classes()
{
    QList<IFeatureClass *> features;
    features.push_back(classByName(name()));
    return features;
}

//------------------------------------------------------------------------------
GeometryType ShapeFileFeatureDataset::geometryType()
{
    GeometryType type = GeometryNull;
    if (!prepareToReading(name()))
        return type;

    ReaderPtr reader(m_locator->buildInstance<IShapeFileReader>());
    reader->setInputDevice(mp_file);

    ShapeFileHeader header;
    reader->readHeader(header);

    finishReading();

    GeometryFactoryPtr geometryFactory(m_locator->buildInstance<IGeometryFactory>());

    return geometryFactory->geometryTypeFromShapeType(header.shapeType);
}

//------------------------------------------------------------------------------
IFeatureClass *ShapeFileFeatureDataset::createFeatureClass(GeometryType geometryType, const QRectF &extent)
{
    return new FeatureClass(geometryType, extent);
}

//------------------------------------------------------------------------------
bool ShapeFileFeatureDataset::prepareToReading(const QString &name)
{
    if (m_isOpen)
        return true;

    QDir dir(m_workspace.pathName());

    QString shapeFileName = dir.absoluteFilePath(name);
    QFileInfo fileInfo(shapeFileName);
    if (fileInfo.suffix() == "")
        fileInfo = shapeFileName + ShapeFileFeatureDataset::m_shapeFileExt;

    if (!fileInfo.exists())
        return false;

    if (!fileInfo.isReadable())
        return false;

    mp_file = new QFile(fileInfo.absoluteFilePath());
    mp_file->open(QIODevice::ReadOnly);

    m_isOpen = true;

    return true;
}

//------------------------------------------------------------------------------
void ShapeFileFeatureDataset::finishReading()
{
    if (!m_isOpen)
        return;

    m_isOpen = false;

    delete mp_file;
    mp_file = nullptr;
}

//------------------------------------------------------------------------------
