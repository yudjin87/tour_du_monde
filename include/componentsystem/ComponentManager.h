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

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "componentsystem/IComponentManager.h"
#include "componentsystem/IComponentInitialiser.h"

#include <QtCore/QStringList>
#include <QtCore/QSet>

class ILogger;

/*!
 * @brief
 *   The ComponentManager holds information about the components that can be used by the application.
 * @details
 *   Each component (described in a IComponent and ComponentDefinition classes, stores the name,
 *   description and availability of the component) that was statically registered or dynamically discovered
 *   by providers will be added to the ComponentManager after boot loading sequence in
 *   CarouselBootloader::_configureComponentManager() method. Components also can be added and
 *   started during run-time.
 *
 *   Then, after checking and resolving dependencies, all enabled components will be started
 *   with AbstractApplication reference as @a initialziation @a data.
 *   It enables components to get access to your application.
 *
 *   The ComponentManager uses IComponentInitialiser (for startup, shutdown, etc) inside. You can
 *   set your custom instance in your bootloader.
 *
 *   Also manager uses IComponentDependencies for components sorting and finding components dependencies.
 *
 * @note it takes ownership for added components, and also takes for the IComponentDependencies
 *   and IComponentInitialiser.
 */
class COMP_API ComponentManager : public IComponentManager
{
    Q_OBJECT
public:
    /*!
     * @details
     *   Creates an instance of the ComponentManager class with default ComponentInitialiser and
     *   ComponentDependencies instances.
     */
    ComponentManager(ILogger &log, QObject *parent = nullptr);

    /*!
     * @details
     *   Creates an instance of the ComponentManager class with specified @a initializer and
     *   default ComponentDependencies instance.
     */
    ComponentManager(IComponentInitialiser *initializer, ILogger &log, QObject *parent = nullptr);

    /*!
     * @details
     *   Creates an instance of the ComponentManager class with specified @a dependencies and
     *   default ComponentInitialiser instance.
     */
    ComponentManager(IComponentDependencies *dependencies, ILogger &log, QObject *parent = nullptr);

    /*!
     * @details
     *   Creates an instance of the ComponentManager class with specified @a dependencies and
     *   @a initializer.
     */
    ComponentManager(IComponentDependencies *dependencies, IComponentInitialiser *initializer, ILogger &log, QObject *parent = nullptr);
    ~ComponentManager();

    /*!
     * @details
     *   Adds a new component. Component with same name should not already exists in
     *   the manager.
     *
     *   A newly is appended to the stoppedComponents() list and to the dependencies().
     *   This method sets isChecked() to false.
     * @param ip_component
     *   If manager already has component with same name as @a ip_component - the last one will
     *   not be added to the manager. The same for the null pointer - it will be ignored.
     *
     *   Returns @a true if component was succesfully added. If it is a null point or already
     *   existed one - returns @a false. Note, that ComponentManager does not take ownership
     *   for component, which was not successfully added.
     *
     * @sa IComponentDependencies::addComponent()
     */
    bool addComponent(IComponent *ip_component);

    /*!
     * @details
     *   Uses DependencySolver for checking of added components according to their dependencies.
     *
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found.
     *
     *   It caches resulting value for prefomance, but addComponent() is resets it.
     *
     * @sa isChecked()
     */
    DependenciesSolvingResult check();

    /*!
     * @details
     *   Returns a list of all added components.
     *   It is a shortcut to the IComponentDependencies::components().
     *
     * @sa IComponentDependencies::dependencies().
     */
    const ObservableList<IComponent *> &components() const;

    /*!
     * @details
     *   Returns a component dependencies.
     */
    const IComponentDependencies &dependencies() const;

    /*!
     * @details
     *   Uses DependencySolver for checking of added components according to their dependencies.
     *
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found.
     *
     * @sa check()
     */
    bool isChecked() const;

    /*!
     * @details
     *   Returns a component initializer.
     */
    const IComponentInitialiser &initializer() const;

    /*!
     * @details
     *   Returns a list of missing parent names those children were added
     *   to the manager.
     *
     *   This list is populated after check() or startup/shutdown components
     *   and resets after the addComponent() call.
     *
     * @sa orphanComponents()
     */
    QStringList missingComponents() const;

    /*!
     * @details
     *   Returns a list of components those parents were not added
     *   to the manager while components were started.
     *
     *   This list is populated after check() or startup/shutdown components
     *   and resets after the addComponent() call.
     *
     * @sa missingComponents()
     */
    QList<IComponent *> orphanComponents() const;

