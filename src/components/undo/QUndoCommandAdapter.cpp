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

#include <components/undo/QUndoCommandAdapter.h>
#include <carousel/commands/IUndoableCommand.h>

QUndoCommandAdapter::QUndoCommandAdapter(IUndoableCommand *wrappedCmd, QObject *parent)
    : QObject(parent)
    , QUndoCommand(wrappedCmd->text())
    , m_wrappedCmd(wrappedCmd)
{
}

QUndoCommandAdapter::~QUndoCommandAdapter()
{
    delete m_wrappedCmd;
    m_wrappedCmd = nullptr;
}

const IUndoableCommand *QUndoCommandAdapter::wrapped() const
{
    return m_wrappedCmd;
}

void QUndoCommandAdapter::undo()
{
    m_wrappedCmd->undo();
}

void QUndoCommandAdapter::redo()
{
    m_wrappedCmd->redo();
}

int QUndoCommandAdapter::id() const
{
    return m_wrappedCmd->id();
}

bool QUndoCommandAdapter::mergeWith(const QUndoCommand *other)
{
    const QUndoCommandAdapter* adapter = dynamic_cast<const QUndoCommandAdapter*>(other);
    if (adapter == nullptr) {
        return false;
    }

    return m_wrappedCmd->mergeWith(adapter->wrapped());
}
