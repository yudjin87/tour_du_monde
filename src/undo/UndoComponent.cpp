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

#include "UndoComponent.h"
#include "UndoInteractiveExtension.h"

#include <componentsystem/ComponentExport.h>
#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QUndoStack>

//------------------------------------------------------------------------------
static const QByteArray description(
        "");

//------------------------------------------------------------------------------
UndoComponent::UndoComponent(QObject *parent)
    : BaseComponent("Undo", parent)
    , m_undoStack(nullptr)
{
    IInteractiveExtension *interactiveExtension = new UndoInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    setProductName("Undo");
    setDescription(description);
    setProvider("Carousel");
    addParent("Interactivity");
}

//------------------------------------------------------------------------------
UndoComponent::~UndoComponent()
{
    if (started())
        qWarning("Logic error: onShutdown() was not called.");
}

//------------------------------------------------------------------------------
void UndoComponent::onShutdown()
{
    // TODO:
    // Unregister them before deletion!

    delete m_undoStack;
    m_undoStack = nullptr;
}

//------------------------------------------------------------------------------
bool UndoComponent::onStartup(QObject *initData)
{
    if (initData == nullptr)
        return false;

    AbstractApplication *app = dynamic_cast<AbstractApplication *>(initData);
    if (app == nullptr)
        return false;

    IServiceLocator &locator = app->serviceLocator();

    // QUndoStack registration
    m_undoStack = new QUndoStack();
    locator.registerInstance<QUndoStack>(m_undoStack);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(UndoComponent)

//------------------------------------------------------------------------------
