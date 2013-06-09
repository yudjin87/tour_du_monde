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

#ifndef DEPENDENCYSOLVER_H
#define DEPENDENCYSOLVER_H

#include <carousel/componentsystem/componentsystem_global.h>

#include <QtCore/QStringList>

template<typename TKey, typename TValue>
class ListDictionary;

/*!
 * @brief
 *   Used by IComponentManager to get the load sequence for the components to load according to
 *   their dependencies.
 * @details
 *   The component dependencies solving is an component names ordering indeed. At first component
 *   names are registered at the dependency matrix using addComponent() method, and then if component
 *   has dependencies, both - component itself and dependent component name - are registered in the
 *   matrix using addDependency() method. When all components and their dependencies were added to the
 *   solver, call solve() to calculate an ordered list according to the defined component dependencies.
 *   Non-dependant components appears at the beginning of the resulting collection.
 */
class COMP_API DependencySolver
{
public:
    DependencySolver();
    ~DependencySolver();

    /*!
     * @details
     *   Adds a component to the solver. The empty string
     *   does not considered as correct name, and will not be added.
     * @param name
     *   the name that uniquely identifies the component.
     */
    void addComponent(const QString &name);

    /*!
     * @details
     *   Adds a component dependency between the components specified by
     *   @a childComponent and @a parentComponent. The empty string
     *   does not considered as correct name, and will not be added.
     *
     * @param childComponent
     *   the name of the component with the dependency.
     * @param parentComponent
     *   the name of the component @a childComponent depends on.
     */
    void addDependency(const QString &childComponent, const QString &parentComponent);

    /*!
     * @details
     *   Gets the number of components added to the solver.
     */
    int componentsCount() const;

    /*!
     * @details
     *   Calculates an ordered list according to the defined dependencies. Non-dependant components
     *   appears at the beginning of the resulting collection.
     *
     * @param ordered The resulting ordered list of components.
     * @param orphans The list of components which parents are in the @a missing list.
     * @param missing The list of components declared a dependency on another component which
     *   is not added to the solver.
     * @return
     *   @a false if at least one cyclic dependency has been found during solving. Otherwise, returns
     *   @a true.
     */
    bool solve(QStringList &ordered, QStringList &orphans, QStringList &missing) const;

private:
    void addToDependencyMatrix(const QString &component);
    void addToKnownComponents(const QString &component);
    QStringList findLeaves(const QStringList &skip) const;
    void removeMissingComponents(const QString &unknownComponent, QStringList &orderedList, QStringList &orphans) const;

private:
    ListDictionary<QString, QString> *m_dependencyMatrix;
    QStringList m_knownComponents;
};

#endif // DEPENDENCYSOLVER_H
