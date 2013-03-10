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

#include "ShapeFileReader.h"

#include <QtCore/QIODevice>

//------------------------------------------------------------------------------
static void swapEndian(int &data)
{
    int temp;

    reinterpret_cast<char *>(&temp)[0] = reinterpret_cast<char *>(&data)[3];
    reinterpret_cast<char *>(&temp)[1] = reinterpret_cast<char *>(&data)[2];
    reinterpret_cast<char *>(&temp)[2] = reinterpret_cast<char *>(&data)[1];
    reinterpret_cast<char *>(&temp)[3] = reinterpret_cast<char *>(&data)[0];

    data = temp;
}

//------------------------------------------------------------------------------
const int ShapeFileReader::fileCode = 9994;
const int ShapeFileReader::fileVersion = 1000;

//------------------------------------------------------------------------------
ShapeFileReader::ShapeFileReader(QIODevice *inputDevice)
    : QObject()
    , mp_inputDevice(inputDevice)
{
    setObjectName("ShapeFileReader");
}

//------------------------------------------------------------------------------
ShapeFileReader::~ShapeFileReader()
{
    mp_inputDevice = nullptr;
}

//------------------------------------------------------------------------------
QIODevice *ShapeFileReader::inputDevice() const
{
    return mp_inputDevice;
}

//------------------------------------------------------------------------------
void ShapeFileReader::setInputDevice(QIODevice *inputDevice)
{
    mp_inputDevice = inputDevice;
}

//------------------------------------------------------------------------------
bool ShapeFileReader::readHeader(ShapeFileHeader &outHeader)
{
    if (mp_inputDevice == nullptr)
        return false;

    ShapeFileHeader tempHeader;
    readFileCode(tempHeader.fileCode);
    if (tempHeader.fileCode != ShapeFileReader::fileCode)
        return false;

    // read 5 integers (unused bytes)
    readUnusedInts(tempHeader.unused1, 5);

    readFileLength(tempHeader.fileLength);

    mp_inputDevice->read(reinterpret_cast<char *>(&tempHeader.version), sizeof(tempHeader.version));
    if (tempHeader.version != ShapeFileReader::fileVersion)
        return false;

    readShapeType(tempHeader.shapeType);

    readBoundingBox(tempHeader.bBox);

    // read one more 4 doubles
    mp_inputDevice->read(reinterpret_cast<char *>(&tempHeader.zmin), sizeof(tempHeader.zmin));
    mp_inputDevice->read(reinterpret_cast<char *>(&tempHeader.zmax), sizeof(tempHeader.zmax));
    mp_inputDevice->read(reinterpret_cast<char *>(&tempHeader.mmin), sizeof(tempHeader.mmin));
    mp_inputDevice->read(reinterpret_cast<char *>(&tempHeader.mmax), sizeof(tempHeader.mmax));

    outHeader = tempHeader;
    return true;
}

//------------------------------------------------------------------------------
void ShapeFileReader::readShapeRecord(Record &record)
{
    // read record number (big indian)
    mp_inputDevice->read(reinterpret_cast<char *>(&record.recordNumber), sizeof(record.recordNumber));
    swapEndian(record.recordNumber);

    // read record lenght (big indian). Length is presented in 16-bit words
    mp_inputDevice->read(reinterpret_cast<char *>(&record.contentLength), sizeof(record.contentLength));
    swapEndian(record.contentLength);
    record.contentLength *= 2;
    record.shapeBlob = new char[record.contentLength];

    mp_inputDevice->read(record.shapeBlob, record.contentLength);
}

//------------------------------------------------------------------------------
void ShapeFileReader::readFileCode(int &fileCode)
{
    mp_inputDevice->read(reinterpret_cast<char *>(&fileCode), sizeof(fileCode));
    swapEndian(fileCode);
}

//------------------------------------------------------------------------------
void ShapeFileReader::readUnusedInts(int &start, int size)
{
    mp_inputDevice->read(reinterpret_cast<char *>(&start), sizeof(start) * size);
}

//------------------------------------------------------------------------------
void ShapeFileReader::readFileLength(int &fileLength)
{
    // read file lenght (big indian). Length is presented in 16-bit words
    mp_inputDevice->read(reinterpret_cast<char *>(&fileLength), sizeof(fileLength));
    swapEndian(fileLength);
    fileLength *= 2;
}

//------------------------------------------------------------------------------
void ShapeFileReader::readBoundingBox(QRectF &bBox)
{
    double xmin;
    double ymin;
    double xmax;
    double ymax;
    mp_inputDevice->read(reinterpret_cast<char *>(&xmin), sizeof(double));
    mp_inputDevice->read(reinterpret_cast<char *>(&ymin), sizeof(double));
    mp_inputDevice->read(reinterpret_cast<char *>(&xmax), sizeof(double));
    mp_inputDevice->read(reinterpret_cast<char *>(&ymax), sizeof(double));

    bBox.setCoords(xmin, ymin, xmax, ymax);
}

//------------------------------------------------------------------------------
void ShapeFileReader::readShapeType(int &shapeType)
{
    mp_inputDevice->read(reinterpret_cast<char *>(&shapeType), sizeof(int));
}

//------------------------------------------------------------------------------
