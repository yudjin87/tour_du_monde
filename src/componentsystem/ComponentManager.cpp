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

#include "ComponentManager.h"
#include "ComponentDependencies.h"
#include "ComponentInitialiser.h"
#include "IComponent.h"

#include <logging/ILogger.h>
#include <utils/IServiceLocator.h>
#include <utils/ObservableList.h>

#include <QtCore/QSet>
#include <QtCore/QCoreApplication>

//------------------------------------------------------------------------------
ComponentManager::ComponentManager(ILogger &log, QObject *parent)
    : m_log(log)
    , m_shutDownFunc(&IComponentInitialiser::shutdownComponent)
    , m_initializationData(QCoreApplication::instance())
    , mp_components(new ComponentDependencies())
    , mp_componentInitialiser(new ComponentInitialiser(log))
    , m_startedComponents(QList<IComponent *>())
    , m_stoppedComponents(QList<IComponent *>())
    , m_orphanComponents(QSet<IComponent *>())
    , m_isCheck(false)
{
    QObject::setParent(parent);
}

//------------------------------------------------------------------------------
ComponentManager::ComponentManager(IComponentInitialiser *initializer, ILogger &log, QObject *parent)
    : m_log(log)
    , m_shutDownFunc(&IComponentInitialiser::shutdownComponent)
    , m_initializationData(QCoreApplication::instance())
    , mp_components(new ComponentDependencies())
    , mp_componentInitialiser(initializer)
    , m_startedComponents(QList<IComponent *>())
    , m_stoppedComponents(QList<IComponent *>())
    , m_orphanComponents(QSet<IComponent *>())
    , m_isCheck(false)
{
    QObject::setParent(parent);
    Q_ASSERT(mp_componentInitialiser != nullptr);
}

//------------------------------------------------------------------------------
ComponentManager::ComponentManager(IComponentDependencies *dependencies, ILogger &log, QObject *parent)
    : m_log(log)
    , m_shutDownFunc(&IComponentInitialiser::shutdownComponent)
    , m_initializationData(QCoreApplication::instance())
    , mp_components(dependencies)
    , mp_componentInitialiser(new ComponentInitialiser(log))
    , m_startedComponents(QList<IComponent *>())
    , m_stoppedComponents(QList<IComponent *>())
    , m_orphanComponents(QSet<IComponent *>())
    , m_isCheck(false)
{
    QObject::setParent(parent);
    Q_ASSERT(mp_components != nullptr);
}

//------------------------------------------------------------------------------
ComponentManager::ComponentManager(IComponentDependencies *dependencies, IComponentInitialiser *initializer, ILogger &log, QObject *parent)
    : m_log(log)
    , m_shutDownFunc(&IComponentInitialiser::shutdownComponent)
    , m_initializationData(QCoreApplication::instance())
    , mp_components(dependencies)
    , mp_componentInitialiser(initializer)
    , m_startedComponents(QList<IComponent *>())
    , m_stoppedComponents(QList<IComponent *>())
    , m_orphanComponents(QSet<IComponent *>())
    , m_isCheck(false)
{
    QObject::setParent(parent);
    Q_ASSERT(mp_components != nullptr);
    Q_ASSERT(mp_componentInitialiser != nullptr);
}

//------------------------------------------------------------------------------
ComponentManager::~ComponentManager()
{
    foreach(IComponent *comp, mp_components->components())
        delete comp;

    delete mp_componentInitialiser;
    mp_componentInitialiser = nullptr;

    delete mp_components;
    mp_components = nullptr;
}

