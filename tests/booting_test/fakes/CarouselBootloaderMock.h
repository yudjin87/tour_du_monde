#pragma once
#include <carousel/booting/CarouselBootloader.h>

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

    IServiceLocator *locator();

protected:
    ILoggerEngineCreator *createLoggerEngine();
    void onLoadingSequenceStarting();
    IComponentProvider *createComponentProvider();
    IComponentManager *createComponentManager();
    IServiceLocator *createServiceLocator();
    void initialiseComponentProvider();
    void configureComponentProvider();
    void configureComponentManager();
    void configureServiceLocator();
    void startComponentManager();
    void onLoadingSequenceFinised();

private:
    bool mcreateLoggerCalled;
    bool monLoadingSequenceStartingCalled;
    bool mcreateComponentProviderCalled;
    bool mcreateComponentManagerCalled;
    bool mcreateServiceLocatorCalled;
    bool minitialiseComponentProviderCalled;
    bool mconfigureComponentProviderCalled;
    bool mconfigureComponentManagerCalled;
    bool mconfigureServiceLocatorCalled;
    bool mstartComponentManagerCalled;
    bool monLoadingSequenceFinisedCalled;
    QStringList m_methodCalls;
};

