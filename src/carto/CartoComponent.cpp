/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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

#include "carto/CartoComponent.h"
#include "carto/commands/AddShapesCommand.h"
#include "carto/commands/RemoveLayerCommand.h"
#include "carto/commands/RenameLayerCommand.h"
#include "carto/commands/ChangeLayerStyleCommand.h"
#include "carto/commands/ChangeLegendClassCommand.h"
#include "carto/commands/MoveLayerCommand.h"
#include "carto/TourDuMondeDocumentController.h"
#include "carto/FeatureLayer.h"
#include "carto/CartoScriptExtension.h"
#include "carto/Map.h"
#include <geodatabase/IShapeFileWorkspaceFactory.h>
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

    addParent("org.carousel.QmlScripting", 1, 0);
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
    ITourDuMondeDocumentController *controller = serviceLocator->unregisterInstance<ITourDuMondeDocumentController>();
    delete controller;
}

bool CartoComponent::onStartup(IServiceLocator *serviceLocator)
{
    TypeCreator<AddShapesCommand, TypeLocator<IUndoStack>, TypeLocator<ITourDuMondeDocumentController>, TypeLocator<IShapeFileWorkspaceFactory>> addShapesCreator{serviceLocator};
    serviceLocator->registerType<AddShapesCommand>(addShapesCreator);

    TypeCreator<RemoveLayerCommand, TypeLocator<IUndoStack>, TypeLocator<ITourDuMondeDocumentController>> removeLayerCommand{serviceLocator};
    serviceLocator->registerType<RemoveLayerCommand>(removeLayerCommand);

    TypeCreator<RenameLayerCommand, TypeLocator<IUndoStack>> renameLayerCreator{serviceLocator};
    serviceLocator->registerType<RenameLayerCommand>(renameLayerCreator);

    TypeCreator<MoveLayerCommand, TypeLocator<IUndoStack>, TypeLocator<ITourDuMondeDocumentController>> moveLayerCreator{serviceLocator};
    serviceLocator->registerType<MoveLayerCommand>(moveLayerCreator);

    TypeCreator<ChangeLayerStyleCommand, TypeLocator<IUndoStack>, TypeLocator<ITourDuMondeDocumentController>> changeLayerSymbolCommandCreator{serviceLocator};
    serviceLocator->registerType<ChangeLayerStyleCommand>(changeLayerSymbolCommandCreator);

    TypeCreator<ChangeLegendClassCommand, TypeLocator<IUndoStack>, TypeLocator<ITourDuMondeDocumentController>> changeLegendClassCommand{serviceLocator};
    serviceLocator->registerType<ChangeLegendClassCommand>(changeLegendClassCommand);

    IDisplay *display = serviceLocator->locate<IDisplay>();
    ITourDuMondeDocumentController *controller = new TourDuMondeDocumentController(display); // TODO:  rename controller
    serviceLocator->registerInstance<ITourDuMondeDocumentController>(controller);

    TypeCreator<Map, TypeLocator<IDisplay>> mapCreator{serviceLocator};
    serviceLocator->registerType<IMap>(mapCreator);

    // For creating from scripting
    serviceLocator->bindType<FeatureLayer, FeatureLayer>();
}

EXPORT_COMPONENT(CartoComponent)

