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

#include "ObservableListTest.h"

#include "fakes/MockObservableList.h"
#include <carousel/utils/ObservableList.h>

#include <QtCore/QtAlgorithms>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
ObservableListTest::ObservableListTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void ObservableListTest::shouldAddItemsCorrectly()
{
    MockObservableList list;
    QCOMPARE(list.size(), 0);
    QVERIFY(list.empty());
    QVERIFY(list.isEmpty());

    list.append(new QObject(this));
    QCOMPARE(list.size(), 1);

    QList<QObject *> objects;
    objects.append(new QObject(this));
    objects.append(new QObject(this));

    list.append(objects);
    QCOMPARE(list.size(), 3);

    list.push_front(new QObject(this));
    QCOMPARE(list.size(), 4);

    list.push_back(new QObject(this));
    QCOMPARE(list.size(), 5);

    QVERIFY(!list.empty());
    QVERIFY(!list.isEmpty());
}

//------------------------------------------------------------------------------
void ObservableListTest::shouldRemoveItemsCorrectly()
{
    MockObservableList list;
    list.push_back(new QObject(this));
    list.push_back(new QObject(this));
    list.push_back(new QObject(this));
    list.push_back(new QObject(this));
    QObject *obj = new QObject(this);
    list.push_back(obj);

    list.removeAt(0);
    QCOMPARE(list.size(), 4);

    list.removeOne(obj);
    QCOMPARE(list.size(), 3);

    MockObservableList list2;
    list2.push_back(obj);
    list2.push_back(new QObject(this));
    list2.push_back(obj);
    QCOMPARE(list2.size(), 3);

    list2.removeAll(obj);
    QCOMPARE(list2.size(), 1);

    list.clear();
    QVERIFY(list.empty());
}

//------------------------------------------------------------------------------
void ObservableListTest::shouldGetCorrectElemets()
{
    MockObservableList list;
    QObject *obj  = new QObject(this); list.push_back(obj);
    QObject *obj1 = new QObject(this); list.push_back(obj1);
    QObject *obj2 = new QObject(this); list.push_back(obj2);

    QCOMPARE(list.at(1), obj1);
    QCOMPARE(list[1], obj1);

    QCOMPARE(list.first(), obj);
    QCOMPARE(list.last(), obj2);

    QCOMPARE(list.front(), obj);
    QCOMPARE(list.back(), obj2);

    QCOMPARE(*list.begin(), obj);
    QCOMPARE(*list.constBegin(), obj);
    QVERIFY(list.begin() != list.end());
    QVERIFY(list.constBegin() != list.constEnd());

    MockObservableList emptyList;
    QCOMPARE(emptyList.begin(), emptyList.end());
    QCOMPARE(emptyList.constBegin(), emptyList.constEnd());
}

//------------------------------------------------------------------------------
void ObservableListTest::shouldFindElementsCorrectly()
{
    MockObservableList list;
    QObject *obj  = new QObject(this); list.push_back(obj);
    QObject *obj1 = new QObject(this); list.push_back(obj1);
    list.push_back(obj1);
    QObject *obj2 = new QObject(this); list.push_back(obj2);

    QCOMPARE(list.indexOf(obj2), 3);
    QCOMPARE(list.lastIndexOf(obj1), 2);
    QCOMPARE(list.count(obj1), 2);

    QVERIFY(list.contains(obj1));
    QVERIFY(!list.contains(new QObject(this)));
}

//------------------------------------------------------------------------------
void ObservableListTest::shouldNotifyAboutItemsAdding()
{
    {// append
        MockObservableList list;

        QObject *obj1 = new QObject(this);
        list.append(obj1);

        QVERIFY(list.addedCalled);
    }

    {// prepend
        MockObservableList list;

        QObject *obj1 = new QObject(this);
        list.prepend(obj1);

        QVERIFY(list.addedCalled);
    }

    {// push_back
        MockObservableList list;

        QObject *obj1 = new QObject(this);
        list.push_back(obj1);

        QVERIFY(list.addedCalled);
    }

    {// push_front
        MockObservableList list;

        QObject *obj1 = new QObject(this);
        list.push_front(obj1);

        QVERIFY(list.addedCalled);
    }
}

//------------------------------------------------------------------------------
void ObservableListTest::shouldNotifyAboutItemsRemoving()
{
    {// removeOne
        QObject *obj1 = new QObject(this);
        MockObservableList list; list.append(obj1);

        list.removeOne(obj1);

        QVERIFY(list.removedCalled);
    }
    {// removeAt
        QObject *obj1 = new QObject(this);
        MockObservableList list; list.append(obj1);

        list.removeAt(0);

        QVERIFY(list.removedCalled);
    }
    {// removeAll
        QObject *obj1 = new QObject(this);
        MockObservableList list; list.append(obj1);

        list.removeAll(obj1);

        QVERIFY(list.removedCalled);
    }
}

//------------------------------------------------------------------------------
void ObservableListTest::shouldNotifyAboutClearing()
{
    MockObservableList list;
    QObject *obj1 = new QObject(this);
    list.append(obj1); list.append(obj1); list.append(obj1);

    list.clear();

    QVERIFY(list.removedCalled);
}

//------------------------------------------------------------------------------
void ObservableListTest::shouldSortItems()
{
    MockObservableList list;
    list.push_front(new QObject(this)); list.push_front(new QObject(this)); list.push_front(new QObject(this));

    list.sort();

    QVERIFY(list[0] < list[1]);
    QVERIFY(list[1] < list[2]);
}

//------------------------------------------------------------------------------
void ObservableListTest::shouldSortItemsWithCustomPredicate()
{
    MockObservableList list;
    list.push_front(new QObject(this)); list.push_front(new QObject(this)); list.push_front(new QObject(this));

    auto predicate = qLess<QObject *>();
    list.sort(predicate);

    QVERIFY(list[0] < list[1]);
    QVERIFY(list[1] < list[2]);
}

//------------------------------------------------------------------------------


