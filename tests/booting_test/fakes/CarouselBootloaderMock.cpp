#include "CarouselBootloaderMock.h"

//------------------------------------------------------------------------------
CarouselBootloaderMock::CarouselBootloaderMock()
    : mcreateLoggerCalled(false)
    , mcreateComponentProviderCalled(false)
    , mcreateComponentManagerCalled(false)
    , mcreateServiceLocatorCalled(false)
    , mcreateMainWindowCalled(false)
    , minitialiseComponentProviderCalled(false)
    , mconfigureComponentProviderCalled(false)
    , mconfigureComponentManagerCalled(false)
    , mconfigureServiceLocatorCalled(false)
{
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::createLoggerCalled() const
{
    return mcreateLoggerCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::createComponentProviderCalled() const
{
    return mcreateComponentProviderCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::createComponentManagerCalled() const
{
    return mcreateComponentManagerCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::createServiceLocatorCalled() const
{
    return mcreateServiceLocatorCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::createMainWindowCalled() const
{
    return mcreateMainWindowCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::initialiseComponentProviderCalled() const
{
    return minitialiseComponentProviderCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::configureComponentProviderCalled() const
{
    return mconfigureComponentProviderCalled;
}

bool CarouselBootloaderMock::configureComponentManagerCalled() const
{
    return mconfigureComponentManagerCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::configureServiceLocatorCalled() const
{
    return mconfigureServiceLocatorCalled;
}

//------------------------------------------------------------------------------
const QStringList &CarouselBootloaderMock::methodCalls() const
{
    return m_methodCalls;
}

//------------------------------------------------------------------------------
ILogger *CarouselBootloaderMock::createLogger()
{
    mcreateLoggerCalled = true;
    m_methodCalls.push_back("createLogger");
    return CarouselBootloader::createLogger();
}

//------------------------------------------------------------------------------
IComponentProvider *CarouselBootloaderMock::createComponentProvider()
{
    mcreateComponentProviderCalled = true;
    m_methodCalls.push_back("createComponentProvider");
    return CarouselBootloader::createComponentProvider();
}

//------------------------------------------------------------------------------
IComponentManager *CarouselBootloaderMock::createComponentManager()
{
    mcreateComponentManagerCalled = true;
    m_methodCalls.push_back("createComponentManager");
    return CarouselBootloader::createComponentManager();
}

//------------------------------------------------------------------------------
IServiceLocator *CarouselBootloaderMock::createServiceLocator()
{
    mcreateServiceLocatorCalled = true;
    m_methodCalls.push_back("createServiceLocator");
    return CarouselBootloader::createServiceLocator();
}

//------------------------------------------------------------------------------
QMainWindow *CarouselBootloaderMock::createMainWindow()
{
    mcreateMainWindowCalled = true;
    m_methodCalls.push_back("createMainWindow");
    return CarouselBootloader::createMainWindow();
}

//------------------------------------------------------------------------------
void CarouselBootloaderMock::initialiseComponentProvider()
{
    minitialiseComponentProviderCalled = true;
    m_methodCalls.push_back("initialiseComponentProvider");
    CarouselBootloader::initialiseComponentProvider();
}

//------------------------------------------------------------------------------
void CarouselBootloaderMock::configureComponentProvider()
{
    mconfigureComponentProviderCalled = true;
    m_methodCalls.push_back("configureComponentProvider");
    CarouselBootloader::configureComponentProvider();
}

//------------------------------------------------------------------------------
void CarouselBootloaderMock::configureComponentManager()
{
    mconfigureComponentManagerCalled = true;
    m_methodCalls.push_back("configureComponentManager");
    CarouselBootloader::configureComponentManager();
}

//------------------------------------------------------------------------------
void CarouselBootloaderMock::configureServiceLocator()
{
    mconfigureServiceLocatorCalled = true;
    m_methodCalls.push_back("configureServiceLocator");
    CarouselBootloader::configureServiceLocator();
}

//------------------------------------------------------------------------------
