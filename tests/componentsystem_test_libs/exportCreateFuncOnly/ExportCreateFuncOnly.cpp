#include "ExportCreateFuncOnly.h"

#include <carousel/componentsystem/ComponentExport.h>

//------------------------------------------------------------------------------
TestComponent::TestComponent()
    : BaseComponent("TestComponent")
{
}

//------------------------------------------------------------------------------
CREATE_INSTANCE_FUNCTION(TestComponent)

//------------------------------------------------------------------------------
