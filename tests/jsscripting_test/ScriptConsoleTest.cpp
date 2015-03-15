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

#include "ScriptConsoleTest.h"

#include <components/jsscripting/ScriptConsole.h>

#include <QtScript/QScriptEngine>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>

const QByteArray simpleScript(
        "var obj = serviceLocator.locate(\"ScriptEngineTest\");"
        "var name = obj.objectName");

ScriptConsoleTest::ScriptConsoleTest(QObject *parent)
    : QObject(parent)
{
}

void ScriptConsoleTest::evaluateLine_shouldReturnTrueForCorrectScript()
{
    ScriptConsole console;
    QSignalSpy printed(&console, SIGNAL(printed(QString)));
    QSignalSpy error(&console, SIGNAL(error(QString)));

    QVERIFY(console.execCommand(simpleScript));

    QVERIFY(printed.isEmpty());
    QVERIFY(error.isEmpty());
}

void ScriptConsoleTest::evaluateLine_shouldReturnFalseForIncorrectScript()
{
    ScriptConsole console;    
    QSignalSpy printed(&console, SIGNAL(printed(QString)));
    QSignalSpy error(&console, SIGNAL(error(QString)));

    QVERIFY(!console.execCommand(wrongScript));
    QVERIFY(printed.isEmpty());
    QVERIFY(!error.isEmpty());
}

void ScriptConsoleTest::evaluateLine_shouldPopulateHistory()
{
    ScriptConsole console;
    QVERIFY(console.commandHistory().isEmpty());

    console.execCommand("oldest");
    console.execCommand("older");
    console.execCommand("newest");

    QCOMPARE(console.commandHistory().size(), 3);
}

void ScriptConsoleTest::evaluateLine_shouldNotPopulateHistoryWithEmptyLine()
{
    ScriptConsole console;
    QVERIFY(console.commandHistory().isEmpty());

    console.execCommand("oldest");
    console.execCommand("    ");
    console.execCommand("");
    console.execCommand("newest");

    QCOMPARE(console.commandHistory().size(), 2);
}

void ScriptConsoleTest::evaluateLine_shouldResetHistoryHead()
{
    ScriptConsole console;
    console.execCommand("0");
    console.execCommand("1");
    console.execCommand("2");

    console.prevCommand();
    console.prevCommand();
    console.prevCommand();

    console.execCommand("3");

    QStringList commandHistory = console.commandHistory();

    QCOMPARE(console.nextCommand(), QString(""));
    QCOMPARE(console.prevCommand(), commandHistory[3]);
}

void ScriptConsoleTest::historyPrev_shouldReturnCorrectCommand()
{
    ScriptConsole console;
    console.execCommand("oldest");
    console.execCommand("older");
    console.execCommand("newest");

    QStringList commandHistory = console.commandHistory();

    QCOMPARE(console.prevCommand(), commandHistory[2]); // "last (newest)"    ^
    QCOMPARE(console.prevCommand(), commandHistory[1]); // "older"            |
    QCOMPARE(console.prevCommand(), commandHistory[0]); // "oldest"           |
    QCOMPARE(console.prevCommand(), commandHistory[0]); // "oldest" anyway    |
    QCOMPARE(console.prevCommand(), commandHistory[0]); // "oldest" anyway    |
}

void ScriptConsoleTest::historyNext_shouldReturnCorrectCommand()
{
    ScriptConsole console;
    console.execCommand("oldest");
    console.execCommand("older");
    console.execCommand("newest");

    console.prevCommand();
    console.prevCommand();
    console.prevCommand();

    QStringList commandHistory = console.commandHistory();
    QCOMPARE(console.nextCommand(), commandHistory[1]); // "older"           |
    QCOMPARE(console.nextCommand(), commandHistory[2]); // "last (newest)"   |
    QCOMPARE(console.nextCommand(), QString("")); // "last"   anyway   |
    QCOMPARE(console.nextCommand(), QString("")); // "last"   anyway   v
}

void ScriptConsoleTest::historyPrevNext_shouldReturnCorrectCommands()
{
    ScriptConsole console;
    console.execCommand("oldest");
    console.execCommand("middle");
    console.execCommand("newest");

    QStringList commandHistory = console.commandHistory();

    console.prevCommand();                       // "newest"    ^
    console.prevCommand();                       // "middle"    ^
    QCOMPARE(console.prevCommand(), commandHistory[0]); // "oldest"    ^
    QCOMPARE(console.nextCommand(), commandHistory[1]); // "middle"    v
    QCOMPARE(console.nextCommand(), commandHistory[2]); // "newest"    v
    QCOMPARE(console.prevCommand(), commandHistory[1]); // "middle"    ^
    QCOMPARE(console.nextCommand(), commandHistory[2]); // "newest"    v
    QCOMPARE(console.nextCommand(), QString("")); // "newest"    v

    console.nextCommand();
    console.nextCommand();
    console.nextCommand();
    console.nextCommand();
}

const QByteArray ScriptConsoleTest::simpleScript("var a = 1 + 1");
const QByteArray ScriptConsoleTest::wrongScript("var a = b + 1");

