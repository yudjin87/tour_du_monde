#ifndef SERVICELOCATORTEST_H
#define SERVICELOCATORTEST_H

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
    void canLocateByIndex();

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

#endif // SERVICELOCATORTEST_H
