#pragma once
#include <carousel/componentsystem/CompositeComponentProvider.h>

class MockCompositeComponentProvider : public CompositeComponentProvider
{
public:
    MockCompositeComponentProvider();
    ~MockCompositeComponentProvider();

    size_t size() const;
};

