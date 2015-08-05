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

#include "geodatabase/geodatabase_api.h"

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <memory>

class IFields;

class GEODATABASE_API IRecord : public QObject
{
    Q_OBJECT
public:
    // Read-only for now
    IRecord(){}

    virtual int index() const = 0;

    virtual QVariant value(int index) const = 0;
    virtual QVariant value(const QString& name) const = 0;

    //virtual IFields* fields() = 0;
    virtual const IFields* fields() const = 0;

    // void setValue(int i, const QVariant& val);
    // void setValue(const QString& name, const QVariant& val);

    // void setNull(int i);
    // void setNull(const QString& name);
//    virtual bool isNull(int i) const = 0;
//    virtual bool isNull(const QString& name) const = 0;

//    virtual int indexOf(const QString &name) const = 0;
//    virtual QString fieldName(int i) const = 0;

    // QSqlField field(int i) const;
    // QSqlField field(const QString &name) const;

//    virtual bool isGenerated(int i) const = 0;
//    virtual bool isGenerated(const QString& name) const = 0;
    // void setGenerated(const QString& name, bool generated);
    // void setGenerated(int i, bool generated);

    // void append(const QSqlField& field);
    // void replace(int pos, const QSqlField& field);
    // void insert(int pos, const QSqlField& field);
    // void remove(int pos);

    //virtual bool isEmpty() const = 0;
    //virtual bool contains(const QString& name) const = 0;
    // void clear();
    // void clearValues();
    //virtual int count() const = 0;
    // QSqlRecord keyValues(const QSqlRecord &keyFields) const;

private:
    Q_DISABLE_COPY(IRecord)
};

typedef std::unique_ptr<IRecord> IRecordUPtr;
