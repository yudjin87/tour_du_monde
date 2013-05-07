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

#include "DependencySolver.h"
#include <utils/ListDictionary.h>

#include <algorithm>
#include <iterator>

//------------------------------------------------------------------------------
DependencySolver::DependencySolver()
    : m_dependencyMatrix(new ListDictionary<QString, QString>())
{
}

//------------------------------------------------------------------------------
DependencySolver::~DependencySolver()
{
    delete m_dependencyMatrix;
    m_dependencyMatrix = nullptr;
}

//------------------------------------------------------------------------------
void DependencySolver::addComponent(const QString &i_name)
{
    if (i_name.isEmpty()) {
        QString error = QString("The provided component name must not be null or empty.");
        qDebug(error.toLatin1());
        return;
    }

    addToDependencyMatrix(i_name);
    addToKnownComponents(i_name);
}

//------------------------------------------------------------------------------
void DependencySolver::addDependency(const QString &childComponent, const QString &parentComponent)
{
    if (childComponent.isEmpty()) {
        QString error = QString("The provided child component component name must not be null or empty.");
        qDebug(error.toLatin1());
        return;
    }

    if (parentComponent.isEmpty()) {
        QString error = QString("The provided parent component name must not be null or empty.");
        qDebug(error.toLatin1());
        return;
    }

    if (!m_knownComponents.contains(childComponent)) {
        QString error = QString("Cannot add dependency for unknown component \"%1\". Add it first.").arg(childComponent);
        qDebug(error.toLatin1());
        return;
    }

    addToDependencyMatrix(parentComponent);
    m_dependencyMatrix->add(parentComponent, childComponent);
}

//------------------------------------------------------------------------------
int DependencySolver::componentsCount() const
{
    return m_knownComponents.size();
}

//------------------------------------------------------------------------------
int Compare(const QString &a, const QString &b)
{
    return QString::compare(a, b);
}

//------------------------------------------------------------------------------
bool DependencySolver::solve(QStringList &ordered, QStringList &orphans, QStringList &missing) const
{
    QStringList orderedList;
    while (orderedList.size() < m_dependencyMatrix->size()) {
        QStringList leaves = findLeaves(orderedList);
        if ((leaves.size() == 0) && (orderedList.size() < m_dependencyMatrix->size()))
            return false; // Cyclic dependencies are found

        orderedList.append(leaves);
    }

    // Clean ordered list
    foreach (const QString &component, orderedList) {
        if (m_knownComponents.contains(component))
            continue;

        // Remove missing from sorted
        missing.append(component);
        orderedList.removeOne(component);

        // Remove orphans from sorted
        const QStringList &children = *m_dependencyMatrix->value(component);
        foreach (const QString &orphan, children) {
            orderedList.removeOne(orphan);
            orphans.append(orphan);
        }
    }

    std::reverse(orderedList.begin(), orderedList.end());
    ordered = orderedList;

    return true;
}

//------------------------------------------------------------------------------
void DependencySolver::addToDependencyMatrix(const QString &i_component)
{
    if (!m_dependencyMatrix->contains(i_component))
        m_dependencyMatrix->add(i_component);
}

//------------------------------------------------------------------------------
void DependencySolver::addToKnownComponents(const QString &i_component)
{
    if (!m_knownComponents.contains(i_component, Qt::CaseInsensitive))
        m_knownComponents.push_back(i_component);
}

//------------------------------------------------------------------------------
QStringList DependencySolver::findLeaves(const QStringList &i_skip) const
{
    QStringList result;

    foreach (const QString &parentComponent, m_dependencyMatrix->keys()) {
        if (i_skip.contains(parentComponent))
            continue;

        int count = 0;
        const QStringList &children = *m_dependencyMatrix->value(parentComponent);
        foreach (const QString &child, children) {
            if (i_skip.contains(child))
                continue;

            ++count;
        }
        if (count == 0)
            result.append(parentComponent);
    }

    return result;
}

//------------------------------------------------------------------------------
