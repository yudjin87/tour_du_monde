#include "InputInterceptorTest.h"
#include "fakes/MockTool.h"

#include <interactivity/InputInterceptor.h>

#include <QtGui/QWidget>
#include <QtTest/QtTest>
#include <QtTest/qtestkeyboard.h>

#include <functional>

//------------------------------------------------------------------------------
InputInterceptorTest::InputInterceptorTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldStoreSetWidget()
{
    QWidget widget;
    InputInterceptor interceptor;
    interceptor.setSender(&widget);

    QCOMPARE(interceptor.sender(), &widget);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldNotThrowIfWidgetNullWhileDeactivate()
{
    InputInterceptor interceptor;
    interceptor.deactivate();

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldNotThrowIfWidgetNullWhileActivate()
{
    InputInterceptor interceptor;
    interceptor.activate();

    QVERIFY(true);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldStoreReceivedTool()
{
    InputInterceptor interceptor;
    MockTool tool;
    interceptor.setReceiver(&tool);

    QCOMPARE(interceptor.receiver(), &tool);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldReturnNullWidgetByDefault()
{
    InputInterceptor interceptor;

    QVERIFY(interceptor.sender() == nullptr);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldReturnNullReceivedToolByDefault()
{
    InputInterceptor interceptor;

    QVERIFY(interceptor.receiver() == nullptr);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldBeDeactivedByDefault()
{
    InputInterceptor interceptor;

    QCOMPARE(interceptor.isActive(), false);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldBeActiveAfterActivating()
{
    InputInterceptor interceptor;
    QCOMPARE(interceptor.isActive(), false);

    interceptor.activate();

    QCOMPARE(interceptor.isActive(), true);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldBeWorkingAfterActivatingWithSenderAndReceiver()
{
    QWidget widget;
    InputInterceptor interceptor;
    interceptor.setSender(&widget);
    MockTool tool;
    interceptor.setReceiver(&tool);

    QCOMPARE(interceptor.isWorking(), false);

    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), true);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldBeWorkingAfterSettingSenderIfWasActivatedWithNullOne()
{
    QWidget widget; MockTool tool;

    InputInterceptor interceptor;
    interceptor.setReceiver(&tool);
    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), false);

    interceptor.setSender(&widget);

    QCOMPARE(interceptor.isWorking(), true);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldBeWorkingAfterSettingReceiverIfWasActivatedWithNullOne()
{
    QWidget widget; MockTool tool;

    InputInterceptor interceptor;
    interceptor.setSender(&widget);
    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), false);

    interceptor.setReceiver(&tool);

    QCOMPARE(interceptor.isWorking(), true);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldNotBeWorkingAfterActivatingWithoutSettingTheSenderAndReceiver()
{
    QWidget widget;
    InputInterceptor interceptor;

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
void InputInterceptorTest::shouldNotBeActiveAfterActivatingAndDeactivating()
{
    InputInterceptor interceptor;

    interceptor.activate();

    QCOMPARE(interceptor.isActive(), true);

    interceptor.deactivate();

    QCOMPARE(interceptor.isActive(), false);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldNotBeWorkingIfNotActive()
{
    QWidget widget; MockTool tool;
    InputInterceptor interceptor;
    interceptor.setReceiver(&tool);
    interceptor.setSender(&widget);
    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), true);

    interceptor.deactivate();

    QCOMPARE(interceptor.isWorking(), false);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldNotBeInvokeKeyboardHandlerAfterSettingNullSender()
{
    QWidget widget;
    InputInterceptor interceptor;
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
void InputInterceptorTest::shouldNotBeInvokeKeyboardHandlerAfterSettingNullReceiver()
{
    QWidget widget;
    InputInterceptor interceptor;
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
void InputInterceptorTest::shouldNotBeWorkingAfterSenderDeletion()
{
    MockTool tool;

    InputInterceptor interceptor;
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
void InputInterceptorTest::shouldCallReceiverIfWorking()
{
    QWidget widget;
    InputInterceptor interceptor;
    interceptor.setSender(&widget);
    MockTool tool;
    interceptor.setReceiver(&tool);
    interceptor.activate();

    QCOMPARE(interceptor.isWorking(), true);

    QTest::keyRelease(&widget, 'E');

    QVERIFY(tool.keyUpCalled);
}

//------------------------------------------------------------------------------
void InputInterceptorTest::shouldNotInvokeKeyboardHandlerIfNotWorking()
{
    QWidget widget;
    InputInterceptor interceptor;
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
void InputInterceptorTest::shouldInvokeKeyboardHandlerAfterReactivating()
{
    QWidget widget;
    InputInterceptor interceptor;
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
