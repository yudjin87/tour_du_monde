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

#include "DialogServiceTest.h"
#include "fakes/MockDialog.h"
#include "fakes/MockDialogService.h"

#include <components/interactivity/DialogService.h>
#include <carousel/utils/ServiceLocator.h>

#include <QtWidgets/QWidget>
#include <QtTest/QTest>

//------------------------------------------------------------------------------
DialogServiceTest::DialogServiceTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void DialogServiceTest::registerDialog_shouldRegisterViewWithViewModel()
{
    QWidget mainWindow; DialogService service(&mainWindow, nullptr);
    QVERIFY(!service.isRegistered<MockDialogModel>());
    service.registerDialog<MockDialog, MockDialogModel>();
    QVERIFY(service.isRegistered<MockDialogModel>());
}

//------------------------------------------------------------------------------
void DialogServiceTest::unregisterDialogForModel_shouldUnregisterViewForModelType()
{
    QWidget mainWindow; DialogService service(&mainWindow, nullptr);

    service.registerDialog<MockDialog, MockDialogModel>();
    QVERIFY(service.isRegistered<MockDialogModel>());

    QVERIFY(service.unregisterDialogForModel<MockDialogModel>());
    QVERIFY(!service.isRegistered<MockDialogModel>());
}

//------------------------------------------------------------------------------
void DialogServiceTest::showDialog_shouldCreateDialog()
{
    MockDialog::wasCreated = false;
    QWidget mainWindow; MockDialogService service(&mainWindow, nullptr);
    service.registerDialog<MockDialog, MockDialogModel>();

    MockDialogModel model;
    service.showDialog(&model);

    QVERIFY(MockDialog::wasCreated);
}

//------------------------------------------------------------------------------
void DialogServiceTest::showDialog_shouldReturnRightResult()
{
    MockDialog::s_result = QDialog::Rejected;
    QWidget mainWindow; MockDialogService service(&mainWindow, nullptr);
    service.registerDialog<MockDialog, MockDialogModel>();

    MockDialogModel model;
    bool result = service.showDialog(&model);

    QCOMPARE(result, false);

    MockDialog::s_result = QDialog::Accepted;
    result = service.showDialog(&model);
    QCOMPARE(result, true);
}

//------------------------------------------------------------------------------
void DialogServiceTest::showDialog_shouldDeleteDialogAfterShowing()
{
    MockDialog::wasDestroyed = false;
    QWidget mainWindow; MockDialogService service(&mainWindow, nullptr);
    service.registerDialog<MockDialog, MockDialogModel>();

    MockDialogModel model;
    service.showDialog(&model);

    QVERIFY(MockDialog::wasDestroyed);
}

//------------------------------------------------------------------------------
void DialogServiceTest::showDialog_shouldReturnFalseIfDialogWasNotRegistered()
{
    MockDialog::s_result = QDialog::Accepted;
    QWidget mainWindow; DialogService service(&mainWindow, nullptr);

    MockDialogModel model;
    bool result = service.showDialog(&model);

    QVERIFY(!service.isRegistered<MockDialogModel>());
    QCOMPARE(result, false);
}

//------------------------------------------------------------------------------
void DialogServiceTest::showDialog_shouldInjectLocatorToTheModel()
{
    MockDialog::s_result = QDialog::Accepted;
    ServiceLocator locator;
    QWidget mainWindow; MockDialogService service(&mainWindow, &locator);
    service.registerDialog<MockDialog, MockDialogModel>();

    MockDialogModel model;
    service.showDialog(&model);

    QCOMPARE(model.injectedLocator, &locator);
}

//------------------------------------------------------------------------------
