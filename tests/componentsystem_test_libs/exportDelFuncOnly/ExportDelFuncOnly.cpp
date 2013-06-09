#include "ExportDelFuncOnly.h"

#include <carousel/componentsystem/ComponentExport.h>

//------------------------------------------------------------------------------
TestComponent::TestComponent()
    : BaseComponent("TestComponent")
{
}

//------------------------------------------------------------------------------
RELEASE_INSTANCE_FUNCTION(TestComponent)

//------------------------------------------------------------------------------
