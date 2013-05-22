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

#include "OperationCatalogTest.h"
#include "fakes/MockOperation.h"

#include <interactivity/OperationCatalog.h>
#include <utils/ServiceLocator.h>

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
OperationCatalogTest::OperationCatalogTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void OperationCatalogTest::shouldAddOperationToList()
{
    OperationCatalog catalog;
    MockOperation *operation = new MockOperation();
    catalog.add(operation);

    QVERIFY(operation == catalog.operations()[0]);
}

//------------------------------------------------------------------------------
void OperationCatalogTest::shouldEmitWhenOperationAdded()
{
    OperationCatalog catalog;
    MockOperation *operation = new MockOperation();
    QSignalSpy spy(&catalog, SIGNAL(operationAdded(Operation *)));

    catalog.add(operation);
    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void OperationCatalogTest::shouldInitializeAddedOperation()
{
    OperationCatalog catalog;
    MockOperation *operation = new MockOperation();
    catalog.add(operation);

    QVERIFY(operation->initializeCalled);
}

//------------------------------------------------------------------------------
void OperationCatalogTest::shouldInitializeAddedOperationWithStartupData()
{
    OperationCatalog catalog;
    ServiceLocator serviceLocator;
    catalog.setStartupData(&serviceLocator);

    MockOperation *operation = new MockOperation();
    catalog.add(operation);

    QCOMPARE(&serviceLocator, operation->m_serviceLocator);
}

//------------------------------------------------------------------------------
void OperationCatalogTest::shouldReturnTheSameOperation()
{
    OperationCatalog catalog;
    MockOperation *operation = new MockOperation();

    QVERIFY(operation == catalog.add(operation));
}

//------------------------------------------------------------------------------
void OperationCatalogTest::shouldReturnOperationsByCategory()
{
    OperationCatalog catalog;
    MockOperation *operation = new MockOperation(); operation->setCategory("ctg");
    MockOperation *operation1 = new MockOperation(); operation1->setCategory("ctg1");
    MockOperation *operation2 = new MockOperation(); operation2->setCategory("ctg2");
    catalog.add(operation);
    catalog.add(operation1);
    catalog.add(operation2);

    QList<Operation *> operations = catalog.operations("ctg1");

    QCOMPARE(operations.size(), 1);
    QVERIFY(operation1 == operations[0]);
}

//------------------------------------------------------------------------------
void OperationCatalogTest::shouldFindOperationByName()
{
    OperationCatalog catalog;
    MockOperation *operation = new MockOperation(); operation->setName("ctg");
    MockOperation *operation1 = new MockOperation(); operation1->setName("ctg1");
    MockOperation *operation2 = new MockOperation(); operation2->setName("ctg2");
    catalog.add(operation);
    catalog.add(operation1);
    catalog.add(operation2);

    QVERIFY(operation == catalog.find("ctg"));
}

//------------------------------------------------------------------------------
void OperationCatalogTest::shouldDeleteOperation()
{
    OperationCatalog catalog;
    MockOperation *operation = new MockOperation(); operation->setName("ctg");
    MockOperation *operation1 = new MockOperation(); operation1->setName("ctg1");
    catalog.add(operation);
    catalog.add(operation1);

    catalog.deleteOperation(operation);
    QCOMPARE(catalog.operations().size(), 1);
    QVERIFY(catalog.find("ctg") == nullptr);
}

//------------------------------------------------------------------------------
void OperationCatalogTest::shouldDeleteOperationByName()
{
    OperationCatalog catalog;
    MockOperation *operation = new MockOperation(); operation->setName("ctg");
    MockOperation *operation1 = new MockOperation(); operation1->setName("ctg1");
    catalog.add(operation);
    catalog.add(operation1);

    catalog.deleteOperation("ctg");
    QCOMPARE(catalog.operations().size(), 1);
    QVERIFY(catalog.find("ctg") == nullptr);
}

//------------------------------------------------------------------------------
