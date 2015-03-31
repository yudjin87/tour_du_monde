#pragma once
#include <QtCore/QObject>

class ServiceLocatorTest: public QObject
{
    Q_OBJECT
public:
    ServiceLocatorTest();

private Q_SLOTS:
    // Instances
    void canRegisterInstance();
    void shouldNotRegisterInstanceOfExistingType();
    void canRegisterInstanceOfExistingTypeWithTag();
    void shouldNotRegisterInstanceOfExistingTypeWithExistingTag();
    void unregisterInstance_shouldReturnFoundInstance();
    void unregisterInstance_shouldRemoveInstanceFromList();
    void shouldRegisterInstanceAfterUnregistring();

    void canLocateToRegisterInstanceByType();
    void canLocateToRegisterInstanceByTypeAndTag();
    void canLocateToRegisteredObjectByClassName();

    void services_shouldReturnAllRegisteredServices();

    // Types
    void canRegisterFactoryMethodForType();
    void canBindConcreteClassForType();
    void shouldNotBindConcreteClassForExistingType();
    void canBindConcreteClassForExistingTypeWithTag();
    void shouldNotBindConcreteClassForExistingTypeWithExistingTag();

    void canBuildRegisteredWithFactoryMethodInterfaceByType();
    void canBuildBindedInterfaceByType();
    void canBuildBindedInterfaceByTypeAndTag();    
    void canBuildRegisteredWithFactoryMethodInterfaceClassName();

};

