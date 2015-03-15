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

#include <components/undo/UndoOperation.h>
#include <components/undo/QUndoStackAdapter.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QUndoStack>

UndoOperation::UndoOperation()
    : Operation("Undo")
    , m_action(nullptr)
{
    setIcon(QIcon(":/undo/images/undo.png"));
    setIconVisibleInMenu(true);
    setShortcut(QKeySequence("Ctrl+Z"));
}

void UndoOperation::execute()
{
    m_action->trigger();
}

void UndoOperation::initialize(IServiceLocator *serviceLocator)
{
    QUndoStackAdapter* adapter = serviceLocator->locate<QUndoStackAdapter>();
    QUndoStack *stack = adapter->wrappedStack();

    m_action = stack->createUndoAction(this);
    setEnabled(m_action->isEnabled());

    connect(m_action, &QAction::changed, this, &UndoOperation::onActionChanged);
}

void UndoOperation::onActionChanged()
{
    setEnabled(m_action->isEnabled());
    setText(m_action->text());
}


