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

#include "ComponentInitialiserTest.h"

#include "fakes/MockComponent.h"
#include "fakes/TestDescriptionComponent.h"

#include <componentsystem/ComponentInitialiser.h>
#include <logging/NullLogger.h>

#include <QtTest/QtTest>

//------------------------------------------------------------------------------
namespace { NullLogger lg; }

//------------------------------------------------------------------------------
ComponentInitialiserTest::ComponentInitialiserTest()
{
}

//------------------------------------------------------------------------------
void ComponentInitialiserTest::shouldStartupComponent()
{
    MockComponent component;
    QSignalSpy spy(&component, SIGNAL(whenStarted(const QString &)));

    ComponentInitialiser initialser(lg);
    initialser.startupComponent(&component, this);

    QCOMPARE(spy.count(), 1);
    QVERIFY(component.started());
}

//------------------------------------------------------------------------------
void ComponentInitialiserTest::shouldReturnTrueWhenStartupComponent()
{
    MockComponent component;

    ComponentInitialiser initialser(lg);
    bool result = initialser.startupComponent(&component, this);

    QVERIFY(result);
}

//------------------------------------------------------------------------------
void ComponentInitialiserTest::shouldNotStartupDisabledComponent()
{
    TestDescriptionComponent disabledDomponent;
    disabledDomponent.setAvailability(IComponent::Disabled);
    QSignalSpy spy(&disabledDomponent, SIGNAL(whenStarted(QString)));

    ComponentInitialiser initialser(lg);
    initialser.startupComponent(&disabledDomponent, this);

    QCOMPARE(spy.count(), 0);
}

//------------------------------------------------------------------------------
void ComponentInitialiserTest::shouldNotStartupUnavailableComponent()
{
    TestDescriptionComponent disabledDomponent;
    disabledDomponent.setAvailability(IComponent::Unavailable);
    QSignalSpy spy(&disabledDomponent, SIGNAL(whenStarted(QString)));

    ComponentInitialiser initialser(lg);
    initialser.startupComponent(&disabledDomponent, this);

    QCOMPARE(spy.count(), 0);
}

//------------------------------------------------------------------------------
void ComponentInitialiserTest::shouldReturnFalseWhenStartupDisabledComponent()
{
    TestDescriptionComponent disabledComponent;
    disabledComponent.setAvailability(IComponent::Disabled);

    ComponentInitialiser initialser(lg);
    bool result = initialser.startupComponent(&disabledComponent, this);

    QVERIFY(!result);
}

//------------------------------------------------------------------------------
void ComponentInitialiserTest::shouldReturnFalseWhenStartupUnavailableComponent()
{
    TestDescriptionComponent unavailableComponent;
    unavailableComponent.setAvailability(IComponent::Unavailable);

    ComponentInitialiser initialser(lg);
    bool result = initialser.startupComponent(&unavailableComponent, this);

    QVERIFY(!result);
}

//------------------------------------------------------------------------------
void ComponentInitialiserTest::shouldPassInitDataToStartupComponents()
{
    MockComponent component;

    ComponentInitialiser initialser(lg);
    initialser.startupComponent(&component, this);

    QCOMPARE(component.data(), this);
}

//------------------------------------------------------------------------------
void ComponentInitialiserTest::shouldShutdownComponents()
{
    MockComponent component;
    component.startup(this);
    QSignalSpy spy(&component, SIGNAL(whenShutdown(const QString &)));

    ComponentInitialiser initialser(lg);
    initialser.shutdownComponent(&component);

    QCOMPARE(spy.count(), 1);
}


//------------------------------------------------------------------------------
void ComponentInitialiserTest::shouldNotShutdownBuiltInComponent()
{
    MockComponent mockComponent("MockComponent", true);
    QSignalSpy spy(&mockComponent, SIGNAL(whenShutdown(const QString &)));

    mockComponent.startup(nullptr);

    QCOMPARE(mockComponent.started(), true);

    ComponentInitialiser initialser(lg);
    initialser.shutdownComponent(&mockComponent);

    // make sure the signal wasn't emitted
    QCOMPARE(spy.count(), 0);
    QCOMPARE(mockComponent.started(), true);
}

//------------------------------------------------------------------------------
void ComponentInitialiserTest::shouldShutdownBuilInComponentForcely()
{
    MockComponent component;
    component.startup(this);
    QSignalSpy spy(&component, SIGNAL(whenShutdown(const QString &)));

    ComponentInitialiser initialser(lg);
    initialser.forceShutdownComponent(&component);

    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
