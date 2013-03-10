#include "ExportBothFuncs.h"

#include <componentsystem/ComponentExport.h>

//------------------------------------------------------------------------------
TestComponent::TestComponent()
    : BaseComponent("TestComponent")
{
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(TestComponent)

//------------------------------------------------------------------------------
