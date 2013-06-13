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
#include <components/undo/UndoInteractiveExtension.h>

#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QUndoStack>

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
    : BaseComponent("Undo", parent)
{
    IInteractiveExtension *interactiveExtension = new UndoInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    setShortName("Undo");
    setProductName("Undo");
    setDescription(description);
    setProvider("Carousel");
    addParent("Interactivity");
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
    QUndoStack *undoStack = serviceLocator->unregisterInstance<QUndoStack>();
    delete undoStack;
}

//------------------------------------------------------------------------------
bool UndoComponent::onStartup(IServiceLocator *serviceLocator)
{
    // QUndoStack registration
    QUndoStack *undoStack = new QUndoStack();
    serviceLocator->registerInstance<QUndoStack>(undoStack);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(UndoComponent)

//------------------------------------------------------------------------------
