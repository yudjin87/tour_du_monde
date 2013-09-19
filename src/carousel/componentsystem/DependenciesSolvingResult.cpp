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

#include "DependenciesSolvingResult.h"
#include "IComponent.h"

#include <algorithm>
#include <functional>

//------------------------------------------------------------------------------
DependenciesSolvingResult::DependenciesSolvingResult(const QList<IComponent *> &ordered)
    : m_orderedNames(QStringList())
    , m_orphansNames(QStringList())
    , m_missingNames(QStringList())
    , m_components(QList<IComponent *>())
    , m_orphans(QList<IComponent *>())
    , m_ordered(ordered)
    , m_hasCyclic(false)
{
}

//------------------------------------------------------------------------------
DependenciesSolvingResult::DependenciesSolvingResult(QStringList &ordered, QStringList &orphans, QStringList &missing, const QList<IComponent *> &components, bool hasCyclic /*= false*/)
    : m_orderedNames(ordered)
    , m_orphansNames(orphans)
    , m_missingNames(missing)
    , m_components(components)
    , m_orphans(QList<IComponent *>())
    , m_ordered(QList<IComponent *>())
    , m_hasCyclic(hasCyclic)
{
}

//------------------------------------------------------------------------------
DependenciesSolvingResult::DependenciesSolvingResult(const DependenciesSolvingResult &other)
    : m_orderedNames(other.m_orderedNames)
    , m_orphansNames(other.m_orphansNames)
    , m_missingNames(other.m_missingNames)
    , m_components(other.m_components)
    , m_orphans(other.m_orphans)
    , m_ordered(other.m_ordered)
    , m_hasCyclic(other.m_hasCyclic)
{
}

//------------------------------------------------------------------------------
const DependenciesSolvingResult &DependenciesSolvingResult::operator =(const DependenciesSolvingResult &other)
{
    if (this == &other)
        return *this;

    m_orderedNames = other.m_orderedNames;
    m_orphansNames = other.m_orphansNames;
    m_missingNames = other.m_missingNames;
    m_components   = other.m_components;
    m_orphans      = other.m_orphans;
    m_ordered      = other.m_ordered;
    m_hasCyclic    = other.m_hasCyclic;

    return *this;
}

//------------------------------------------------------------------------------
DependenciesSolvingResult::~DependenciesSolvingResult()
{
}

//------------------------------------------------------------------------------
bool DependenciesSolvingResult::hasCyclicDependencies() const
{
    return m_hasCyclic;
}

//------------------------------------------------------------------------------
QStringList DependenciesSolvingResult::missing() const
{
    return m_missingNames;
}

//------------------------------------------------------------------------------
QList<IComponent *> DependenciesSolvingResult::orphans() const
{
    if (!m_orphans.isEmpty())
        return m_orphans;

    collectComponents(m_orphansNames, m_orphans);

    return m_orphans;
}

//------------------------------------------------------------------------------
QList<IComponent *> DependenciesSolvingResult::ordered() const
{
    if (!m_ordered.isEmpty())
        return m_ordered;

    collectComponents(m_orderedNames, m_ordered);

    return m_ordered;
}

//------------------------------------------------------------------------------
bool DependenciesSolvingResult::precidate(IComponent *component, const QString &name)
{
    return component->name() == name;
}

//------------------------------------------------------------------------------
void DependenciesSolvingResult::collectComponents(const QStringList &names, QList<IComponent *> &result) const
{
    for (const QString &name : names) {
        std::function<bool(IComponent *)> pred = std::bind(&DependenciesSolvingResult::precidate, std::placeholders::_1, name);
        auto component = std::find_if(m_components.begin(), m_components.end(), pred);
        if (component != m_components.end())
            result.push_back(*component);
    }
}

//------------------------------------------------------------------------------
