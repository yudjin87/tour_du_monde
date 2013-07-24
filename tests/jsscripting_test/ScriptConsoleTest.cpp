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

//------------------------------------------------------------------------------
const QByteArray simpleScript(
        "var obj = serviceLocator.findService(\"ScriptEngineTest\");"
        "var name = obj.objectName");

//------------------------------------------------------------------------------
ScriptConsoleTest::ScriptConsoleTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void ScriptConsoleTest::evaluateLine_shouldReturnTrueForCorrectScript()
{
    QScriptEngine engine; ScriptConsole console(&engine);

    QString error;
    QVERIFY(console.evaluateLine(simpleScript, &error));
    QVERIFY(error.isEmpty());
}

//------------------------------------------------------------------------------
void ScriptConsoleTest::evaluateLine_shouldReturnFalseForIncorrectScript()
{
    QScriptEngine engine; ScriptConsole console(&engine);

    QString error;
    QVERIFY(!console.evaluateLine(wrongScript, &error));
    QVERIFY(!error.isEmpty());
}

//------------------------------------------------------------------------------
void ScriptConsoleTest::evaluateLine_shouldPopulateHistory()
{
    QScriptEngine engine; ScriptConsole console(&engine);
    QVERIFY(console.history().isEmpty());

    console.evaluateLine("oldest");
    console.evaluateLine("older");
    console.evaluateLine("last (newest)");

    QCOMPARE(console.history().size(), 3);
}

//------------------------------------------------------------------------------
void ScriptConsoleTest::historyPrev_shouldReturnCorrectCommand()
{
    QScriptEngine engine; ScriptConsole console(&engine);
    console.evaluateLine("oldest");
    console.evaluateLine("older");
    console.evaluateLine("last (newest)");

    QStringList history = console.history();

    QCOMPARE(console.historyPrev(), history[2]); // "last (newest)"    ^
    QCOMPARE(console.historyPrev(), history[1]); // "older"            |
    QCOMPARE(console.historyPrev(), history[0]); // "oldest"           |
    QCOMPARE(console.historyPrev(), history[0]); // "oldest" anyway    |
    QCOMPARE(console.historyPrev(), history[0]); // "oldest" anyway    |
}

//------------------------------------------------------------------------------
void ScriptConsoleTest::historyNext_shouldReturnCorrectCommand()
{
    QScriptEngine engine; ScriptConsole console(&engine);
    console.evaluateLine("oldest");
    console.evaluateLine("older");
    console.evaluateLine("last (newest)");

    console.historyPrev();
    console.historyPrev();
    console.historyPrev();

    QStringList history = console.history();
    QCOMPARE(console.historyNext(), history[0]); // "oldest"          |
    QCOMPARE(console.historyNext(), history[1]); // "older"           |
    QCOMPARE(console.historyNext(), history[2]); // "last (newest)"   |
    QCOMPARE(console.historyNext(), history[2]); // "last"   anyway   |
    QCOMPARE(console.historyNext(), history[2]); // "last"   anyway   v
}

//------------------------------------------------------------------------------
const QByteArray ScriptConsoleTest::simpleScript("var a = 1 + 1");
const QByteArray ScriptConsoleTest::wrongScript("var a = b + 1");

//------------------------------------------------------------------------------
