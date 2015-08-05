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

#include "geodatabase/BinaryReader.h"
#include <algorithm>
#include <sstream>

namespace
{

int32_t swapEndian(const int32_t data)
{
    int temp = 0;

    reinterpret_cast<char *>(&temp)[0] = reinterpret_cast<const char *>(&data)[3];
    reinterpret_cast<char *>(&temp)[1] = reinterpret_cast<const char *>(&data)[2];
    reinterpret_cast<char *>(&temp)[2] = reinterpret_cast<const char *>(&data)[1];
    reinterpret_cast<char *>(&temp)[3] = reinterpret_cast<const char *>(&data)[0];

    return temp;
}

}

BinaryReader::BinaryReader(std::unique_ptr<std::istream> binaryStream, const size_t bufferSize)
    : m_binaryStream(std::move(binaryStream))
    , m_bufferSize(bufferSize)
    , m_byteIter(0)
{
}

BinaryReader::BinaryReader(const char *buffer, const size_t size)
    : m_binaryStream(new std::stringstream(std::string(buffer, size)))
    , m_bufferSize(size)
    , m_byteIter(0)
{
}

BinaryReader::BinaryReader(const uint8_t *buffer, const size_t size)
    : BinaryReader(reinterpret_cast<const char*>(buffer), size)
{
}

BinaryReader::~BinaryReader()
{
}

bool BinaryReader::endOfStream()
{
    const size_t currPos = m_binaryStream->tellg(); // eof doesn't work for stringstream
    return currPos == m_bufferSize;
}

int32_t BinaryReader::readInt32(const BinaryReader::BigEndian&)
{
    const int32_t value = readInt32(BinaryReader::LittleEndian());
    const int32_t swapped = swapEndian(value);

    return swapped;
}

int32_t BinaryReader::readInt32(const BinaryReader::LittleEndian &)
{
    checkByteIterator();

    int32_t value = 1;
    m_binaryStream->read(reinterpret_cast<char*>(&value), sizeof(value));

    shiftByteIterator(sizeof(value));

    return value;
}

double BinaryReader::readDouble()
{
    const size_t doubleLimit = m_byteIter + sizeof(double);
    Q_ASSERT(doubleLimit <= m_bufferSize);

    double value = 0.0;
    m_binaryStream->read(reinterpret_cast<char*>(&value), sizeof(value));

    shiftByteIterator(sizeof(value));

    return value;
}

void BinaryReader::readRawData(char *destination, const size_t size)
{
    Q_ASSERT((m_byteIter + size) <= m_bufferSize && "readRawData: size is too much");

    m_binaryStream->read(destination, size);
    m_byteIter += size;
}

void BinaryReader::readRawData(uint8_t *destination, const size_t size)
{
    readRawData(reinterpret_cast<char*>(destination), size);
}

void BinaryReader::shiftByteIterator(const size_t offset)
{
    checkByteIterator();
    m_byteIter += offset;
}

void BinaryReader::checkByteIterator()
{
    Q_ASSERT(m_byteIter <= m_bufferSize);
}

