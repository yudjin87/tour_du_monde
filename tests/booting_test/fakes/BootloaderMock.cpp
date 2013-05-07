#include "BootloaderMock.h"

//------------------------------------------------------------------------------
BootloaderMock::BootloaderMock()
    : m_runAttemptsCount(0)
{
}

//------------------------------------------------------------------------------
void BootloaderMock::callCreateLogger()
{
    m_logger = _createLogger();
}

//------------------------------------------------------------------------------
void BootloaderMock::callCreateComponentProvider()
{
    m_componentProvider = _createComponentProvider();
}

//------------------------------------------------------------------------------
void BootloaderMock::callCreateComponentManager()
{
    m_componentManager = _createComponentManager();
}

//------------------------------------------------------------------------------
void BootloaderMock::callCreateServiceLocator()
{
    m_serviceLocator = _createServiceLocator();
}

//------------------------------------------------------------------------------
void BootloaderMock::callCreateMainWindow()
{
    m_mainWindow = _createMainWindow();
}

//------------------------------------------------------------------------------
ILogger *BootloaderMock::logger() const
{
    return m_logger;
}

//------------------------------------------------------------------------------
IComponentProvider *BootloaderMock::componentProvider() const
{
    return m_componentProvider;
}

//------------------------------------------------------------------------------
IComponentManager *BootloaderMock::componentManager() const
{
    return m_componentManager;
}

//------------------------------------------------------------------------------
IServiceLocator *BootloaderMock::serviceLocator() const
{
    return m_serviceLocator;
}

//------------------------------------------------------------------------------
QMainWindow *BootloaderMock::mainWindow() const
{
    return m_mainWindow;
}

//------------------------------------------------------------------------------
int BootloaderMock::runAttemptsCount() const
{
    return m_runAttemptsCount;
}

//------------------------------------------------------------------------------
void BootloaderMock::_run()
{
    ++m_runAttemptsCount;
}

//------------------------------------------------------------------------------
void BootloaderMock::_configureServiceLocator()
{
}

//------------------------------------------------------------------------------
