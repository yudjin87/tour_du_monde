#pragma once
#include <carousel/utils/ServiceLocator.h>
#include <carousel/utils/TypeObjectsMap.h>

class MockServiceLocator : public ServiceLocator
{
public:
    MockServiceLocator();

public:
    const TypeObjectsMap<void *> &items() const;
    const TypeObjectsMap<factoryMethod> &creators() const;
};

