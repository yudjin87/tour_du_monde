#include "BootloaderMock.h"

//------------------------------------------------------------------------------
BootloaderMock::BootloaderMock()
    : m_runAttemptsCount(0)
{
}

//------------------------------------------------------------------------------
void BootloaderMock::callCreateLogger()
{
    mp_logger = _createLogger();
}

//------------------------------------------------------------------------------
void BootloaderMock::callCreateComponentProvider()
{
    mp_componentProvider = _createComponentProvider();
}

//------------------------------------------------------------------------------
void BootloaderMock::callCreateComponentManager()
{
    mp_componentManager = _createComponentManager();
}

//------------------------------------------------------------------------------
void BootloaderMock::callCreateServiceLocator()
{
    mp_serviceLocator = _createServiceLocator();
}

//------------------------------------------------------------------------------
void BootloaderMock::callCreateMainWindow()
{
    mp_mainWindow = _createMainWindow();
}

//------------------------------------------------------------------------------
ILogger *BootloaderMock::logger() const
{
    return mp_logger;
}

//------------------------------------------------------------------------------
IComponentProvider *BootloaderMock::componentProvider() const
{
    return mp_componentProvider;
}

//------------------------------------------------------------------------------
IComponentManager *BootloaderMock::componentManager() const
{
    return mp_componentManager;
}

//------------------------------------------------------------------------------
IServiceLocator *BootloaderMock::serviceLocator() const
{
    return mp_serviceLocator;
}

//------------------------------------------------------------------------------
QMainWindow *BootloaderMock::mainWindow() const
{
    return mp_mainWindow;
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
