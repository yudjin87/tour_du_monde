#include "ExportCreateFuncOnly.h"

#include <componentsystem/ComponentExport.h>

//------------------------------------------------------------------------------
TestComponent::TestComponent()
    : BaseComponent("TestComponent")
{
}

//------------------------------------------------------------------------------
CREATE_INSTANCE_FUNCTION(TestComponent)

//------------------------------------------------------------------------------
