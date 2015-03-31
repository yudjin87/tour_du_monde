#pragma once
#include <QtCore/QObject>

class BaseBootloaderTest : public QObject
{
    Q_OBJECT
public:
    explicit BaseBootloaderTest(QObject *parent = 0);
    
private Q_SLOTS:
    void shouldCreateDefaultLogger();
    void shouldCreateDefaultComponentProvider();
    void shouldCreateDefaultComponentManager();
    void shouldCreateDefaultServiceLocator();
    void canRunOnlyOncePerInstance();
};

