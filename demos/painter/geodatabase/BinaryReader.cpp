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

#include "geodatabase/BinaryReader.h"
#include <algorithm>
#include <sstream>

BinaryReader::BinaryReader(std::istream &&binaryStream)
    : m_binaryStream(std::move(binaryStream))
    , m_bufferSize(0)
    , m_byteIter(0)
{
}

BinaryReader::BinaryReader(const char *buffer, const size_t size)
    : m_binaryStream(std::stringstream(std::string(buffer, size)))
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

bool BinaryReader::endOfBuffer() const
{
    return m_bufferSize <= m_byteIter;
}

int32_t BinaryReader::readInt32(const BinaryReader::BigEndian&)
{
    checkByteIterator();

    int value = 0;
//    value |= m_buffer[m_byteIter] << 24;
//    shiftByteIterator();

//    value |= m_buffer[m_byteIter] << 16;
//    shiftByteIterator();

//    value |= m_buffer[m_byteIter] << 8;
//    shiftByteIterator();

//    value |= m_buffer[m_byteIter] && 0xFF;
//    shiftByteIterator();

    return value;
}

int32_t BinaryReader::readInt32(const BinaryReader::LittleEndian &)
{
    checkByteIterator();

    int32_t value = 0;
    m_binaryStream.read(reinterpret_cast<char*>(&value), sizeof(value));

    shiftByteIterator();
    shiftByteIterator();
    shiftByteIterator();
    shiftByteIterator();

    return value;
}

double BinaryReader::readDouble()
{
    const size_t doubleLimit = m_byteIter + sizeof(double);
    Q_ASSERT(doubleLimit <= m_bufferSize);

    double value = 0.0;
    m_binaryStream.read(reinterpret_cast<char*>(&value), sizeof(value));
    //std::copy(m_buffer + m_byteIter, m_buffer + doubleLimit, reinterpret_cast<uint8_t*>(&value));

    m_byteIter += sizeof(double);

    return value;
}

void BinaryReader::readRawData(char *destination, const size_t size)
{
    Q_ASSERT((m_byteIter + size) <= m_bufferSize && "readRawData: size is too much");

    m_binaryStream.read(destination, size);
    m_byteIter += size;
}

void BinaryReader::readRawData(uint8_t *destination, const size_t size)
{
    readRawData(reinterpret_cast<char*>(destination), size);
}

void BinaryReader::shiftByteIterator()
{
    checkByteIterator();
    ++m_byteIter;
}

void BinaryReader::checkByteIterator()
{
    Q_ASSERT(m_byteIter <= m_bufferSize);
}

