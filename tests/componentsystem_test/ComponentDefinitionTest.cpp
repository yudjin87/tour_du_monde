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

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ParentDefinition.h>
#include <carousel/componentsystem/ParentDefinitions.h>

#include <QtTest/QTest>

//------------------------------------------------------------------------------
ComponentDefinitionTest::ComponentDefinitionTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void ComponentDefinitionTest::isCompatible_shouldReturnTrue()
{
    ParentDefinitions definitions;
    definitions.append(new ParentDefinition("CompA", 1, 2, 3, 4));
    definitions.append(new ParentDefinition("CompB", 2, 3, 4, 5));
    definitions.append(new ParentDefinition("CompC", 3, 4, 5, 6));

    ComponentDefinition definition;
    definition.addParent(new ParentDefinition("CompA", 1, 2, 3, 4));
    definition.addParent(new ParentDefinition("CompB", 2, 3, 4, 5));
    definition.addParent(new ParentDefinition("CompC", 3, 4, 5, 6));

    QVERIFY(definition.isCompatible(definitions));
}

//------------------------------------------------------------------------------
void ComponentDefinitionTest::isCompatible_shouldReturnTrueForUnknownParent()
{
    ParentDefinitions definitions;
    definitions.append(new ParentDefinition("CompA", 1, 2, 3, 4));
    definitions.append(new ParentDefinition("CompB", 2, 3, 4, 5));

    ComponentDefinition definition;
    definition.addParent(new ParentDefinition("CompA", 1, 2, 3, 4));

    QVERIFY(definition.isCompatible(definitions));
}

//------------------------------------------------------------------------------
void ComponentDefinitionTest::isCompatible_shouldReturnFalseIfAtLeastOneDoesNotMatch()
{
    ParentDefinitions definitions;
    definitions.append(new ParentDefinition("CompA", 1, 0, 0, 0));
    definitions.append(new ParentDefinition("CompB", 1, 0, 0, 0));
    definitions.append(new ParentDefinition("CompC", 9, 9, 9, 9));

    ComponentDefinition definition;
    definition.addParent(new ParentDefinition("CompA", 1, 0, 0, 0));
    definition.addParent(new ParentDefinition("CompB", 1, 0, 0, 0));
    definition.addParent(new ParentDefinition("CompC", 1, 0, 0, 0));

    QVERIFY(!definition.isCompatible(definitions));
}

//------------------------------------------------------------------------------
