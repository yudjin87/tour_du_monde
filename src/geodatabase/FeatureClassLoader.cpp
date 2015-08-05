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

#include "geodatabase/FeatureClassLoader.h"
#include "geodatabase/BinaryReader.h"
#include "geodatabase/GeometryFactory.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QDir>

#include <fstream>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("FeatureClassLoader");
}

namespace
{
static const char* SHAPE_FILE_EXT = "shp";
const int32_t SHAPE_FILE_CODE = 9994;
const int32_t SHAPE_FILE_VERSION = 1000;
}

FeatureClassLoader::FeatureClassLoader(const QString &dirPath)
    : IFeatureClassLoader()
    , m_dirPath(dirPath)
    , m_file()
    , m_reader()
    , m_shapeType(ShapeType::NullShape)
    , m_boundingBox()
{
}

FeatureClassLoader::~FeatureClassLoader()
{
}

IFeatureClassLoader::LoadResult FeatureClassLoader::open(const QString &name)
{
    const QDir dir(m_dirPath);
    if (!dir.exists())
    {
        Log.w(QString("Can't open \"%1\", because provided directory path \"%2\" doesn't exist").arg(name).arg(m_dirPath));
        return LoadResult::Fail;
    }

    const QString shapeFileName = dir.absoluteFilePath(name);
    m_file = QFileInfo(shapeFileName);
    if (m_file.suffix().isEmpty())
    {
        m_file = shapeFileName + "." + SHAPE_FILE_EXT;
    }

    std::unique_ptr<std::ifstream> stream(new std::ifstream());
    stream->open(m_file.absoluteFilePath().toStdString(), std::ios::in | std::ios::binary);
    if (stream->fail())
    {
        Log.w(QString("Can't open \"%1\"").arg(name).arg(m_file.absoluteFilePath()));
        return LoadResult::Fail;
    }

    stream->seekg(0, std::ifstream::end);
    const size_t fileSize = stream->tellg();

    stream->seekg(0, std::ifstream::beg);
    m_reader.reset(new BinaryReader(std::move(stream), fileSize));

    return readHeader(fileSize);
}

bool FeatureClassLoader::hasNext()
{
    if (m_reader == nullptr)
    {
        return false;
    }

    return !m_reader->endOfStream();
}

void FeatureClassLoader::goToFirst()
{
    // TODO
}

Geometry::Type FeatureClassLoader::geometryType() const
{
    return GeometryFactory::geometryTypeFromShapeType(m_shapeType);
}

QRectF FeatureClassLoader::boundingBox() const
{
    return m_boundingBox;
}

void FeatureClassLoader::loadFeature(IFeature *feature)
{
    // TODO: assert for EoF
    const int recordNumber = m_reader->readInt32(BinaryReader::BigEndian());
    feature->setId(recordNumber - 1); // in shape files, feature id start from 1

    const int contentLenght = m_reader->readInt32(BinaryReader::BigEndian()); Q_UNUSED(contentLenght)

    IGeometry* shape = GeometryFactory::createGeometry(*m_reader);
    feature->setGeometry(shape);
}

QFileInfo FeatureClassLoader::source() const
{
    return m_file;
}

IFeatureClassLoader::LoadResult FeatureClassLoader::readHeader(const int64_t fileSize)
{
    const int32_t fileCode = m_reader->readInt32(BinaryReader::BigEndian());
    if (fileCode != SHAPE_FILE_CODE)
    {
        Log.w(QString("Can't open \"%1\", because file code is invalid: %2").arg(m_file.absoluteFilePath()).arg(fileCode));
        return LoadResult::Fail;
    }

    const int32_t unused1 = m_reader->readInt32(BinaryReader::BigEndian()); Q_UNUSED(unused1)
    const int32_t unused2 = m_reader->readInt32(BinaryReader::BigEndian()); Q_UNUSED(unused2)
    const int32_t unused3 = m_reader->readInt32(BinaryReader::BigEndian()); Q_UNUSED(unused3)
    const int32_t unused4 = m_reader->readInt32(BinaryReader::BigEndian()); Q_UNUSED(unused4)
    const int32_t unused5 = m_reader->readInt32(BinaryReader::BigEndian()); Q_UNUSED(unused5)


    const int32_t fileLength = m_reader->readInt32(BinaryReader::BigEndian()) * 2;
    if (fileLength != fileSize)
    {
        Log.w(QString("Can't open \"%1\", because file length is invalid: %2, expected %3")
              .arg(m_file.absoluteFilePath().arg(fileLength).arg(fileSize)));
        return LoadResult::Fail;
    }

    const int32_t version = m_reader->readInt32(BinaryReader::LittleEndian());
    if (version != SHAPE_FILE_VERSION)
    {
        Log.w(QString("Can't open \"%1\", because file version is invalid: %2").arg(m_file.absoluteFilePath()).arg(version));
        return LoadResult::Fail;
    }

    m_shapeType = static_cast<ShapeType>(m_reader->readInt32(BinaryReader::LittleEndian()));
    if (!verifyEnum(m_shapeType))
    {
        Log.w(QString("Can't open \"%1\", because shape type is unsupported: %2")
              .arg(m_file.absoluteFilePath()).arg( static_cast<int>(m_shapeType)));
        return LoadResult::Fail;
    }

    GeometryFactory::readBoundingBox(*m_reader, &m_boundingBox);

    QRectF unusedBbox;
    GeometryFactory::readBoundingBox(*m_reader, &unusedBbox);

    return LoadResult::Success;
}

