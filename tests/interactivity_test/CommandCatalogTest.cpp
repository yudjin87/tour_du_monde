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

#include "CommandCatalogTest.h"
#include "fakes/MockCommand.h"

#include <interactivity/CommandCatalog.h>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
CommandCatalogTest::CommandCatalogTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void CommandCatalogTest::shouldAddCommandToList()
{
    CommandCatalog catalog;
    MockCommand *command = new MockCommand();
    catalog.add(command);

    QVERIFY(command == catalog.commands()[0]);
}

//------------------------------------------------------------------------------
void CommandCatalogTest::shouldEmitWhenCommandAdded()
{
    CommandCatalog catalog;
    MockCommand *command = new MockCommand();
    QSignalSpy spy(&catalog, SIGNAL(commandAdded(Command *)));

    catalog.add(command);
    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void CommandCatalogTest::shouldInitializeAddedCommand()
{
    CommandCatalog catalog;
    MockCommand *command = new MockCommand();
    catalog.add(command);

    QVERIFY(command->initializeCalled);
}

//------------------------------------------------------------------------------
void CommandCatalogTest::shouldInitializeAddedCommandWithStartupData()
{
    CommandCatalog catalog;
    QObject data;
    catalog.setStartupData(&data);

    MockCommand *command = new MockCommand();
    catalog.add(command);

    QCOMPARE(&data, command->mp_startUpData);
}

//------------------------------------------------------------------------------
void CommandCatalogTest::shouldReturnTheSameCommand()
{
    CommandCatalog catalog;
    MockCommand *command = new MockCommand();

    QVERIFY(command == catalog.add(command));
}

//------------------------------------------------------------------------------
void CommandCatalogTest::shouldReturnCommandsByCategory()
{
    CommandCatalog catalog;
    MockCommand *command = new MockCommand(); command->setCategory("ctg");
    MockCommand *command1 = new MockCommand(); command1->setCategory("ctg1");
    MockCommand *command2 = new MockCommand(); command2->setCategory("ctg2");
    catalog.add(command);
    catalog.add(command1);
    catalog.add(command2);

    QList<Command *> commands = catalog.commands("ctg1");

    QCOMPARE(commands.size(), 1);
    QVERIFY(command1 == commands[0]);
}

//------------------------------------------------------------------------------
void CommandCatalogTest::shouldFindCommandByName()
{
    CommandCatalog catalog;
    MockCommand *command = new MockCommand(); command->setName("ctg");
    MockCommand *command1 = new MockCommand(); command1->setName("ctg1");
    MockCommand *command2 = new MockCommand(); command2->setName("ctg2");
    catalog.add(command);
    catalog.add(command1);
    catalog.add(command2);

    QVERIFY(command == catalog.find("ctg"));
}

//------------------------------------------------------------------------------
void CommandCatalogTest::shouldDeleteCommand()
{
    CommandCatalog catalog;
    MockCommand *command = new MockCommand(); command->setName("ctg");
    MockCommand *command1 = new MockCommand(); command1->setName("ctg1");
    catalog.add(command);
    catalog.add(command1);

    catalog.deleteCommand(command);
    QCOMPARE(catalog.commands().size(), 1);
    QVERIFY(catalog.find("ctg") == nullptr);
}

//------------------------------------------------------------------------------
void CommandCatalogTest::shouldDeleteCommandByName()
{
    CommandCatalog catalog;
    MockCommand *command = new MockCommand(); command->setName("ctg");
    MockCommand *command1 = new MockCommand(); command1->setName("ctg1");
    catalog.add(command);
    catalog.add(command1);

    catalog.deleteCommand("ctg");
    QCOMPARE(catalog.commands().size(), 1);
    QVERIFY(catalog.find("ctg") == nullptr);
}

//------------------------------------------------------------------------------
