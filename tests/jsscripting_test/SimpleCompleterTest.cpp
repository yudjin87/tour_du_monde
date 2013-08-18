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

#include "SimpleCompleterTest.h"

#include <components/jsscripting/SimpleCompleter.h>
#include <components/jsscripting/ServiceLocatorWrapper.h>
#include <carousel/utils/ServiceLocator.h>

#include <QtScript/QScriptEngine>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
SimpleCompleterTest::SimpleCompleterTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void SimpleCompleterTest::completeGlobals_shouldReturnAllObjects()
{
    SimpleCompleter completer; QScriptEngine eng;
    completer.resetEngine(&eng);

    QStringList globals = completer.completeGlobals();

    QCOMPARE(globals.size(), 34);

    QVERIFY(globals.contains("Math"));
    QVERIFY(globals.contains("NaN"));
    QVERIFY(globals.contains("undefined"));
    QVERIFY(globals.contains("Infinity"));
    QVERIFY(globals.contains("JSON"));
    QVERIFY(globals.contains("Object"));
    QVERIFY(globals.contains("Function"));
    QVERIFY(globals.contains("Array"));
    QVERIFY(globals.contains("Boolean"));
    QVERIFY(globals.contains("String"));
    QVERIFY(globals.contains("Number"));
    QVERIFY(globals.contains("Date"));
    QVERIFY(globals.contains("RegExp"));
    QVERIFY(globals.contains("Error"));
    QVERIFY(globals.contains("EvalError"));
    QVERIFY(globals.contains("RangeError"));
    QVERIFY(globals.contains("ReferenceError"));
    QVERIFY(globals.contains("SyntaxError"));
    QVERIFY(globals.contains("TypeError"));
    QVERIFY(globals.contains("URIError"));
    QVERIFY(globals.contains("eval"));
    QVERIFY(globals.contains("parseInt"));
    QVERIFY(globals.contains("parseFloat"));
    QVERIFY(globals.contains("isNaN"));
    QVERIFY(globals.contains("isFinite"));
    QVERIFY(globals.contains("escape"));
    QVERIFY(globals.contains("unescape"));
    QVERIFY(globals.contains("decodeURI"));
    QVERIFY(globals.contains("decodeURIComponent"));
    QVERIFY(globals.contains("encodeURI"));
    QVERIFY(globals.contains("encodeURIComponent"));
    QVERIFY(globals.contains("print"));
    QVERIFY(globals.contains("gc"));
    QVERIFY(globals.contains("version"));
}

//------------------------------------------------------------------------------
void SimpleCompleterTest::completeGlobals_shouldReturnNewObjectObject()
{
    SimpleCompleter completer; QScriptEngine eng;
    QScriptValue value = eng.newQObject(this);
    eng.globalObject().setProperty("serviceLocator", value);

    completer.resetEngine(&eng);

    QStringList globals = completer.completeGlobals();

    QVERIFY(globals.contains("serviceLocator"));
}

//------------------------------------------------------------------------------
