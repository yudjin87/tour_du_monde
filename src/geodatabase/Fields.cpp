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

#include "geodatabase/Fields.h"
#include "geodatabase/Field.h"

#include <algorithm>

Fields::Fields(const QSqlRecord& record)
    : IFieldsEdit()
    , m_fields(record.count())
{
    for (int i = 0; i < record.count(); ++i)
    {
        m_fields[i] = new Field(record.field(i));
    }
}

Fields::~Fields()
{
    for (IField* f : m_fields)
    {
        delete f;
    }

    m_fields.clear();
}

int Fields::fieldCount() const
{
    return m_fields.size();
}

IField *Fields::field(const int index)
{
    return const_cast<IField*>(const_cast<const Fields*>(this)->field(index));
}

const IField *Fields::field(const int index) const
{
    if (index < m_fields.size())
    {
        return m_fields[index];
    }

    return nullptr;
}


IField *Fields::field(const QString &name)
{
    return const_cast<IField*>(const_cast<const Fields*>(this)->field(name));
}

const IField *Fields::field(const QString &name) const
{
    const auto byName = [name](const IField *f){return f->name().toLower() == name.toLower();};
    const auto it = std::find_if(std::begin(m_fields), std::end(m_fields), byName);
    if (it == std::end(m_fields))
    {
        return nullptr;
    }

    const IField * field = *it;
    return field;
}

IFields::ConstListenerVector::const_iterator Fields::begin() const
{
    return m_fields.begin();
}

IFields::ConstListenerVector::const_iterator Fields::end() const
{
    return m_fields.end();
}

void Fields::addField(IField *field)
{
    m_fields.push_back(field);
}
