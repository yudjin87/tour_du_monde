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
    void shouldCallCreateLoggerOnRun();
    void shouldCallCreateComponentProviderOnRun();
    void shouldCallCreateComponentManagerOnRun();
    void shouldCallCreateServiceLocatorOnRun();
    void shouldCallCreateMainWindowOnRun();
    void shouldCallConfigureComponentProviderOnRun();
    void shouldCallConfigureComponentManagerOnRun();
    void shouldCallConfigureServiceLocatorOnRun();
    void shouldCallInitialiseComponentProviderOnRun();
    void shouldCallRunSequenceInOrderOnRun();
    void shouldInitialiseComponentProviderOnRun();

    void configuringComponentManagerShouldAddComponentsToIt();

    void configuringServiceLocatorShouldAddComponentProviderToServices();
    void configuringServiceLocatorShouldAddLoggerToServices();
    void configuringServiceLocatorShouldAddComponentManagerToServices();
    void configuringServiceLocatorShouldAddMainWindowToServices();
};

#endif // CAROUSELBOOTLOADERTEST_H
