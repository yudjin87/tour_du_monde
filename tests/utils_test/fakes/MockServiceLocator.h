#ifndef MOCKSERVICELOCATOR_H
#define MOCKSERVICELOCATOR_H

#include <utils/ServiceLocator.h>
#include <utils/TypeObjectsMap.h>

class MockServiceLocator : public ServiceLocator
{
public:
    MockServiceLocator();

public:
    const TypeObjectsMap<void *> &items() const;
    const TypeObjectsMap<factoryMethod> &creators() const;
};

#endif // MOCKSERVICELOCATOR_H
