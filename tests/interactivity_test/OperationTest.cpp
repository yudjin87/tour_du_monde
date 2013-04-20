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

#include "OperationTest.h"

#include "fakes/MockOperation.h"

#include <QtGui/QWidget>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
OperationTest::OperationTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void OperationTest::shouldCallExecuteWhenActionTriggered()
{
    MockOperation operation;
    operation.activate(QAction::Trigger);

    QVERIFY(operation.executeCalled);
}

//------------------------------------------------------------------------------
void OperationTest::shouldNotCallStopExecuteIfIsNotCheckable()
{
    MockOperation operation;
    operation.setCheckable(false);

    // checked
    operation.activate(QAction::Trigger);
    QVERIFY(operation.executeCalled);

    operation.executeCalled = false;

    // unchecked
    operation.activate(QAction::Trigger);
    QVERIFY(!operation.stopExecuteCalled);
    QVERIFY(operation.executeCalled);
}

//------------------------------------------------------------------------------
void OperationTest::shouldCallExecuteWhenActionTriggeredIfCheckable()
{
    MockOperation operation;
    operation.setCheckable(true);
    operation.activate(QAction::Trigger);

    QVERIFY(operation.executeCalled);
}

//------------------------------------------------------------------------------
void OperationTest::shouldCallStopExecuteIfCheckableAndActivatedSecondTime()
{
    MockOperation operation;
    operation.setCheckable(true);

    // checked
    operation.activate(QAction::Trigger);
    operation.executeCalled = false; //reset

    // unchecked
    operation.activate(QAction::Trigger);

    QVERIFY(operation.stopExecuteCalled);
    QVERIFY(!operation.executeCalled);
}

//------------------------------------------------------------------------------
