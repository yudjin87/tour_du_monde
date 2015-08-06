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

#include "CartoUIComponent.h"
#include "CartoUIInteractiveExtension.h"

#include <carto/ITourDuMondeDocument.h>
#include <carto/ITourDuMondeDocumentController.h>

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QGraphicsScene>

static const QByteArray productName("CartoUI");

CartoUIComponent::CartoUIComponent(QObject *parent /*= nullptr*/)
    : BaseComponent("org.carousel.demos.CartoUI", parent)
{
    IInteractiveExtension *interactiveExtension = new CartoUIInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    addParent("org.carousel.demos.Geodatabase", 1, 0);
    addParent("org.carousel.demos.Display", 1, 0);
    addParent("org.carousel.demos.DisplayWidgets", 1, 0);
    addParent("org.carousel.demos.Carto", 1, 0);
    setShortName("Carto UI");
    setProductName(productName);
    setProvider("Carousel");
    setVersion(1, 0);
}

CartoUIComponent::~CartoUIComponent()
{
}

bool CartoUIComponent::onStartup(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)
    return true;
}

void CartoUIComponent::onShutdown(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)
}

EXPORT_COMPONENT(CartoUIComponent)


