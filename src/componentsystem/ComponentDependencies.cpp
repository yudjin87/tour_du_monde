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

#include "ComponentDependencies.h"
#include "DependencySolver.h"
#include "IComponent.h"
#include "ComponentDefinition.h"

//------------------------------------------------------------------------------
ComponentDependencies::ComponentDependencies(QObject *parent)
    : QObject(parent)
{
    m_components.reserve(20);
}

//------------------------------------------------------------------------------
ComponentDependencies::~ComponentDependencies()
{
    m_components.clear();
}

//------------------------------------------------------------------------------
bool ComponentDependencies::addComponent(IComponent *ip_component)
{
    if (ip_component == nullptr) {
        qDebug("null argument: ip_component.");
        return false;
    }

    if (componentByName(ip_component->name()) != nullptr) {
        qDebug("Attempt to add already existing component");
        return false;
    }

    m_components.push_back(ip_component);
    return true;
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::completeListWithChild(IComponent *ip_forChild) const
{
    QList<IComponent *> components;
    components.push_back(ip_forChild);

    return completeListWithChildren(components);
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::completeListWithChildren(const QList<IComponent *> &i_forChildren) const
{
    if (i_forChildren.empty())
        return DependenciesSolvingResult();

    QList<IComponent *> completeList;
    QList<IComponent *> unresolvedList(i_forChildren);

    while (unresolvedList.size() > 0) {
        IComponent *componentInfo = unresolvedList[0];
        if (componentInfo == nullptr) {
            unresolvedList.removeFirst();
            continue;
        }

        DependenciesSolvingResult result = getParentComponents(componentInfo);
        foreach (IComponent *dependency, result.ordered()) {
            if (dependency == nullptr)
                continue;

            if (!completeList.contains(dependency) && !unresolvedList.contains(dependency))
                unresolvedList.push_back(dependency);
        }

        unresolvedList.removeFirst();
        completeList.push_back(componentInfo);
    }

    DependenciesSolvingResult result = solveDependencies(completeList);
    return result;
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::completeListWithParent(IComponent *ip_forParent) const
{
    QList<IComponent *> components;
    components.push_back(ip_forParent);

    return completeListWithParents(components);
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::completeListWithParents(const QList<IComponent *> &ip_forParents) const
{
    if (ip_forParents.empty())
        return DependenciesSolvingResult();

    DependencySolver solver;

    QStringList ordered;
    QStringList orphans;
    QStringList missing;

    QList<IComponent *> completeList;
    QList<IComponent *> unresolvedList(ip_forParents);

    // TODO: refactoring is needed.
    // Find all children for parents and reverse parent-children dependencies for correct ordering:
    while (unresolvedList.size() > 0) {
        IComponent *parent = unresolvedList[0];
        solver.addComponent(parent->name());

        DependenciesSolvingResult result = getChildComponents(parent);
        foreach (IComponent * child, result.ordered()) {
            if (!completeList.contains(child) && !unresolvedList.contains(child)) {
                unresolvedList.push_back(child);
            }

            const ComponentDefinition *definition = child->definition();
            QStringList parents = definition->parents();
            foreach (const QString &dependencyName, parents) {
                solver.addComponent(dependencyName);
                solver.addDependency(dependencyName, child->name());
            }

        }

        unresolvedList.removeFirst();
        completeList.push_back(parent);
    }

    bool hasCyclic = !solver.solve(ordered, orphans, missing);
    if (hasCyclic) {
        qDebug("At least one cyclic dependency has been found in the component manager. Cycles in the component dependencies must be avoided.");
        return DependenciesSolvingResult(ordered, orphans, missing, m_components, hasCyclic);
    }

    if (!missing.isEmpty()) {
        qDebug(QString("A component declared a dependency on another component which is not declared to be loaded. Missing component(s): %1")
               .arg(missing.join(", ")).toLatin1());
    }

    return DependenciesSolvingResult(ordered, orphans, missing, m_components, hasCyclic);
}

//------------------------------------------------------------------------------
IComponent *ComponentDependencies::componentByName(const QString &i_byName) const
{
    if (m_components.empty())
        return nullptr;

    foreach(IComponent *p_com, m_components) {
        if (p_com->name() == i_byName)
            return p_com;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
QList<IComponent *> ComponentDependencies::components() const
{
    return m_components;
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::orderedComponents() const
{
    return completeListWithChildren(components());
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::getParentComponents(const IComponent *ip_forChild) const
{
    if (ip_forChild == nullptr)
        return DependenciesSolvingResult();

    const ComponentDefinition *definition = ip_forChild->definition();
    if (definition == nullptr)
        return DependenciesSolvingResult();

    QList<IComponent *> components_to_return;
    QStringList parents = definition->parents();

    foreach(IComponent *p_com, m_components) {
        if (parents.contains(p_com->name()))
            components_to_return.push_back(p_com);
    }

    return DependenciesSolvingResult(components_to_return);
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::getChildComponents(const IComponent *ip_forParent) const
{
    if (ip_forParent == nullptr)
        return DependenciesSolvingResult();

    if (!this->componentByName(ip_forParent->name()))
        return DependenciesSolvingResult();

    QList<IComponent *> components_to_return;

    foreach(IComponent *p_com, m_components) {
        const ComponentDefinition *definition = p_com->definition();
        QStringList parents = definition->parents();
        if (parents.contains(ip_forParent->name()))
            components_to_return.push_back(p_com);

    }

    return DependenciesSolvingResult(components_to_return);
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::solveDependencies(const QList<IComponent *> &i_components)
{
    QStringList ordered;
    QStringList orphans;
    QStringList missing;
    DependencySolver solver;

    foreach (IComponent *p_com, i_components) {
        solver.addComponent(p_com->name());

        const ComponentDefinition *definition = p_com->definition();
        QStringList parents = definition->parents();
        foreach (const QString &dependency, parents)
            solver.addDependency(p_com->name(), dependency);
    }

    bool hasCyclic = !solver.solve(ordered, orphans, missing);
    if (hasCyclic) {
        qDebug("At least one cyclic dependency has been found in the component manager. Cycles in the component dependencies must be avoided.");
        return DependenciesSolvingResult(ordered, orphans, missing, i_components, hasCyclic);
    }

    if (!missing.isEmpty()) {
        qDebug(QString("A component declared a dependency on another component which is not declared to be loaded. Missing component(s): %1")
               .arg(missing.join(", ")).toLatin1());
    }

    return DependenciesSolvingResult(ordered, orphans, missing, i_components, hasCyclic);
}

//------------------------------------------------------------------------------
