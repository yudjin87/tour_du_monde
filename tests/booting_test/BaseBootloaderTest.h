#ifndef BASEBOOTLOADERTEST_H
#define BASEBOOTLOADERTEST_H

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
    void shouldCreateDefaultMainWindow();
    void canRunOnlyOncePerInstance();
};

#endif // BASEBOOTLOADERTEST_H
