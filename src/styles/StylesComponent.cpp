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

#include "styles/StylesComponent.h"
#include "styles/StyleGalery.h"

#include <carousel/commands/IUndoStack.h>
#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/utils/IServiceLocator.h>
#include <carousel/utils/TypeCreators.h>

StylesComponent::StylesComponent()
    : BaseComponent("org.carousel.demos.Styles")
{
    addParent("org.carousel.demos.Carto", 1, 0);
    addParent("org.carousel.demos.CartoPersist", 1, 0);
    setShortName("Styles");
    setProductName("Styles");
    setProvider("Carousel");
    setVersion(1, 0);
}

StylesComponent::~StylesComponent()
{
}

void StylesComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IStyleGalery *galery = serviceLocator->unregisterInstance<IStyleGalery>();
    delete galery;
}

bool StylesComponent::onStartup(IServiceLocator *serviceLocator)
{
    IStyleGalery* galery = new StyleGalery();
    serviceLocator->registerInstance(galery);
//    TypeCreator<AddShapesCommand, TypeLocator<IUndoStack>, TypeLocator<ITourDuMondeDocumentController>, TypeLocator<IShapeFileWorkspaceFactory>> addShapesCreator{serviceLocator};
//    serviceLocator->registerType<AddShapesCommand>(addShapesCreator);

    return true;
}

EXPORT_COMPONENT(StylesComponent)

