#include "ExportDelFuncOnly.h"

#include <componentsystem/ComponentExport.h>

//------------------------------------------------------------------------------
TestComponent::TestComponent()
    : BaseComponent("TestComponent")
{
}

//------------------------------------------------------------------------------
RELEASE_INSTANCE_FUNCTION(TestComponent)

//------------------------------------------------------------------------------
