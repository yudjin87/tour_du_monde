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

#include <components/undo/UndoComponent.h>
#include <components/undo/QUndoStackAdapter.h>
#include <components/undo/UndoInteractiveExtension.h>

#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("UndoComponent");
}


//------------------------------------------------------------------------------
static const QByteArray description(
        "");

//------------------------------------------------------------------------------
UndoComponent::UndoComponent(QObject *parent)
    : BaseComponent("org.carousel.Undo", parent)
{
    IInteractiveExtension *interactiveExtension = new UndoInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    setShortName("Undo");
    setProductName("Undo");
    setDescription(description);
    setProvider("Carousel");
    setVersion(1, 0);
    addParent("org.carousel.Interactivity", 1, 0);
}

//------------------------------------------------------------------------------
UndoComponent::~UndoComponent()
{
    if (started())
        Log.w("Logic error: onShutdown() was not called.");
}

//------------------------------------------------------------------------------
void UndoComponent::onShutdown(IServiceLocator *serviceLocator)
{
    QUndoStackAdapter *undoStack = serviceLocator->unregisterInstance<QUndoStackAdapter>();
    delete undoStack;
}

//------------------------------------------------------------------------------
bool UndoComponent::onStartup(IServiceLocator *serviceLocator)
{
    QUndoStackAdapter *undoStack = new QUndoStackAdapter();
    serviceLocator->registerInstance<QUndoStackAdapter>(undoStack);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(UndoComponent)

//------------------------------------------------------------------------------
