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
    InputDispatcher dispatcher;
    dispatcher.setSender(&widget);

    QCOMPARE(dispatcher.sender(), &widget);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotThrowIfWidgetNullWhileDeactivate()
{
    InputDispatcher dispatcher;
    dispatcher.deactivate();

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotThrowIfWidgetNullWhileActivate()
{
    InputDispatcher dispatcher;
    dispatcher.activate();

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldStoreReceivedTool()
{
    InputDispatcher dispatcher;
    MockTool tool;
    dispatcher.setReceiver(&tool);

    QCOMPARE(dispatcher.receiver(), &tool);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldReturnNullWidgetByDefault()
{
    InputDispatcher dispatcher;

    QVERIFY(dispatcher.sender() == nullptr);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldReturnNullReceivedToolByDefault()
{
    InputDispatcher dispatcher;

    QVERIFY(dispatcher.receiver() == nullptr);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldBeDeactivedByDefault()
{
    InputDispatcher dispatcher;

    QCOMPARE(dispatcher.isActive(), false);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldBeActiveAfterActivating()
{
    InputDispatcher dispatcher;
    QCOMPARE(dispatcher.isActive(), false);

    dispatcher.activate();

    QCOMPARE(dispatcher.isActive(), true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldBeWorkingAfterActivatingWithSenderAndReceiver()
{
    QWidget widget;
    InputDispatcher dispatcher;
    dispatcher.setSender(&widget);
    MockTool tool;
    dispatcher.setReceiver(&tool);

    QCOMPARE(dispatcher.isWorking(), false);

    dispatcher.activate();

    QCOMPARE(dispatcher.isWorking(), true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldBeWorkingAfterSettingSenderIfWasActivatedWithNullOne()
{
    QWidget widget; MockTool tool;

    InputDispatcher dispatcher;
    dispatcher.setReceiver(&tool);
    dispatcher.activate();

    QCOMPARE(dispatcher.isWorking(), false);

    dispatcher.setSender(&widget);

    QCOMPARE(dispatcher.isWorking(), true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldBeWorkingAfterSettingReceiverIfWasActivatedWithNullOne()
{
    QWidget widget; MockTool tool;

    InputDispatcher dispatcher;
    dispatcher.setSender(&widget);
    dispatcher.activate();

    QCOMPARE(dispatcher.isWorking(), false);

    dispatcher.setReceiver(&tool);

    QCOMPARE(dispatcher.isWorking(), true);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeWorkingAfterActivatingWithoutSettingTheSenderAndReceiver()
{
    QWidget widget;
    InputDispatcher dispatcher;

    QCOMPARE(dispatcher.isActive(), false);

    dispatcher.activate();

    QCOMPARE(dispatcher.isWorking(), false);

    dispatcher.setSender(&widget);

    QCOMPARE(dispatcher.isWorking(), false);

    dispatcher.setSender(nullptr);

    MockTool tool;
    dispatcher.setReceiver(&tool);

    QCOMPARE(dispatcher.isWorking(), false);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeActiveAfterActivatingAndDeactivating()
{
    InputDispatcher dispatcher;

    dispatcher.activate();

    QCOMPARE(dispatcher.isActive(), true);

    dispatcher.deactivate();

    QCOMPARE(dispatcher.isActive(), false);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeWorkingIfNotActive()
{
    QWidget widget; MockTool tool;
    InputDispatcher dispatcher;
    dispatcher.setReceiver(&tool);
    dispatcher.setSender(&widget);
    dispatcher.activate();

    QCOMPARE(dispatcher.isWorking(), true);

    dispatcher.deactivate();

    QCOMPARE(dispatcher.isWorking(), false);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeInvokeKeyboardHandlerAfterSettingNullSender()
{
    QWidget widget;
    InputDispatcher dispatcher;
    dispatcher.setSender(&widget);
    MockTool tool;
    dispatcher.setReceiver(&tool);
    dispatcher.activate();

    QCOMPARE(dispatcher.isWorking(), true);

    dispatcher.setSender(nullptr);
    QTest::keyRelease(&widget, 'E');

    QCOMPARE(dispatcher.isWorking(), false);
    QVERIFY(!tool.keyUpCalled);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeInvokeKeyboardHandlerAfterSettingNullReceiver()
{
    QWidget widget;
    InputDispatcher dispatcher;
    dispatcher.setSender(&widget);
    MockTool tool;
    dispatcher.setReceiver(&tool);
    dispatcher.activate();

    QCOMPARE(dispatcher.isWorking(), true);

    dispatcher.setReceiver(nullptr);
    QTest::keyRelease(&widget, 'E');

    QCOMPARE(dispatcher.isWorking(), false);
    QVERIFY(!tool.keyUpCalled);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeWorkingAfterSenderDeletion()
{
    MockTool tool;

    InputDispatcher dispatcher;
    dispatcher.activate();
    dispatcher.setReceiver(&tool);

    {
        QWidget widget;
        dispatcher.setSender(&widget);
        QCOMPARE(dispatcher.isWorking(), true);
    }

    QCOMPARE(dispatcher.isWorking(), false);
    QVERIFY(dispatcher.sender() == nullptr);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotBeWorkingAfterReceiverDeletion()
{
    InputDispatcher dispatcher;
    dispatcher.activate();
    QWidget widget;
    dispatcher.setSender(&widget);

    {
        MockTool tool;
        dispatcher.setReceiver(&tool);
        QCOMPARE(dispatcher.isWorking(), true);
    }

    QCOMPARE(dispatcher.isWorking(), false);
    QVERIFY(dispatcher.receiver() == nullptr);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldCallReceiverIfWorking()
{
    QWidget widget;
    InputDispatcher dispatcher;
    dispatcher.setSender(&widget);
    MockTool tool;
    dispatcher.setReceiver(&tool);
    dispatcher.activate();

    QCOMPARE(dispatcher.isWorking(), true);

    QTest::keyRelease(&widget, 'E');

    QVERIFY(tool.keyUpCalled);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldNotInvokeKeyboardHandlerIfNotWorking()
{
    QWidget widget;
    InputDispatcher dispatcher;
    dispatcher.setSender(&widget);
    MockTool tool;
    dispatcher.setReceiver(&tool);

    dispatcher.activate();
    dispatcher.deactivate();

    QCOMPARE(dispatcher.isWorking(), false);

    QTest::keyRelease(&widget, 'E');

    QVERIFY(!tool.keyUpCalled);
}

//------------------------------------------------------------------------------
void InputDispatcherTest::shouldInvokeKeyboardHandlerAfterReactivating()
{
    QWidget widget;
    InputDispatcher dispatcher;
    dispatcher.setSender(&widget);
    dispatcher.activate();

    MockTool tool;
    dispatcher.setReceiver(&tool);

    dispatcher.deactivate();
    dispatcher.activate();

    QTest::keyRelease(&widget, 'E');

    QVERIFY(tool.keyUpCalled);
}

//------------------------------------------------------------------------------
