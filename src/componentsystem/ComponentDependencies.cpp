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

#include <logging/LoggerFacade.h>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ComponentDependencies");
}

//------------------------------------------------------------------------------
ComponentDependencies::ComponentDependencies(QObject *parent)
    : QObject(parent)
{
    m_components.reserve(20);
}

//------------------------------------------------------------------------------
ComponentDependencies::~ComponentDependencies()
{
}

//------------------------------------------------------------------------------
bool ComponentDependencies::addComponent(IComponent *component)
{
    if (component == nullptr) {
        Log.w("Attemp to add null component. Ignoring it.");
        return false;
    }

    if (componentByName(component->name()) != nullptr) {
        Log.w("Attemp to add already existing component. Ignoring it.");
        return false;
    }

    m_components.push_back(component);
    return true;
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::completeListWithChild(IComponent *forChild) const
{
    QList<IComponent *> components;
    components.push_back(forChild);

    return completeListWithChildren(components);
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::completeListWithChildren(const QList<IComponent *> &forChildren) const
{
    if (forChildren.empty())
        return DependenciesSolvingResult();

    QList<IComponent *> completeList;
    QList<IComponent *> unresolvedList(forChildren);

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
DependenciesSolvingResult ComponentDependencies::completeListWithParent(IComponent *forParent) const
{
    QList<IComponent *> components;
    components.push_back(forParent);

    return completeListWithParents(components);
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::completeListWithParents(const QList<IComponent *> &forParents) const
{
    if (forParents.empty())
        return DependenciesSolvingResult();

    DependencySolver solver;

    QList<IComponent *> completeList;
    QList<IComponent *> unresolvedList(forParents);

    // TODO: refactoring is needed.
    // Find all children for parents and reverse parent-children dependencies for correct ordering:
    while (unresolvedList.size() > 0) {
        IComponent *parent = unresolvedList[0];
        solver.addComponent(parent->name());

        DependenciesSolvingResult result = getChildComponents(parent);
        foreach (IComponent * child, result.ordered()) {
            if (!completeList.contains(child) && !unresolvedList.contains(child))
                unresolvedList.push_back(child);

            solver.addComponent(child->name());
            solver.addDependency(parent->name(), child->name());
        }

        unresolvedList.removeFirst();
        completeList.push_back(parent);
    }

    QStringList ordered;
    QStringList orphans;
    QStringList missing;

    bool hasCyclic = !solver.solve(ordered, orphans, missing);
    if (hasCyclic) {
        qDebug("At least one cyclic dependency has been found in the component manager. Cycles in the component dependencies must be avoided.");
        return DependenciesSolvingResult(ordered, orphans, missing, m_components.toList(), hasCyclic);
    }

    if (!missing.isEmpty()) {
        qDebug(QString("A component declared a dependency on another component which is not declared to be loaded. Missing component(s): %1")
               .arg(missing.join(", ")).toLatin1());
    }

    return DependenciesSolvingResult(ordered, orphans, missing, m_components.toList(), hasCyclic);
}

//------------------------------------------------------------------------------
IComponent *ComponentDependencies::componentByName(const QString &byName) const
{
    if (m_components.empty())
        return nullptr;

    foreach(IComponent *com, m_components) {
        if (com->name() == byName)
            return com;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
const ObservableList<IComponent *> &ComponentDependencies::components() const
{
    return m_components;
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::orderedComponents() const
{
    return completeListWithChildren(components().toList());
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::getParentComponents(const IComponent *forChild) const
{
    if (forChild == nullptr)
        return DependenciesSolvingResult();

    const ComponentDefinition *definition = forChild->definition();
    if (definition == nullptr)
        return DependenciesSolvingResult();

    QList<IComponent *> components_to_return;
    QStringList parents = definition->parents();

    foreach(IComponent *com, m_components) {
        if (parents.contains(com->name()))
            components_to_return.push_back(com);
    }

    return DependenciesSolvingResult(components_to_return);
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::getChildComponents(const IComponent *forParent) const
{
    if (forParent == nullptr)
        return DependenciesSolvingResult();

    if (!this->componentByName(forParent->name()))
        return DependenciesSolvingResult();

    QList<IComponent *> components_to_return;

    foreach(IComponent *com, m_components) {
        const ComponentDefinition *definition = com->definition();
        QStringList parents = definition->parents();
        if (parents.contains(forParent->name()))
            components_to_return.push_back(com);

    }

    return DependenciesSolvingResult(components_to_return);
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentDependencies::solveDependencies(const QList<IComponent *> &components)
{
    QStringList ordered;
    QStringList orphans;
    QStringList missing;
    DependencySolver solver;

    foreach (IComponent *com, components) {
        solver.addComponent(com->name());

        const ComponentDefinition *definition = com->definition();
        QStringList parents = definition->parents();
        foreach (const QString &dependency, parents)
            solver.addDependency(com->name(), dependency);
    }

    bool hasCyclic = !solver.solve(ordered, orphans, missing);
    if (hasCyclic) {
        Log.w("At least one cyclic dependency has been found in the component manager. Cycles in the component dependencies must be avoided.");
        return DependenciesSolvingResult(ordered, orphans, missing, components, hasCyclic);
    }

    if (!missing.isEmpty()) {
        Log.w(QString("A component declared a dependency on another component which is not declared to be loaded. Missing component(s): %1")
               .arg(missing.join(", ")).toLatin1());
    }

    return DependenciesSolvingResult(ordered, orphans, missing, components, hasCyclic);
}

//------------------------------------------------------------------------------
