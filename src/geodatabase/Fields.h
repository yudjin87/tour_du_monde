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

#include <geodatabase/IField.h>
#include <geodatabase/IFieldsEdit.h>

#include <QtCore/QVector>
#include <QtSql/QSqlRecord>

class Fields : public IFieldsEdit
{
    Q_OBJECT
public:
    Fields(const QSqlRecord& record);
    ~Fields();

    int fieldCount() const override;

    const IField* field(const int index) const override;
    const IField* field(const QString& name) const override;

    ConstListenerVector::const_iterator begin() const override;
    ConstListenerVector::const_iterator end() const override;

    // IFieldsEdit:
    IField* field(const int index) override;
    IField* field(const QString& name) override;
    void addField(IField* field) override;

private:
    QVector<IField*> m_fields;
};
