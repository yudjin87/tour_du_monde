#ifndef BASECOMPONENTTEST_H
#define BASECOMPONENTTEST_H

#include <QtCore/QObject>

class BaseComponentTest : public QObject
{
    Q_OBJECT
public:
    BaseComponentTest(QObject *parent = 0);

private Q_SLOTS:
    void shouldReturnResultOfProtectedMethodOnFirstSuccessfulStartup();
    void shouldAssignResultOfProtectedMethodToTheStartedFlag();
    void shouldNotStartupIfAlreadyStarted();
    void shouldShutdownIfAlreadyStoped();

    void shouldReturnRegisteredInDerivedClassesExtensions();
    void shouldReturnNullWhenUnregisteredExtensionIsQueried();
};

#endif // BASECOMPONENTTEST_H
