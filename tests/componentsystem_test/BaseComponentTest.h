#ifndef BASECOMPONENTTEST_H
#define BASECOMPONENTTEST_H

#include <QtCore/QObject>

class BaseComponentTest : public QObject
{
    Q_OBJECT
public:
    BaseComponentTest(QObject *parent = 0);

private Q_SLOTS:
    void shouldNotSetAvailabilityIfDidNotLoad();
    void shouldEmitWhenAvailabilitySet();
    void shouldSaveSetAvailabilityInDestructor();
    void shouldSetLoadedAvailability();
    void shouldSetAvailabilityEnabledByDefault();

    void shouldReturnResultOfProtectedMethodOnFirstSuccessfulStartup();
    void started_shouldReturnCorrectValue();
    void shouldNotStartupIfAlreadyStarted();
    void shouldShutdownIfAlreadyStoped();

    void shouldReturnRegisteredInDerivedClassesExtensions();
    void shouldReturnNullWhenUnregisteredExtensionIsQueried();

    void isCompatible_shouldReturnTrue();
};

#endif // BASECOMPONENTTEST_H
