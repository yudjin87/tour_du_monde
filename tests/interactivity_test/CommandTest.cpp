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

#include "CommandTest.h"

#include "fakes/MockCommand.h"

#include <QtGui/QWidget>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
CommandTest::CommandTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void CommandTest::shouldCallExecuteWhenActionTriggered()
{
    MockCommand command;
    command.activate(QAction::Trigger);

    QVERIFY(command.executeCalled);
}

//------------------------------------------------------------------------------
void CommandTest::shouldNotCallStopExecuteIfIsNotCheckable()
{
    MockCommand command;
    command.setCheckable(false);

    // checked
    command.activate(QAction::Trigger);
    QVERIFY(command.executeCalled);

    command.executeCalled = false;

    // unchecked
    command.activate(QAction::Trigger);
    QVERIFY(!command.stopExecuteCalled);
    QVERIFY(command.executeCalled);
}

//------------------------------------------------------------------------------
void CommandTest::shouldCallExecuteWhenActionTriggeredIfCheckable()
{
    MockCommand command;
    command.setCheckable(true);
    command.activate(QAction::Trigger);

    QVERIFY(command.executeCalled);
}

//------------------------------------------------------------------------------
void CommandTest::shouldCallStopExecuteIfCheckableAndActivatedSecondTime()
{
    MockCommand command;
    command.setCheckable(true);

    // checked
    command.activate(QAction::Trigger);
    command.executeCalled = false; //reset

    // unchecked
    command.activate(QAction::Trigger);

    QVERIFY(command.stopExecuteCalled);
    QVERIFY(!command.executeCalled);
}

//------------------------------------------------------------------------------
