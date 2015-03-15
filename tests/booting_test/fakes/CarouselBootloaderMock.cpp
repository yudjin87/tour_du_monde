#include "CarouselBootloaderMock.h"

CarouselBootloaderMock::CarouselBootloaderMock()
    : mcreateLoggerCalled(false)
    , monLoadingSequenceStartingCalled(false)
    , mcreateComponentProviderCalled(false)
    , mcreateComponentManagerCalled(false)
    , mcreateServiceLocatorCalled(false)
    , minitialiseComponentProviderCalled(false)
    , mconfigureComponentProviderCalled(false)
    , mconfigureComponentManagerCalled(false)
    , mconfigureServiceLocatorCalled(false)
    , mstartComponentManagerCalled(false)
    , monLoadingSequenceFinisedCalled(false)
{
}

bool CarouselBootloaderMock::createLoggerCalled() const
{
    return mcreateLoggerCalled;
}

bool CarouselBootloaderMock::createComponentProviderCalled() const
{
    return mcreateComponentProviderCalled;
}

bool CarouselBootloaderMock::createComponentManagerCalled() const
{
    return mcreateComponentManagerCalled;
}

bool CarouselBootloaderMock::createServiceLocatorCalled() const
{
    return mcreateServiceLocatorCalled;
}

bool CarouselBootloaderMock::initialiseComponentProviderCalled() const
{
    return minitialiseComponentProviderCalled;
}

bool CarouselBootloaderMock::configureComponentProviderCalled() const
{
    return mconfigureComponentProviderCalled;
}

bool CarouselBootloaderMock::configureComponentManagerCalled() const
{
    return mconfigureComponentManagerCalled;
}

bool CarouselBootloaderMock::configureServiceLocatorCalled() const
{
    return mconfigureServiceLocatorCalled;
}

const QStringList &CarouselBootloaderMock::methodCalls() const
{
    return m_methodCalls;
}

IServiceLocator *CarouselBootloaderMock::locator()
{
    return serviceLocator();
}

ILoggerEngineCreator *CarouselBootloaderMock::createLoggerEngine()
{
    mcreateLoggerCalled = true;
    m_methodCalls.push_back("createLoggerEngine");
    return CarouselBootloader::createLoggerEngine();
}

IComponentProvider *CarouselBootloaderMock::createComponentProvider()
{
    mcreateComponentProviderCalled = true;
    m_methodCalls.push_back("createComponentProvider");
    return CarouselBootloader::createComponentProvider();
}

IComponentManager *CarouselBootloaderMock::createComponentManager()
{
    mcreateComponentManagerCalled = true;
    m_methodCalls.push_back("createComponentManager");
    return CarouselBootloader::createComponentManager();
}

IServiceLocator *CarouselBootloaderMock::createServiceLocator()
{
    mcreateServiceLocatorCalled = true;
    m_methodCalls.push_back("createServiceLocator");
    return CarouselBootloader::createServiceLocator();
}

void CarouselBootloaderMock::initialiseComponentProvider()
{
    minitialiseComponentProviderCalled = true;
    m_methodCalls.push_back("initialiseComponentProvider");
    CarouselBootloader::initialiseComponentProvider();
}

void CarouselBootloaderMock::configureComponentProvider()
{
    mconfigureComponentProviderCalled = true;
    m_methodCalls.push_back("configureComponentProvider");
    CarouselBootloader::configureComponentProvider();
}

void CarouselBootloaderMock::configureComponentManager()
{
    mconfigureComponentManagerCalled = true;
    m_methodCalls.push_back("configureComponentManager");
    CarouselBootloader::configureComponentManager();
}

void CarouselBootloaderMock::configureServiceLocator()
{
    mconfigureServiceLocatorCalled = true;
    m_methodCalls.push_back("configureServiceLocator");
    CarouselBootloader::configureServiceLocator();
}

void CarouselBootloaderMock::onLoadingSequenceStarting()
{
    monLoadingSequenceStartingCalled = true;
    m_methodCalls.push_back("onLoadingSequenceStarting");
    CarouselBootloader::onLoadingSequenceStarting();
}

void CarouselBootloaderMock::startComponentManager()
{
    mstartComponentManagerCalled = true;
    m_methodCalls.push_back("startComponentManager");
    CarouselBootloader::startComponentManager();
}

void CarouselBootloaderMock::onLoadingSequenceFinised()
{
    monLoadingSequenceFinisedCalled = true;
    m_methodCalls.push_back("onLoadingSequenceFinised");
    CarouselBootloader::onLoadingSequenceFinised();
}