    /*!
     * @details
     *   Returns a list of already stopped or non-started yet components.
     */
    QList<IComponent *> stoppedComponents() const;

    /*!
     * @details
     *   Returns a list of started components.
     */
    QList<IComponent *> startedComponents() const;

    /*!
     * @details
     *   Shuts down all the components. Call this method when your application is going to
     *   quit
     */
    void shutdown();

    /*!
     * @details
     *   Shuts down the specified component and all its implicit children,
     *   obtained by IComponentDependencies::completeListWithParent() in such order, that
     *   children will be shuted down first.
     *
     *   Shutted component is moved from the startedComponents() to
     *   the stoppedComponents() list.
     *
     *   Ignores null pointer or unexisting component.
     */
    void shutdownComponent(IComponent *ip_component);

    /*!
     * @details
     *   This method is added for convinient. It is a shortkey to the
     *   shutdownComponents(components()).
     *
     * @sa shutdownComponents()
     */
    void shutdownAllComponents();

    /*!
     * @details
     *   Shuts down specified components in such order, that
     *   children will be shuted down before their parents.
     *
     *   Shutted components are moved from the startedComponents() to
     *   the stoppedComponents() list.
     */
    void shutdownComponents(const QList<IComponent *> &components);

    /*!
     * @details
     *   Implicitly calls check() and starts (if resolving) up the specified component and
     *   all its parents, obtained by IComponentDependencies::completeListWithChild() in
     *   such order, that parents will be started first.
     *
     *   Disabled components and components with disabled parent components will not be
     *   started.
     *
     *   @a ip_initializationData will be passed to the started components.
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found.
     *
     *   All started components will be moved from the stoppedComponents() to the
     *   startedComponents() list.
     *
     * @note component should be added to the manager before starting.
     * @sa addComponent(), check()
     */
    DependenciesSolvingResult startupComponent(IComponent *ip_component, QObject *ip_initializationData = nullptr);

    /*!
     * @details
     *   This method is added for convinient. It is a shortkey to the
     *   startupComponents(components()).
     *
     * @sa addComponent(), check(), startupComponents()
     */
    DependenciesSolvingResult startupAllComponents(QObject *ip_initializationData = nullptr);

    /*!
     * @details
     *   Implicitly calls check() and starts (if resolving) up the specified components and
     *   all its parents, obtained by IComponentDependencies::completeListWithChild() in
     *   such order, that parents will be started first.
     *
     *   Disabled components and components with disabled parent components will not be
     *   started.
     *
     *   @a ip_initializationData will be passed to the started components.
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found.
     *
     *   Components, those parents were not added to manager, will be appended to the
     *   orphanComponents() list and names of their missing parents will be appended to
     *   the missingComponents() list. All started components will be moved from the
     *   stoppedComponents() to the startedComponents() list.
     *
     * @note components should be added to the manager before starting.
     * @sa addComponent(), check(), startupAllComponents()
     */
    DependenciesSolvingResult startupComponents(QList<IComponent *> components, QObject *ip_initializationData = nullptr);


protected slots:
    /*!
     * @details
     *   This method is invoked when @a ip_component is started up by the
     *   ComponentManager. It emits componentStarted() signal and moves @a ip_component
     *   from the stopped to started list.
     */
    void onComponentStarted(IComponent *ip_component);

    /*!
     * @details
     *   This method is invoked when @a ip_component is shuted down by the
     *   ComponentManager. It emits componentShutedDown() signal and moves @a ip_component
     *   from the started to stopped list.
     */
    void onComponentShutedDown(IComponent *ip_component);

private:
    bool addComponentInternal(IComponent *component);
    void resetCheck();

protected:
    ILogger &m_log;

private:
    typedef void (IComponentInitialiser::*InitialiserShutDownFunc)(IComponent *);
    InitialiserShutDownFunc m_shutDownFunc;
    IComponentDependencies *mp_components;
    IComponentInitialiser *mp_componentInitialiser;
    QList<IComponent *> m_startedComponents;
    QList<IComponent *> m_stoppedComponents;
    QSet<IComponent *> m_orphanComponents;
    DependenciesSolvingResult m_checkResult;
    bool m_isCheck;
};

#endif // COMPONENTMANAGER_H
