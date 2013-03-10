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

#ifndef ISHAPEFILEREADER_H
#define ISHAPEFILEREADER_H

#include "geodatabase_api.h"

#include <QtCore/QVector>
#include <QtCore/QPointF>
#include <QtCore/QRectF>

class QIODevice;

struct ShapeFileHeader;
struct Record;

class GEODATABASE_API IShapeFileReader
{
public:
    IShapeFileReader(){}
    virtual ~IShapeFileReader(){}

    virtual QIODevice *inputDevice() const = 0;

    virtual bool readHeader(ShapeFileHeader &outHeader) = 0;

    virtual void readShapeRecord(Record &record) = 0;

    virtual void setInputDevice(QIODevice *inputDevice) = 0;

private:
    Q_DISABLE_COPY(IShapeFileReader)
};

struct ShapeFileHeader
{
    int         fileCode;       //	0
    int         unused1;		//	4
    int         unused2;		//	8
    int         unused3;		//	12
    int         unused4;		//	16
    int         unused5;		//	20
    int         fileLength;		//	24
    int         version;		//	28
    int         shapeType;		//	32
    QRectF      bBox;           //  36..60
    double      zmin;			//	68
    double      zmax;			//	76
    double      mmin;			//	84
    double      mmax;			//	92
};

struct Record
{
    int         recordNumber;
    int         contentLength;
    char*       shapeBlob;
};

#endif // ISHAPEFILEREADER_H