//------------------------------------------------------------------------------
bool ComponentManager::addComponent(IComponent *ip_component)
{
    bool result = addComponentInternal(ip_component);
    resetCheck();
    return result;
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentManager::check()
{
    if (isChecked())
        return m_checkResult;

    m_isCheck = true;

    DependenciesSolvingResult result = mp_components->orderedComponents();
    m_checkResult = result;

    return m_checkResult;
}

//------------------------------------------------------------------------------
const ObservableList<IComponent *> &ComponentManager::components() const
{
    return mp_components->components();
}

//------------------------------------------------------------------------------
const IComponentDependencies &ComponentManager::dependencies() const
{
    return *mp_components;
}

//------------------------------------------------------------------------------
bool ComponentManager::isChecked() const
{
    return m_isCheck;
}

//------------------------------------------------------------------------------
const IComponentInitialiser &ComponentManager::initializer() const
{
    return *mp_componentInitialiser;
}

//------------------------------------------------------------------------------
QObject *ComponentManager::initializationData() const
{
    return m_initializationData;
}

//------------------------------------------------------------------------------
QStringList ComponentManager::missingComponents() const
{
    return m_checkResult.missing();
}

//------------------------------------------------------------------------------
QList<IComponent *> ComponentManager::orphanComponents() const
{
    return m_checkResult.orphans();
}

//------------------------------------------------------------------------------
void ComponentManager::setInitializationData(QObject *initData)
{
    m_initializationData = initData;
}

//------------------------------------------------------------------------------
QList<IComponent *> ComponentManager::stoppedComponents() const
{
    return m_stoppedComponents;
}

//------------------------------------------------------------------------------
QList<IComponent *> ComponentManager::startedComponents() const
{
    return m_startedComponents;
}

//------------------------------------------------------------------------------
void ComponentManager::shutdown()
{
    m_shutDownFunc = &IComponentInitialiser::forceShutdownComponent;
    shutdownAllComponents();
    m_shutDownFunc = &IComponentInitialiser::shutdownComponent;
}

//------------------------------------------------------------------------------
void ComponentManager::shutdownComponent(IComponent *ip_component)
{
    QList<IComponent *> components;
    components.push_back(ip_component);
    shutdownComponents(components);
}

//------------------------------------------------------------------------------
void ComponentManager::shutdownAllComponents()
{
    shutdownComponents(mp_components->components().toList());
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentManager::startupComponent(IComponent *ip_component)
{
    QList<IComponent *> components;
    components.push_back(ip_component);

    return startupComponents(components);
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentManager::startupAllComponents()
{
    return startupComponents(mp_components->components().toList());
}

//------------------------------------------------------------------------------
DependenciesSolvingResult ComponentManager::startupComponents(QList<IComponent *> components)
{
    if (components.empty())
        return DependenciesSolvingResult();

    check();

    // Try to resolve orphan components from the previous starts, because they parents
    // may appear
    components.append(m_orphanComponents.toList());
    DependenciesSolvingResult solvingResult = mp_components->completeListWithChildren(components);

    QSet<IComponent *> skippedComponents;
    QList<IComponent *> componentsToStart = solvingResult.ordered();
    foreach(IComponent *comp, componentsToStart) {
        if (comp->started() || skippedComponents.contains(comp))
            continue;

        if (!mp_components->components().contains(comp)) {
            m_log.log(QString("Can not start unexisting component: \"%1\"").arg(comp->name()), ILogger::Info);
            continue;
        }

        if (mp_componentInitialiser->startupComponent(comp, m_initializationData)) {
            m_log.log(QString("'%1' component is started").arg(comp->name()), ILogger::Info);
            onComponentStarted(comp);
        } else {
            m_log.log(QString("Can not startup component: '%1'").arg(comp->name()), ILogger::Info);

            QStringList skipedChildren;
            DependenciesSolvingResult children = mp_components->completeListWithParent(comp);
            foreach(IComponent *comp, children.ordered()) {
                skippedComponents.insert(comp);
                skipedChildren.append(comp->name());
            }

            QString info = QString("Following child component(s) will not started too: %1").arg(skipedChildren.join(","));
            m_log.log(info, ILogger::Info);
        }
    }

    m_orphanComponents += solvingResult.orphans().toSet();

    return solvingResult;
}

//------------------------------------------------------------------------------
void ComponentManager::shutdownComponents(const QList<IComponent *> &components)
{
    if (components.empty())
        return;

    DependenciesSolvingResult solvingResult = mp_components->completeListWithParents(components);
    QList<IComponent *> componentsToShutdown = solvingResult.ordered();

    foreach(IComponent *comp, componentsToShutdown) {
        if (!mp_components->components().contains(comp)) {
            m_log.log(QString("Can not shutdown unexisting component: \"%1\"").arg(comp->name()), ILogger::Info);
            continue;
        }

        onComponentAboutToShutDown(comp);
        (mp_componentInitialiser->*(m_shutDownFunc))(comp);
        m_log.log(QString("'%1' component is shutted down").arg(comp->name()), ILogger::Info);
        onComponentShutedDown(comp);
    }
}

//------------------------------------------------------------------------------
void ComponentManager::onComponentStarted(IComponent *ip_component)
{    
    m_stoppedComponents.removeOne(ip_component);
    m_startedComponents.push_back(ip_component);
    emit componentStarted(ip_component);
}

//------------------------------------------------------------------------------
void ComponentManager::onComponentAboutToShutDown(IComponent *ip_component)
{
    emit componentAboutToShutDown(ip_component);
}

//------------------------------------------------------------------------------
void ComponentManager::onComponentShutedDown(IComponent *ip_component)
{
    m_startedComponents.removeOne(ip_component);
    m_stoppedComponents.push_back(ip_component);
    emit componentShutedDown(ip_component);
}

//------------------------------------------------------------------------------
bool ComponentManager::addComponentInternal(IComponent *component)
{
    if (!mp_components->addComponent(component))
        return false;

    m_stoppedComponents.push_back(component);
    return true;
}

//------------------------------------------------------------------------------
void ComponentManager::resetCheck()
{
    m_isCheck = false;
    m_checkResult = DependenciesSolvingResult();
}

//------------------------------------------------------------------------------
