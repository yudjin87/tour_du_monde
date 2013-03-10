#ifndef INPUTINTERCEPTORTEST_H
#define INPUTINTERCEPTORTEST_H

#include <QtCore/QObject>

class InputInterceptorTest : public QObject
{
    Q_OBJECT
public:
    explicit InputInterceptorTest(QObject *parent = 0);
    
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

    void shouldCallReceiverIfWorking();
    void shouldNotInvokeKeyboardHandlerIfNotWorking();
    void shouldInvokeKeyboardHandlerAfterReactivating();
};

#endif // INPUTINTERCEPTORTEST_H
