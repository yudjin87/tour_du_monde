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

#include "componentsystem/ParentDefinitions.h"
#include "componentsystem/ParentDefinition.h"

#include <QtCore/QtAlgorithms>

//------------------------------------------------------------------------------
ParentDefinitions::ParentDefinitions(QObject *parent)
    : QObject(parent)
    , m_parents(QList<ParentDefinition *>())
{
}

//------------------------------------------------------------------------------
ParentDefinitions::~ParentDefinitions()
{
    qDeleteAll(m_parents);
    m_parents.clear();
}

//------------------------------------------------------------------------------
bool ParentDefinitions::contains(const QString &parentName) const
{
    for (ParentDefinition *com : m_parents) {
        if (com->name() == parentName)
            return true;
    }

    return false;
}

//------------------------------------------------------------------------------
void ParentDefinitions::append(ParentDefinition *parent)
{
    m_parents.append(parent);
}

//------------------------------------------------------------------------------
int ParentDefinitions::size() const
{
    return m_parents.size();
}

//------------------------------------------------------------------------------
const Version *ParentDefinitions::operator [](const QString &parentName) const
{
    for (ParentDefinition *com : m_parents) {
        if (com->name() == parentName)
            return com->version();
    }

    return nullptr;
}

//------------------------------------------------------------------------------
const ParentDefinition *ParentDefinitions::operator [](int index) const
{
    return m_parents[index];
}

//------------------------------------------------------------------------------
QList<ParentDefinition *>::const_iterator ParentDefinitions::begin() const
{
    return m_parents.begin();
}

//------------------------------------------------------------------------------
QList<ParentDefinition *>::const_iterator ParentDefinitions::constEnd() const
{
    return m_parents.constEnd();
}

//------------------------------------------------------------------------------
QList<ParentDefinition *>::const_iterator ParentDefinitions::end() const
{
    return m_parents.end();
}

//------------------------------------------------------------------------------
QList<ParentDefinition *>::const_iterator ParentDefinitions::constBegin() const
{
    return m_parents.constBegin();
}

//------------------------------------------------------------------------------
