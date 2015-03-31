#pragma once
#include <carousel/booting/BootloaderBase.h>

class BootloaderMock : public BootloaderBase
{
public:
    BootloaderMock();

public:
    void callCreateLogger();
    void callCreateComponentProvider();
    void callCreateComponentManager();
    void callCreateServiceLocator();
    void callCreateMainWindow();

    ILoggerEngineCreator *logger() const;
    IComponentProvider *componentProvider() const;
    IComponentManager *componentManager() const;
    IServiceLocator *serviceLocator() const;

    int runAttemptsCount() const;

protected:
    void safeRun();
    void configureServiceLocator();

private:
    int m_runAttemptsCount;
};

