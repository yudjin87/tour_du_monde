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

#pragma once
#include <geodatabase/geodatabase_api.h>

#include <cstdint>
#include <istream>
#include <memory>

class GEODATABASE_API BinaryReader
{
public:
    struct BigEndian {};
    struct LittleEndian {};

public:
    BinaryReader(std::unique_ptr<std::istream> binaryStream, const size_t bufferSize);
    BinaryReader(const char* buffer, const size_t size);
    BinaryReader(const uint8_t* buffer, const size_t size);
    ~BinaryReader();

    bool endOfStream();

    int32_t readInt32(const BigEndian &);
    int32_t readInt32(const LittleEndian&);

    double readDouble();

    void readRawData(char* destination, const size_t size);
    void readRawData(uint8_t* destination, const size_t size);

private:
    BinaryReader(const BinaryReader&) = delete;
    BinaryReader& operator=(const BinaryReader&) = delete;

    void shiftByteIterator(const size_t offset);
    void checkByteIterator();

private:
    std::unique_ptr<std::istream> m_binaryStream;
    const uint8_t* m_buffer; // doesn't take the ownership
    const size_t m_bufferSize;

    size_t m_byteIter;
};
