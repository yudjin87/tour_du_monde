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

#ifndef ICOMPONENTDEPENDENCIES_H
#define ICOMPONENTDEPENDENCIES_H

#include "componentsystem/componentsystem_global.h"
#include "componentsystem/DependenciesSolvingResult.h"

#include <QtCore/QList>

class IComponent;

template <typename TItem>
class ObservableList;


/*!
 * @brief
 *   The IComponentDependencies interface provides methods to get all dependencies
 *   between the components.
 * @details
 *   Each component (described in a IComponent and IComponentDescriptionExtension classes, stores the name,
 *   description and availability of the component) that statically registered or dynamically discovered
 *   by providers will be added to the IComponentDependencies through IComponentManager after boot loading
 *   sequence in CarouselBootloader::_configureComponentManager() method.
 *
 *   Then you can get any dependnecies between the components using specified methods.
 * @note it does not take ownership for added components.
 */
class COMP_API IComponentDependencies
{
public:
    IComponentDependencies(){}
    virtual ~IComponentDependencies(){}

    /*!
     * @details
     *   Adds a new component. Component with same name should not already exists in.
     *
     * @param component
     *   If IComponentDependencies already has component with same name as @a component
     *   - the last one will not be added. The same for the null pointer - it will be ignored.
     *
     *   Returns @a true if component was succesfully added. If it is a null point or already
     *   existed one - returns @a false.
     */
    virtual bool addComponent(IComponent *component) = 0;

    /*!
     * @details
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found. The component list
     *   will contains all immediate and extended parents for specified child component.
     *
     *   The components are ordered in such way, that parents are firsts and child is last.
     *   E.g. if you have following graph
     * @code
     *              E
     *              v
     *    A <- B <- C <- D
     * @endcode
     *   and you call completeListWithChild() for the @a C component,
     *   the @a A, @a B and @a C components will be returned in that order.
     *
     * @param forChild
     *   The component to get the dependencies (or parents) for.
     */
    virtual DependenciesSolvingResult completeListWithChild(IComponent *forChild) const = 0;

    /*!
     * @details
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found. The component list
     *   will contains all immediate and extended parents for specified children components.
     *
     *   The components are ordered in such way, that parents are firsts and children are last.
     *
     * @param forChildren
     *   The components to get the dependencies (or parents) for.
     */
    virtual DependenciesSolvingResult completeListWithChildren(const QList<IComponent *> &forChildren) const = 0;

    /*!
     * @details
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found. The component list
     *   will contains all immediate and extended children for specified parent component.
     *
     *   The components are ordered in such way, that children are firsts and parent is last.
     *   E.g. if you have following graph
     * @code
     *              E
     *              v
     *    A <- B <- C <- D
     * @endcode
     *   and you call completeListWithParent() for the @a C component,
     *   the @a E, @a D and @a C components will be returned in such order,
     *   where indexOf(E) < indexOf(C) and indexOf(D) < indexOf(C).
     *
     * @param forParent
     *   The component to get the components that depend on it (or its implicit children).
     */
    virtual DependenciesSolvingResult completeListWithParent(IComponent *forParent) const = 0;

    /*!
     * @details
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found. The component list
     *   will contains all immediate and extended children for specified parents components.
     *
     *   The components are ordered in such way, that children are firsts and parents are last.
     *   E.g. if you have following graph
     * @code
     *              E
     *              v
     *    A <- B <- C <- D
     * @endcode
     *   and you call completeListWithParents() for the @a C component,
     *   the @a E, @a D and @a C components will be returned in such order,
     *   where indexOf(E) < indexOf(C) and indexOf(D) < indexOf(C).
     *
     * @param forParents
     *   The components to get the other components that depend on they (or their implicit children).
     */
    virtual DependenciesSolvingResult completeListWithParents(const QList<IComponent *> &forParents) const = 0;

    /*!
     * @details
     *   Finds the component by its name.
     *   Null pointer, if list is empty, or if component with specified name was not added.
     */
    virtual IComponent *componentByName(const QString &byName) const = 0;

    /*!
     * @details
     *   Returns a list of added components.
     */
    virtual const ObservableList<IComponent *> &components() const = 0;

    /*!
     * @details
     *   Returns a dependencies solving result for cpecified child, that contains a list of
     *   distinct components and a list of components, those dependencies were not found.
     *   E.g. if we have components
     * @code
     *   A <- B <- C <- E
     *             D <──┘
     * @endcode
     *   then, getParentComponents(E) will return {A, B, C, D} components.
     * @param forChild
     *   The component to get the dependencies (or parents) for.
     *   If @a forChild is null - result with empty collections will be returned.
     */
    virtual DependenciesSolvingResult getParentComponents(const IComponent *forChild) const = 0;

    /*!
     * @details
     *   Returns a dependencies solving result for cpecified parent, that contains a list of
     *   distinct components and a list of components, those dependencies were not found.
     *   E.g. if we have components
     * @code
     *   A <- B <- C <- E
     *             ^
     *             └─── D
     * @endcode
     *   then, getChildComponents(C) will return {E, D} components.
     * @param forParent
     *   The component to get the other components that depend on it (or its implicit children).
     *   If @a forParent is null or component with such name does not exists - result with
     *   empty collections will be returned.
     */
    virtual DependenciesSolvingResult getChildComponents(const IComponent *forParent) const = 0;

    /*!
     * @details
     *   Returns a dependencies solving result for all components, that contains a list of distinct
     *   components and a list of components, those dependencies were not found. The component list
     *   will contains all immediate and extended parents for specified children components.
     *
     *   The components are ordered in such way, that parents are firsts and children are lasts.
     *
     *   It is a shortkey for the
     * @code
     *   completeListWithChildren(components())
     * @endcode
     */
    virtual DependenciesSolvingResult orderedComponents() const = 0;

private:
    Q_DISABLE_COPY(IComponentDependencies)
};

#endif // ICOMPONENTDEPENDENCIES_H
