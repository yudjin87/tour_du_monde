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

#include "CarouselPersistenceDelegateTest.h"
#include "fakes/JustComponent.h"
#include "fakes/MockPersistExtension.h"
#include "fakes/PersistComponent.h"

#include <carousel/utils/ServiceLocator.h>
#include <components/persistence/CarouselPersistenceDelegate.h>

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
CarouselPersistenceDelegateTest::CarouselPersistenceDelegateTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void CarouselPersistenceDelegateTest::save_shouldCallSaveForPersistComponents()
{
    ServiceLocator locator; QByteArray stream;
    QList<IComponent *> components;
    PersistComponent comp1; components.append(&comp1);
    JustComponent comp2; components.append(&comp2);
    PersistComponent comp3; components.append(&comp3);

    CarouselPersistenceDelegate delegate;
    delegate.save(&locator, components, stream);

    QVERIFY(comp1.persistExtension->saveCalled);
    QVERIFY(comp3.persistExtension->saveCalled);
}

//------------------------------------------------------------------------------
void CarouselPersistenceDelegateTest::save_shouldCreateJsonDocument()
{
    ServiceLocator locator; QByteArray stream;
    QList<IComponent *> components;
    PersistComponent comp1; components.append(&comp1);
    JustComponent comp2; components.append(&comp2);
    PersistComponent comp3; components.append(&comp3);

    CarouselPersistenceDelegate delegate;
    delegate.save(&locator, components, stream);

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(stream, &error);
    QVERIFY(!doc.isNull());
    QVERIFY(error.error == QJsonParseError::NoError);
}

//------------------------------------------------------------------------------
void CarouselPersistenceDelegateTest::save_shouldAddObjectsToDocument()
{
    ServiceLocator locator; QByteArray stream;
    QList<IComponent *> components;
    PersistComponent comp1("PersistComponent1"); components.append(&comp1);
    JustComponent comp2; components.append(&comp2);
    PersistComponent comp3("PersistComponent3"); components.append(&comp3);

    CarouselPersistenceDelegate delegate;
    delegate.save(&locator, components, stream);

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(stream, &error);
    QJsonObject root = doc.object();

    QCOMPARE(root.value("projectInfo").toString(), QCoreApplication::applicationName());

    QJsonArray componentsJson = root.value("components").toArray();
    QCOMPARE(componentsJson.size(), 2);

    QJsonObject comp1Json = componentsJson.at(0).toObject();
    QCOMPARE(comp1Json.value("name").toString(), QString("PersistComponent1"));

    QJsonObject comp1JsonData = comp1Json.value("data").toObject();
    QCOMPARE(comp1JsonData.value("mockField").toString(), QString("mockValue"));
}

//------------------------------------------------------------------------------
void CarouselPersistenceDelegateTest::load_shouldCallLoadForSpecificComponents()
{
    ServiceLocator locator; QByteArray stream;
    QList<IComponent *> components;
    PersistComponent comp1("PersistComponent1"); components.append(&comp1);
    JustComponent comp2; components.append(&comp2);
    PersistComponent comp3("PersistComponent3"); components.append(&comp3);

    CarouselPersistenceDelegate delegate;
    delegate.save(&locator, components, stream);

    PersistComponent comp4("PersistComponent4"); components.append(&comp4);
    delegate.load(&locator, components, stream);

    QVERIFY(comp1.persistExtension->loadCalled);
    QVERIFY(comp3.persistExtension->loadCalled);
    QVERIFY(!comp4.persistExtension->loadCalled);
}

//------------------------------------------------------------------------------
