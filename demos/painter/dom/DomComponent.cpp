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

#include "DomComponent.h"
#include "PainterDocumentController.h"

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/ComponentExport.h>
#include <utils/IServiceLocator.h>

//------------------------------------------------------------------------------
static const QByteArray productName("Dom");

//------------------------------------------------------------------------------
DomComponent::DomComponent()
    : BaseComponent("Dom")
    , mp_docController(nullptr)
{
    addParent("Display");
    addParent("Carto");
    setProductName(productName);
    setProvider("Carousel");
}

//------------------------------------------------------------------------------
DomComponent::~DomComponent()
{

}

//------------------------------------------------------------------------------
void DomComponent::onShutdown()
{
    if (mp_docController == nullptr)
        qWarning("Logic error: onStartup() should be called before onShutdown().");

    delete m_serviceLocator->unregisterInstance<IPainterDocumentController>();
    mp_docController = nullptr;
}

//------------------------------------------------------------------------------
bool DomComponent::onStartup(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
    if (m_serviceLocator == nullptr)
        return false;

    mp_docController = new PainterDocumentController();
    m_serviceLocator->registerInstance<IPainterDocumentController>(mp_docController);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(DomComponent)

//------------------------------------------------------------------------------
