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

#include "ScriptCollectionTest.h"

#include "fakes/FakeScriptCollection.h"
#include "fakes/FakeScriptUnit.h"
#include "fakes/FakeScriptEngineFactory.h"

#include <components/jsscripting/ScriptCollection.h>

#include <QtCore/QCoreApplication>
#include <QtGui/QTextDocument>
#include <QtTest/QtTest>

ScriptCollectionTest::ScriptCollectionTest(QObject *parent)
    : QObject(parent)
    , m_testScriptPath(QCoreApplication::applicationDirPath() + "/scripts/TestScript.js")
{
}

void ScriptCollectionTest::createFromFile_shouldAddScript()
{
    ScriptCollection manager(new FakeScriptEngineFactory(this));
    QVERIFY(manager.scripts().empty());
    manager.createFromFile(m_testScriptPath);

    QCOMPARE(manager.scripts().size(), 1);
}

void ScriptCollectionTest::createFromFile_shouldLoadScript()
{
    ScriptCollection manager(new FakeScriptEngineFactory(this));
    manager.createFromFile(m_testScriptPath);

    QVERIFY(manager.scripts().first()->isLoaded());
}

void ScriptCollectionTest::createFromFile_shouldReturnNullIfLoadingFailed()
{
    FakeScriptCollection manager(new FakeScriptEngineFactory(this));
    FakeScriptUnit *unit = new FakeScriptUnit(); unit->loadFileResult = false;
    manager.unitForCreating = unit;
    QVERIFY(manager.createFromFile(m_testScriptPath) == nullptr);

    QVERIFY(manager.scripts().empty());
}

void ScriptCollectionTest::createFromFile_shouldReturnExistedScript()
{
    ScriptCollection manager(new FakeScriptEngineFactory(this));
    IScriptUnit *script = manager.createFromFile(m_testScriptPath);
    IScriptUnit *sameScript = manager.createFromFile(m_testScriptPath);

    QCOMPARE(script, sameScript);
}

void ScriptCollectionTest::createFromDirectory_shouldAddAllScriptsFromDirectory()
{
    ScriptCollection manager(new FakeScriptEngineFactory(this));
    IScriptCollection::Scripts scripts = manager.createFromDirectory("scripts");
    QCOMPARE(scripts.size(), 2);
    QCOMPARE(manager.scripts().size(), 2);
}

void ScriptCollectionTest::create_shouldAddScript()
{
    ScriptCollection manager(new FakeScriptEngineFactory(this));
    QVERIFY(manager.scripts().empty());
    manager.create();

    QCOMPARE(manager.scripts().size(), 1);
}

void ScriptCollectionTest::remove_shouldRemove()
{
    ScriptCollection manager(new FakeScriptEngineFactory(this));
    IScriptCollection::Scripts scripts = manager.createFromDirectory("scripts");

    manager.remove(scripts.first());

    QCOMPARE(manager.scripts().size(), 1);
}

void ScriptCollectionTest::scriptByFileName_shouldReturnScript()
{
    ScriptCollection manager(new FakeScriptEngineFactory(this));
    IScriptUnit *script = manager.createFromFile(m_testScriptPath);
    IScriptUnit *sameScript = manager.scriptByFileName("scripts/TestScript.js");

    QCOMPARE(script, sameScript);
}

