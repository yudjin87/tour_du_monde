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

#include "components/persistenceui/PersistenceUIComponent.h"
#include "components/persistenceui/PersistenceUIInteractiveExtension.h"

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>

PersistenceUIComponent::PersistenceUIComponent()
    : BaseComponent("org.carousel.PersistenceUI")
{
    IInteractiveExtension *interactiveExtension = new PersistenceUIInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    addParent("org.carousel.Persistence", 1, 0);
    addParent("org.carousel.Interactivity", 1, 0);
    setShortName("PersistenceUI");
    setProductName("PersistenceUI");
    setProvider("Carousel");
    setVersion(1, 0);
}

PersistenceUIComponent::~PersistenceUIComponent()
{
}

void PersistenceUIComponent::onShutdown(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)
}

bool PersistenceUIComponent::onStartup(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)

    return true;
}

EXPORT_COMPONENT(PersistenceUIComponent)
