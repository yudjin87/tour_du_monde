#ifndef CAROUSELBOOTLOADERMOCK_H
#define CAROUSELBOOTLOADERMOCK_H

#include <booting/CarouselBootloader.h>

#include <QtCore/QStringList>

class CarouselBootloaderMock : public CarouselBootloader
{
public:
    CarouselBootloaderMock();

public:
    bool createLoggerCalled() const;
    bool createComponentProviderCalled() const;
    bool createComponentManagerCalled() const;
    bool createServiceLocatorCalled() const;
    bool createMainWindowCalled() const;

    bool initialiseComponentProviderCalled() const;
    bool configureComponentProviderCalled() const;
    bool configureComponentManagerCalled() const;
    bool configureServiceLocatorCalled() const;

    const QStringList &methodCalls() const;

protected:
    ILogger *_createLogger();
    IComponentProvider *_createComponentProvider();
    IComponentManager *_createComponentManager();
    IServiceLocator *_createServiceLocator();
    QMainWindow *_createMainWindow();
    void _initialiseComponentProvider();
    void _configureComponentProvider();
    void _configureComponentManager();
    void _configureServiceLocator();

private:
    bool m_createLoggerCalled;
    bool m_createComponentProviderCalled;
    bool m_createComponentManagerCalled;
    bool m_createServiceLocatorCalled;
    bool m_createMainWindowCalled;
    bool m_initialiseComponentProviderCalled;
    bool m_configureComponentProviderCalled;
    bool m_configureComponentManagerCalled;
    bool m_configureServiceLocatorCalled;
    QStringList m_methodCalls;
};

#endif // CAROUSELBOOTLOADERMOCK_H
