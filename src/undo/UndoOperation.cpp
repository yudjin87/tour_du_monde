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

#include "UndoOperation.h"

#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QUndoStack>

//------------------------------------------------------------------------------
UndoOperation::UndoOperation()
    : Operation("Undo")
    , m_action(nullptr)
{
    setIcon(QIcon(":/undo/images/undo.png"));
    setIconVisibleInMenu(true);
}

//------------------------------------------------------------------------------
void UndoOperation::execute()
{
    m_action->trigger();
}

//------------------------------------------------------------------------------
void UndoOperation::initialize(QObject *ip_startUpData)
{
    AbstractApplication *app = qobject_cast<AbstractApplication *>(ip_startUpData);
    if (app == nullptr)
        return;

    IServiceLocator &locator = app->serviceLocator();
    QUndoStack *stack = locator.locate<QUndoStack>();

    m_action = stack->createUndoAction(this);
    setEnabled(m_action->isEnabled());

    connect(m_action, SIGNAL(changed()), SLOT(onActionChanged()));
}

//------------------------------------------------------------------------------
void UndoOperation::onActionChanged()
{
    setEnabled(m_action->isEnabled());
}

//------------------------------------------------------------------------------
