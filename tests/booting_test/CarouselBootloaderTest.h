#ifndef CAROUSELBOOTLOADERTEST_H
#define CAROUSELBOOTLOADERTEST_H

#include <QtCore/QObject>

class CarouselBootloaderTest : public QObject
{
    Q_OBJECT
public:
    explicit CarouselBootloaderTest(QObject *parent = 0);
    
private Q_SLOTS:
    // running:
    void canRunLoading();
    void shouldCallCreateLoggerEngineOnRun();
    void shouldInstallCreatedLoggerEngineOnRun();
    void shouldCallCreateComponentProviderOnRun();
    void shouldCallCreateComponentManagerOnRun();
    void shouldCallCreateServiceLocatorOnRun();
    void shouldCallConfigureComponentProviderOnRun();
    void shouldCallConfigureComponentManagerOnRun();
    void shouldCallConfigureServiceLocatorOnRun();
    void shouldCallInitialiseComponentProviderOnRun();
    void shouldCallRunSequenceInOrderOnRun();
    void shouldInitialiseComponentProviderOnRun();

    void configuringComponentManagerShouldAddComponentsToIt();

    void configuringServiceLocatorShouldAddComponentProviderToServices();
    void configuringServiceLocatorShouldAddComponentManagerToServices();

    void shouldInstallNullLoggerEngineInDestructor();
};

#endif // CAROUSELBOOTLOADERTEST_H
