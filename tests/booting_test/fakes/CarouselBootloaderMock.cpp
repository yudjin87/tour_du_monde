#include "CarouselBootloaderMock.h"

//------------------------------------------------------------------------------
CarouselBootloaderMock::CarouselBootloaderMock()
    : m_createLoggerCalled(false)
    , m_createComponentProviderCalled(false)
    , m_createComponentManagerCalled(false)
    , m_createServiceLocatorCalled(false)
    , m_createMainWindowCalled(false)
    , m_initialiseComponentProviderCalled(false)
    , m_configureComponentProviderCalled(false)
    , m_configureComponentManagerCalled(false)
    , m_configureServiceLocatorCalled(false)
{
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::createLoggerCalled() const
{
    return m_createLoggerCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::createComponentProviderCalled() const
{
    return m_createComponentProviderCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::createComponentManagerCalled() const
{
    return m_createComponentManagerCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::createServiceLocatorCalled() const
{
    return m_createServiceLocatorCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::createMainWindowCalled() const
{
    return m_createMainWindowCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::initialiseComponentProviderCalled() const
{
    return m_initialiseComponentProviderCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::configureComponentProviderCalled() const
{
    return m_configureComponentProviderCalled;
}

bool CarouselBootloaderMock::configureComponentManagerCalled() const
{
    return m_configureComponentManagerCalled;
}

//------------------------------------------------------------------------------
bool CarouselBootloaderMock::configureServiceLocatorCalled() const
{
    return m_configureServiceLocatorCalled;
}

//------------------------------------------------------------------------------
const QStringList &CarouselBootloaderMock::methodCalls() const
{
    return m_methodCalls;
}

//------------------------------------------------------------------------------
ILogger *CarouselBootloaderMock::_createLogger()
{
    m_createLoggerCalled = true;
    m_methodCalls.push_back("_createLogger");
    return CarouselBootloader::_createLogger();
}

//------------------------------------------------------------------------------
IComponentProvider *CarouselBootloaderMock::_createComponentProvider()
{
    m_createComponentProviderCalled = true;
    m_methodCalls.push_back("_createComponentProvider");
    return CarouselBootloader::_createComponentProvider();
}

//------------------------------------------------------------------------------
IComponentManager *CarouselBootloaderMock::_createComponentManager()
{
    m_createComponentManagerCalled = true;
    m_methodCalls.push_back("_createComponentManager");
    return CarouselBootloader::_createComponentManager();
}

//------------------------------------------------------------------------------
IServiceLocator *CarouselBootloaderMock::_createServiceLocator()
{
    m_createServiceLocatorCalled = true;
    m_methodCalls.push_back("_createServiceLocator");
    return CarouselBootloader::_createServiceLocator();
}

//------------------------------------------------------------------------------
QMainWindow *CarouselBootloaderMock::_createMainWindow()
{
    m_createMainWindowCalled = true;
    m_methodCalls.push_back("_createMainWindow");
    return CarouselBootloader::_createMainWindow();
}

//------------------------------------------------------------------------------
void CarouselBootloaderMock::_initialiseComponentProvider()
{
    m_initialiseComponentProviderCalled = true;
    m_methodCalls.push_back("_initialiseComponentProvider");
    CarouselBootloader::_initialiseComponentProvider();
}

//------------------------------------------------------------------------------
void CarouselBootloaderMock::_configureComponentProvider()
{
    m_configureComponentProviderCalled = true;
    m_methodCalls.push_back("_configureComponentProvider");
    CarouselBootloader::_configureComponentProvider();
}

//------------------------------------------------------------------------------
void CarouselBootloaderMock::_configureComponentManager()
{
    m_configureComponentManagerCalled = true;
    m_methodCalls.push_back("_configureComponentManager");
    CarouselBootloader::_configureComponentManager();
}

//------------------------------------------------------------------------------
void CarouselBootloaderMock::_configureServiceLocator()
{
    m_configureServiceLocatorCalled = true;
    m_methodCalls.push_back("_configureServiceLocator");
    CarouselBootloader::_configureServiceLocator();
}

//------------------------------------------------------------------------------
