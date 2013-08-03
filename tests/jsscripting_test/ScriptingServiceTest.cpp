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

#include "ScriptingServiceTest.h"

#include <components/jsscripting/ServiceLocatorWrapper.h>
#include <components/jsscripting/ScriptingService.h>
#include <components/jsscripting/IScriptConsole.h>
#include <components/interactivity/Catalogs.h>
#include <carousel/utils/ServiceLocator.h>

#include <QtScript/QScriptEngine>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
ScriptingServiceTest::ScriptingServiceTest(QObject *parent)
    : QObject(parent)
{
    setObjectName("ScriptingServiceTest");
}

//------------------------------------------------------------------------------
void ScriptingServiceTest::setLocatorWrapper_shouldSetupNull()
{
    ServiceLocator locator; ScriptingService service(&locator);
    QScriptEngine *engine = service.createEngine(nullptr, this);

    QScriptValue defaultLocator = engine->globalObject().property("serviceLocator");
    QVERIFY(!defaultLocator.isNull());

    service.setLocatorWrapper(nullptr);
    engine = service.createEngine(nullptr, this);
    QScriptValue nullLocator = engine->globalObject().property("serviceLocator");
    QVERIFY(nullLocator.isNull());
}

//------------------------------------------------------------------------------
void ScriptingServiceTest::setLocatorWrapper_shouldResetConsoleEngine()
{
    ServiceLocator locator; ScriptingService service(&locator);
    QScriptEngine *engine = service.console()->engine();

    QScriptValue defaultLocator = engine->globalObject().property("serviceLocator");
    QVERIFY(!defaultLocator.isNull());

    ServiceLocatorWrapper *wrapper = new ServiceLocatorWrapper(&locator);
    wrapper->setObjectName("NewWrapper");
    service.setLocatorWrapper(wrapper);

    QObject *newWrapper = engine->globalObject().property("serviceLocator").toQObject();
    QVERIFY(newWrapper->objectName() == "NewWrapper");
}

//------------------------------------------------------------------------------
