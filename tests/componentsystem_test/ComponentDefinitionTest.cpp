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

#include "ComponentDefinitionTest.h"
#include "fakes/MockComponent.h"

#include <componentsystem/ComponentDefinition.h>

#include <QtCore/QSettings>
#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
ComponentDefinitionTest::ComponentDefinitionTest(QObject *parent)
    : QObject(parent)
{
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, ".");
}

//------------------------------------------------------------------------------
void ComponentDefinitionTest::shouldSetAvailabilityEnabledByDefault()
{
    ComponentDefinition definition("");
    QCOMPARE(definition.availability(), ComponentDefinition::Enabled);
}

//------------------------------------------------------------------------------
void ComponentDefinitionTest::shouldSetLoadedAvailability()
{
    QSettings settings;
    settings.setValue(QString("components_availability/%1").arg("Comp1"), static_cast<int>(ComponentDefinition::Disabled));
    settings.sync();

    ComponentDefinition definition("Comp1");

    QCOMPARE(definition.availability(), ComponentDefinition::Disabled);

    settings.clear();
}

//------------------------------------------------------------------------------
void ComponentDefinitionTest::shouldEmitWhenAvailabilitySet()
{    
    ComponentDefinition definition("Comp1");
    QSignalSpy spy(&definition, SIGNAL(availabilityChanged(Availability)));

    definition.setAvailability(ComponentDefinition::Disabled);

    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void ComponentDefinitionTest::shouldEmitWhenAvailabilityLoaded()
{
    QSettings settings;
    settings.setValue(QString("components_availability/%1").arg("Comp1"), static_cast<int>(ComponentDefinition::Disabled));
    settings.sync();

    ComponentDefinition definition("Comp1");
    QSignalSpy spy(&definition, SIGNAL(availabilityChanged(Availability)));

    definition.loadAvailability();

    QCOMPARE(spy.count(), 1);

    settings.clear();
}

//------------------------------------------------------------------------------
void ComponentDefinitionTest::shouldNotSetAvailabilityIfDidNotLoad()
{
    QSettings settings;
    settings.setValue("components_availability/empty", 0);
    settings.sync();

    ComponentDefinition definition("Comp1");

    QCOMPARE(definition.availability(), ComponentDefinition::Enabled);
}

//------------------------------------------------------------------------------
