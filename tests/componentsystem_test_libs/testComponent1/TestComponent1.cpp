#include "TestComponent1.h"

#include <carousel/componentsystem/ComponentExport.h>

TestComponent1::TestComponent1()
    : BaseComponent("TestComponent1")
{
}

EXPORT_COMPONENT(TestComponent1)

