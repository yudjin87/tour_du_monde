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

#include "cartoPersist/CartoPersistComponent.h"
#include "cartoPersist/CartoPersistExtension.h"

#include <carto/PainterDocumentController.h>
#include <carto/FeatureLayer.h>

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>

static const QByteArray productName("CartoPersist");

CartoPersistComponent::CartoPersistComponent()
    : BaseComponent("org.carousel.demos.CartoPersist")
{
    IPersistExtension *persistExtension = new CartoPersistExtension(this);
    registerExtension<IPersistExtension>(persistExtension);

    addParent("org.carousel.Persistence", 1, 0);
    addParent("org.carousel.demos.Carto", 1, 0);
    setShortName("CartoPersist");
    setProductName(productName);
    setProvider("Carousel");
    setVersion(1, 0);
}

CartoPersistComponent::~CartoPersistComponent()
{
}

void CartoPersistComponent::onShutdown(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)
}

bool CartoPersistComponent::onStartup(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)

    return true;
}

EXPORT_COMPONENT(CartoPersistComponent)

