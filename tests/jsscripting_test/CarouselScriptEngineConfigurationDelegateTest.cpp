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

#include "CarouselScriptEngineConfigurationDelegateTest.h"
#include "fakes/MockScriptExtensionComponent.h"

#include <carousel/utils/ServiceLocator.h>
#include <components/jsscripting/CarouselScriptEngineConfigurationDelegate.h>

#include <QtScript/QScriptEngine>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
CarouselScriptEngineConfigurationDelegateTest::CarouselScriptEngineConfigurationDelegateTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegateTest::configureComponent_shouldConfigureComponentIfItHasScriptExtension()
{
    ServiceLocator locator; QScriptEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);
    MockScriptExtensionComponent component;

    delegate.configureFromComponent(&component, &engine);

    QVERIFY(component.m_extension->m_configureCalled);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegateTest::configureComponent_shouldNotThrowIfComponentHasNoScriptExtension()
{
    ServiceLocator locator; QScriptEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);
    MockNoScriptExtensionComponent component;

    delegate.configureFromComponent(&component, &engine);

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegateTest::configureDefaults_shouldAddServiceLocatorObjectToEngine()
{
    ServiceLocator locator; QScriptEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);
    QString buff;

    delegate.configureDefaults(&engine, &buff);

    QVERIFY(engine.globalObject().property("serviceLocator").isValid());
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegateTest::configureDefaults_shouldAddPrintFunctionToEngine()
{
    ServiceLocator locator; QScriptEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);

    QString buff;
    delegate.configureDefaults(&engine, &buff);
    engine.evaluate("print(\"Hello, carousel!\")");

    QCOMPARE(buff, QString("Hello, carousel!\n"));
}

//------------------------------------------------------------------------------
