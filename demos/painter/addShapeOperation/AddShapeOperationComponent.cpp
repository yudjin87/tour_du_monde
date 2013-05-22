/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "AddShapeOperationComponent.h"
#include "AddShapeOperationInteractiveExtension.h"
#include "AddShapesCommand.h"

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/ComponentExport.h>
#include <utils/IServiceLocator.h>

#include <functional>

//------------------------------------------------------------------------------
static const QByteArray productName("AddShapeOperation");

//------------------------------------------------------------------------------
// TODO: will be removed when c++11 is supported (with lambdas)
void *createAddShapesCommand(IServiceLocator *locator)
{
    return new AddShapesCommand(locator);
}

//------------------------------------------------------------------------------
AddShapeOperationComponent::AddShapeOperationComponent(QObject *parent /*= nullptr*/)
    : BaseComponent("AddShapeOperation", parent)
{
    IInteractiveExtension *interactiveExtension = new AddShapeOperationInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    addParent("Dom");
    addParent("Geodatabase");
    addParent("Display");
    addParent("Carto");
    addParent("CartoUI");
    addParent("Undo");
    setProductName(productName);
    setProvider("Carousel");
}

//------------------------------------------------------------------------------
AddShapeOperationComponent::~AddShapeOperationComponent()
{
}

//------------------------------------------------------------------------------
bool AddShapeOperationComponent::onStartup(IServiceLocator *serviceLocator)
{
    if (serviceLocator == nullptr)
        return false;

    auto creator = std::bind(&createAddShapesCommand, serviceLocator);
    serviceLocator->registerType<AddShapesCommand>(creator);

    return true;
}

//------------------------------------------------------------------------------
void AddShapeOperationComponent::onShutdown()
{
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(AddShapeOperationComponent)

//------------------------------------------------------------------------------
