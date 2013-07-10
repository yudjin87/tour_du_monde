#include "InputDispatcherTest.h"
#include "fakes/MockTool.h"

#include <components/interactivity/InputDispatcher.h>

#include <QtWidgets/QWidget>
#include <QtTest/QtTest>
#include <QtTest/qtestkeyboard.h>

#include <functional>

//------------------------------------------------------------------------------
InputDispatcherTest::InputDispatcherTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldStoreSetWidget()
{
    QWidget widget;
    InputDispatcher interceptor;
    interceptor.setSender(&widget);

    QCOMPARE(interceptor.sender(), &widget);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotThrowIfWidgetNullWhileDeactivate()
{
    InputDispatcher interceptor;
    interceptor.deactivate();

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotThrowIfWidgetNullWhileActivate()
{
    InputDispatcher interceptor;
    interceptor.activate();

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldStoreReceivedTool()
{
    InputDispatcher interceptor;
    MockTool tool;
    interceptor.setReceiver(&tool);

    QCOMPARE(interceptor.receiver(), &tool);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldReturnNullWidgetByDefault()
{
    InputDispatcher interceptor;

    QVERIFY(interceptor.sender() == nullptr);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldReturnNullReceivedToolByDefault()
{
    InputDispatcher interceptor;

    QVERIFY(interceptor.receiver() == nullptr);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldBeDeactivedByDefault()
{
    InputDispatcher interceptor;

    QCOMPARE(interceptor.isActive(), false);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldBeActiveAfterActivating()
{
    InputDispatcher interceptor;
    QCOMPARE(interceptor.isActive(), false);

    interceptor.activate();

    QCOMPARE(interceptor.isActive(), true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldBeWorkingAfterActivatingWithSenderAndReceiver()
{
    QWidget widget;
    InputDispatcher interceptor;
    interceptor.setSender(&widget);
    MockTool tool;
    interceptor.setReceiver(&tool);

    QCOMPARE(interceptor.isWorking(), false);

    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldBeWorkingAfterSettingSenderIfWasActivatedWithNullOne()
{
    QWidget widget; MockTool tool;

    InputDispatcher interceptor;
    interceptor.setReceiver(&tool);
    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), false);

    interceptor.setSender(&widget);

    QCOMPARE(interceptor.isWorking(), true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldBeWorkingAfterSettingReceiverIfWasActivatedWithNullOne()
{
    QWidget widget; MockTool tool;

    InputDispatcher interceptor;
    interceptor.setSender(&widget);
    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), false);

    interceptor.setReceiver(&tool);

    QCOMPARE(interceptor.isWorking(), true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeWorkingAfterActivatingWithoutSettingTheSenderAndReceiver()
{
    QWidget widget;
    InputDispatcher interceptor;

    QCOMPARE(interceptor.isActive(), false);

    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), false);

    interceptor.setSender(&widget);

    QCOMPARE(interceptor.isWorking(), false);

    interceptor.setSender(nullptr);

    MockTool tool;
    interceptor.setReceiver(&tool);

    QCOMPARE(interceptor.isWorking(), false);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeActiveAfterActivatingAndDeactivating()
{
    InputDispatcher interceptor;

    interceptor.activate();

    QCOMPARE(interceptor.isActive(), true);

    interceptor.deactivate();

    QCOMPARE(interceptor.isActive(), false);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeWorkingIfNotActive()
{
    QWidget widget; MockTool tool;
    InputDispatcher interceptor;
    interceptor.setReceiver(&tool);
    interceptor.setSender(&widget);
    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), true);

    interceptor.deactivate();

    QCOMPARE(interceptor.isWorking(), false);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeInvokeKeyboardHandlerAfterSettingNullSender()
{
    QWidget widget;
    InputDispatcher interceptor;
    interceptor.setSender(&widget);
    MockTool tool;
    interceptor.setReceiver(&tool);
    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), true);

    interceptor.setSender(nullptr);
    QTest::keyRelease(&widget, 'E');

    QCOMPARE(interceptor.isWorking(), false);
    QVERIFY(!tool.keyUpCalled);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeInvokeKeyboardHandlerAfterSettingNullReceiver()
{
    QWidget widget;
    InputDispatcher interceptor;
    interceptor.setSender(&widget);
    MockTool tool;
    interceptor.setReceiver(&tool);
    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), true);

    interceptor.setReceiver(nullptr);
    QTest::keyRelease(&widget, 'E');

    QCOMPARE(interceptor.isWorking(), false);
    QVERIFY(!tool.keyUpCalled);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeWorkingAfterSenderDeletion()
{
    MockTool tool;

    InputDispatcher interceptor;
    interceptor.activate();
    interceptor.setReceiver(&tool);

    {
        QWidget widget;
        interceptor.setSender(&widget);
        QCOMPARE(interceptor.isWorking(), true);
    }

    QCOMPARE(interceptor.isWorking(), false);
    QVERIFY(interceptor.sender() == nullptr);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeWorkingAfterReceiverDeletion()
{
    InputDispatcher interceptor;
    interceptor.activate();
    QWidget widget;
    interceptor.setSender(&widget);

    {
        MockTool tool;
        interceptor.setReceiver(&tool);
        QCOMPARE(interceptor.isWorking(), true);
    }

    QCOMPARE(interceptor.isWorking(), false);
    QVERIFY(interceptor.receiver() == nullptr);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldCallReceiverIfWorking()
{
    QWidget widget;
    InputDispatcher interceptor;
    interceptor.setSender(&widget);
    MockTool tool;
    interceptor.setReceiver(&tool);
    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), true);

    QTest::keyRelease(&widget, 'E');

    QVERIFY(tool.keyUpCalled);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotInvokeKeyboardHandlerIfNotWorking()
{
    QWidget widget;
    InputDispatcher interceptor;
    interceptor.setSender(&widget);
    MockTool tool;
    interceptor.setReceiver(&tool);

    interceptor.activate();
    interceptor.deactivate();

    QCOMPARE(interceptor.isWorking(), false);

    QTest::keyRelease(&widget, 'E');

    QVERIFY(!tool.keyUpCalled);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldInvokeKeyboardHandlerAfterReactivating()
{
    QWidget widget;
    InputDispatcher interceptor;
    interceptor.setSender(&widget);
    interceptor.activate();

    MockTool tool;
    interceptor.setReceiver(&tool);

    interceptor.deactivate();
    interceptor.activate();

    QTest::keyRelease(&widget, 'E');

    QVERIFY(tool.keyUpCalled);
}

//------------------------------------------------------------------------------
