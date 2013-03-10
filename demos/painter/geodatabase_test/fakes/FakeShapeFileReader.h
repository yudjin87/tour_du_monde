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

#ifndef FAKESHAPEFILEREADER_H
#define FAKESHAPEFILEREADER_H

#include <geodatabase/IShapeFileReader.h>

#include <QtCore/QObject>

class FakeShapeFileReader : public QObject, public IShapeFileReader
{
    Q_OBJECT
public:
    FakeShapeFileReader();
    ~FakeShapeFileReader();

    QIODevice *inputDevice() const;

    bool readHeader(ShapeFileHeader &outHeader);

    void readShapeRecord(Record &outRecHeader);

    void setInputDevice(QIODevice *inputDevice);

signals:
    void deviceIsSet(QString fileName, qint64 pos, bool isOpen);

public:
    ShapeFileHeader header;
    Record recHeader;
    QIODevice *device;
    int readRecords;
    int readRecordsLimit;
};

#endif // FAKESHAPEFILEREADER_H
