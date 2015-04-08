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

#include "CartoComponent.h"
#include "commands/AddShapesCommand.h"
#include "commands/RemoveLayerCommand.h"
#include "commands/RenameLayerCommand.h"
#include "commands/ChangeLayerSymbolCommand.h"
#include "commands/MoveLayerCommand.h"
#include "PainterDocumentController.h"
#include "CartoScriptExtension.h"
#include "FeatureLayer.h"

#include <geodatabase/IShapeFileWorkspaceFactory.h>
#include <carto/DefaultNavigationHandler.h>
#include <display/IDisplay.h>

#include <carousel/commands/IUndoStack.h>
#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/utils/IServiceLocator.h>
#include <carousel/utils/TypeCreators.h>

static const QByteArray productName("Carto");

CartoComponent::CartoComponent()
    : BaseComponent("org.carousel.demos.Carto")
{
    IScriptExtension *scriptExtension = new CartoScriptExtension(this);
    registerExtension<IScriptExtension>(scriptExtension);

    addParent("org.carousel.JsScripting", 1, 0);
    addParent("org.carousel.demos.Display", 1, 0);
    addParent("org.carousel.demos.Geodatabase", 1, 0);
    addParent("org.carousel.demos.Geometry", 1, 0);
    setShortName("Carto");
    setProductName(productName);
    setProvider("Carousel");
    setVersion(1, 0);
}

CartoComponent::~CartoComponent()
{
}

void CartoComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IPainterDocumentController *controller = serviceLocator->unregisterInstance<IPainterDocumentController>();
    delete controller;
}

bool CartoComponent::onStartup(IServiceLocator *serviceLocator)
{
    TypeCreator<AddShapesCommand, TypeLocator<IUndoStack>, TypeLocator<IPainterDocumentController>, TypeBuilder<IShapeFileWorkspaceFactory>> addShapesCreator{serviceLocator};
    serviceLocator->registerType<AddShapesCommand>(addShapesCreator);

    TypeCreator<RemoveLayerCommand, TypeLocator<IUndoStack>, TypeLocator<IPainterDocumentController>, TypeBuilder<IShapeFileWorkspaceFactory>> removeLayerCommand{serviceLocator};
    serviceLocator->registerType<RemoveLayerCommand>(removeLayerCommand);

    TypeCreator<RenameLayerCommand, TypeLocator<IUndoStack>> renameLayerCreator{serviceLocator};
    serviceLocator->registerType<RenameLayerCommand>(renameLayerCreator);

    TypeCreator<MoveLayerCommand, TypeLocator<IUndoStack>, TypeLocator<IPainterDocumentController>> moveLayerCreator{serviceLocator};
    serviceLocator->registerType<MoveLayerCommand>(moveLayerCreator);

    TypeCreator<ChangeLayerSymbolCommand, TypeLocator<IUndoStack>, TypeLocator<IPainterDocumentController>> changeLayerSymbolCommandCreator{serviceLocator};
    serviceLocator->registerType<ChangeLayerSymbolCommand>(changeLayerSymbolCommandCreator);

    IDisplay *display = serviceLocator->locate<IDisplay>();
    IPainterDocumentController *controller = new PainterDocumentController(display);
    serviceLocator->registerInstance<IPainterDocumentController>(controller);

    // For creating from scripting
    serviceLocator->bindType<FeatureLayer, FeatureLayer>();

    DefaultNavigationHandler* defaultNavigationHandler = new DefaultNavigationHandler(display, controller, this);
    Q_UNUSED(defaultNavigationHandler)

    return true;
}

EXPORT_COMPONENT(CartoComponent)

