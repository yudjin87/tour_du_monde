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

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QUndoStack>

//------------------------------------------------------------------------------
static const QByteArray productName("AddShapeOperation");

//------------------------------------------------------------------------------
AddShapeOperationComponent::AddShapeOperationComponent(QObject *parent /*= nullptr*/)
    : BaseComponent("org.carousel.demos.AddShapeOperation", parent)
{
    IInteractiveExtension *interactiveExtension = new AddShapeOperationInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    addParent("org.carousel.demos.Geodatabase", 1, 0);
    addParent("org.carousel.demos.Display", 1, 0);
    addParent("org.carousel.demos.Carto", 1, 0);
    addParent("org.carousel.demos.CartoUI", 1, 0);
    addParent("org.carousel.Undo", 1, 0);
    setShortName("Add Shape Operation");
    setProductName(productName);
    setProvider("Carousel");
    setVersion(1, 0);
}

//------------------------------------------------------------------------------
AddShapeOperationComponent::~AddShapeOperationComponent()
{
}

//------------------------------------------------------------------------------
bool AddShapeOperationComponent::onStartup(IServiceLocator *serviceLocator)
{    
    QUndoStack *stack = serviceLocator->locate<QUndoStack>();
    auto creator = [stack, serviceLocator](){return new AddShapesCommand(stack, serviceLocator);};
    serviceLocator->registerType<AddShapesCommand>(creator);

    return true;
}

//------------------------------------------------------------------------------
void AddShapeOperationComponent::onShutdown(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(AddShapeOperationComponent)

//------------------------------------------------------------------------------
