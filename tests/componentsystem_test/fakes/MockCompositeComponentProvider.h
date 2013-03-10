#ifndef MOCKCOMPOSITECOMPONENTPROVIDER_H
#define MOCKCOMPOSITECOMPONENTPROVIDER_H

#include <componentsystem/CompositeComponentProvider.h>

class MockCompositeComponentProvider : public CompositeComponentProvider
{
public:
    MockCompositeComponentProvider();
    ~MockCompositeComponentProvider();

    size_t size() const;
};

#endif // MOCKCOMPOSITECOMPONENTPROVIDER_H
