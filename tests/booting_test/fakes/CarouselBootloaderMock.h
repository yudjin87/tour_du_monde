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
    ILogger *createLogger();
    IComponentProvider *createComponentProvider();
    IComponentManager *createComponentManager();
    IServiceLocator *createServiceLocator();
    QMainWindow *createMainWindow();
    void initialiseComponentProvider();
    void configureComponentProvider();
    void configureComponentManager();
    void configureServiceLocator();

private:
    bool mcreateLoggerCalled;
    bool mcreateComponentProviderCalled;
    bool mcreateComponentManagerCalled;
    bool mcreateServiceLocatorCalled;
    bool mcreateMainWindowCalled;
    bool minitialiseComponentProviderCalled;
    bool mconfigureComponentProviderCalled;
    bool mconfigureComponentManagerCalled;
    bool mconfigureServiceLocatorCalled;
    QStringList m_methodCalls;
};

#endif // CAROUSELBOOTLOADERMOCK_H
