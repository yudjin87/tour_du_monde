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
 *   Also manager uses IComponentDependencies for components sorting and finding components dependencies.
 *
 * @note it takes ownership for added components, and also takes for the IComponentDependencies.
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
     *   Creates an instance of the ComponentManager class with specified @a dependencies and
     *   default ComponentInitialiser instance.
     */
    ComponentManager(IComponentDependencies *dependencies, ILogger &log, QObject *parent = nullptr);

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
     *   Gets an initialization data that will be passed to the started components.
     * @sa startupComponent()
     */
    QObject *initializationData() const;

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
     *   Sets an initialization data that will be passed to the started components.
     * @sa startupComponent()
     */
    void setInitializationData(QObject *initData);

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
    DependenciesSolvingResult shutdownComponent(IComponent *ip_component);

    /*!
     * @details
     *   This method is added for convinient. It is a shortkey to the
     *   shutdownComponents(components()).
     *
     * @sa shutdownComponents()
     */
    DependenciesSolvingResult shutdownAllComponents();

    /*!
     * @details
     *   Shuts down specified components in such order, that
     *   children will be shuted down before their parents.
     *
     *   Shutted components are moved from the startedComponents() to
     *   the stoppedComponents() list.
     */
    DependenciesSolvingResult shutdownComponents(const QList<IComponent *> &components);

    /*!
     * @details
     *   Begins working and starts components which were added on the
     *   start of application. Starts only enabled components.
     *
     *   Components with disabled parent components will not be
     *   started.
     *
     *   Initialization data will be passed to the started components (if any).
     *
     * @sa shutdown()
     */
    DependenciesSolvingResult startup();

    /*!
     * @details
     *   Implicitly calls check() and starts (if resolving) up the specified components and
     *   all its parents, obtained by IComponentDependencies::completeListWithChild() in
     *   such order, that parents will be started first. All started components became
     *   enabled.
     *
     *   Components will not start if parent component could not start.
     *
     *   Initialization data will be passed to the started components (if any).
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found.
     *
     *   All started components will be moved from the stoppedComponents() to the
     *   startedComponents() list.
     *
     * @note component should be added to the manager before starting.
     * @sa addComponent(), check()
     */
    DependenciesSolvingResult startupComponent(IComponent *ip_component);

    /*!
     * @details
     *   This method is added for convinient. It is a shortkey to the
     *   startupComponents(components()).
     *
     *   Initialization data will be passed to the started components (if any).
     *
     * @sa addComponent(), check(), startupComponents()
     */
    DependenciesSolvingResult startupAllComponents();

    /*!
     * @details
     *   Implicitly calls check() and starts (if resolving) up the specified components and
     *   all its parents, obtained by IComponentDependencies::completeListWithChild() in
     *   such order, that parents will be started first. All started components became
     *   enabled.
     *
     *   Components will not start if parent component could not start.
     *
     *   Initialization data will be passed to the started components (if any).
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
    DependenciesSolvingResult startupComponents(QList<IComponent *> components);


protected slots:
    /*!
     * @details
     *   This method is invoked when @a ip_component is started up by the
     *   ComponentManager. It emits componentStarted() signal and moves @a ip_component
     *   from the stopped to started list.
     */
    virtual void onComponentStarted(IComponent *ip_component);

    /*!
     * @details
     *   This method is invoked before @a ip_component will be shuted down by the
     *   ComponentManager. It emits componentAboutToShutDown().
     */
    virtual void onComponentAboutToShutDown(IComponent *ip_component);

    /*!
     * @details
     *   This method is invoked when @a ip_component is shuted down by the
     *   ComponentManager. It emits componentShutedDown() signal and moves @a ip_component
     *   from the started to stopped list.
     */
    virtual void onComponentShutedDown(IComponent *ip_component);

    /*!
     * @details
     *   Starts specified component if it is possible (if component
     *   is enabled) and passes the initialization data to it.
     *
     *   Note, that components should have descending order,
     *   e.g. parents should stay before children, because
     *   parents should start first.
     *
     * @return @a true, if component was started. If component is
     *   disabled or unavailabled, returns @a false. Also returns
     *   @a false if component start was failed.
     */
    virtual bool startCheckedComponent(IComponent *component);

    /*!
     * @details
     *   Sets IComponent::Enabled availability to the specified
     *   component and tries to start up that component.
     *
     * @return @a true, if component was started. If component is
     *   disabled or unavailabled, returns @a false. Also returns
     *   @a false if component start was failed.
     */
    virtual bool enableAndStartComponent(IComponent *component);

    /*!
     * @details
     *   Shuts down specified component. Built in components are ignored.
     *
     *   Note, that components should have descending order,
     *   e.g. parents should stay before children, because
     *   children should shut down first.
     */
    virtual void shutdownCheckedComponent(IComponent *component);

    /*!
     * @details
     *   Shuts down specified component regardless whether it is built in
     *   or not.
     *
     *   Note, that components should have descending order,
     *   e.g. parents should stay before children, because
     *   children should shut down first.
     */
    virtual void forceShutdownCheckedComponent(IComponent *component);

private:
    bool addComponentInternal(IComponent *component);
    void resetCheck();

protected:
    ILogger &m_log;

private:
    typedef void (ComponentManager::*ShutDownFunc)(IComponent *);
    typedef bool (ComponentManager::*StartUpFunc)(IComponent *);
    ShutDownFunc m_shutDownFunc;
    StartUpFunc m_startUpFunc;
    QObject *m_initializationData;
    IComponentDependencies *mp_components;
    QList<IComponent *> m_startedComponents;
    QList<IComponent *> m_stoppedComponents;
    QSet<IComponent *> m_orphanComponents;
    DependenciesSolvingResult m_checkResult;
    bool m_isCheck;
    bool m_started;
};

#endif // COMPONENTMANAGER_H
