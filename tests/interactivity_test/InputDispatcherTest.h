#pragma once
#include <QtCore/QObject>

class InputDispatcherTest : public QObject
{
    Q_OBJECT
public:
    explicit InputDispatcherTest(QObject *parent = 0);
    
private Q_SLOTS:
    void shouldStoreSetWidget();
    void shouldNotThrowIfWidgetNullWhileDeactivate();
    void shouldNotThrowIfWidgetNullWhileActivate();
    void shouldStoreReceivedTool();
    void shouldReturnNullWidgetByDefault();
    void shouldReturnNullReceivedToolByDefault();
    void shouldBeDeactivedByDefault();
    void shouldBeActiveAfterActivating();
    void shouldBeWorkingAfterActivatingWithSenderAndReceiver();
    void shouldBeWorkingAfterSettingSenderIfWasActivatedWithNullOne();
    void shouldBeWorkingAfterSettingReceiverIfWasActivatedWithNullOne();

    void shouldNotBeWorkingAfterActivatingWithoutSettingTheSenderAndReceiver();
    void shouldNotBeActiveAfterActivatingAndDeactivating();
    void shouldNotBeWorkingIfNotActive();
    void shouldNotBeInvokeKeyboardHandlerAfterSettingNullSender();
    void shouldNotBeInvokeKeyboardHandlerAfterSettingNullReceiver();
    void shouldNotBeWorkingAfterSenderDeletion();
    void shouldNotBeWorkingAfterReceiverDeletion();

    void shouldCallReceiverIfWorking();
    void shouldNotInvokeKeyboardHandlerIfNotWorking();
    void shouldInvokeKeyboardHandlerAfterReactivating();
};

