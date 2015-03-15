#include "ExportBothFuncs.h"

#include <carousel/componentsystem/ComponentExport.h>

TestComponent::TestComponent()
    : BaseComponent("TestComponent")
{
}

EXPORT_COMPONENT(TestComponent)

