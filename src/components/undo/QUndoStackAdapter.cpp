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

#include <components/undo/QUndoStackAdapter.h>
#include <components/undo/QUndoCommandAdapter.h>
#include <carousel/commands/IUndoableCommand.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QUndoStack>

#include <carousel/logging/LoggerFacade.h>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("UndoStackAdapter");
}

QUndoStackAdapter::QUndoStackAdapter(QObject *parent)
    : IUndoStack(parent)
    , m_stack(new QUndoStack(this))
{
}

QUndoStack *QUndoStackAdapter::wrappedStack()
{
    return m_stack;
}

const QUndoStack *QUndoStackAdapter::wrappedStack() const
{
    return m_stack;
}

void QUndoStackAdapter::clear()
{
    m_stack->clear();
}

void QUndoStackAdapter::push(IUndoableCommand *cmd)
{
    if (cmd->childCount() == 0)
    {
        Log.d("Executing simple operation");
        QUndoCommandAdapter* adapter = new QUndoCommandAdapter(cmd);
        m_stack->push(adapter);
        return;
    }

    // prepare grouped operation
    QUndoCommand* groupOperation = new QUndoCommand(cmd->text());
    Log.d(QString("Executing group operation (%1)").arg(cmd->childCount()));
    for (int i = 0; i < cmd->childCount(); ++i)
    {
        IUndoableCommand *child = cmd->child(i);
        QUndoCommandAdapter* childAdapter = new QUndoCommandAdapter(child, groupOperation);
        Q_UNUSED(childAdapter);
    }

    m_stack->push(groupOperation);
}

bool QUndoStackAdapter::canUndo() const
{
    return m_stack->canUndo();
}

bool QUndoStackAdapter::canRedo() const
{
    return m_stack->canRedo();
}

QString QUndoStackAdapter::undoText() const
{
    return m_stack->undoText();
}

QString QUndoStackAdapter::redoText() const
{
    return m_stack->redoText();
}

int QUndoStackAdapter::count() const
{
    return m_stack->count();
}

int QUndoStackAdapter::index() const
{
    return m_stack->index();
}

QString QUndoStackAdapter::text(int idx) const
{
    return m_stack->text(idx);
}

bool QUndoStackAdapter::isActive() const
{
    return m_stack->isActive();
}

bool QUndoStackAdapter::isClean() const
{
    return m_stack->isClean();
}

int QUndoStackAdapter::cleanIndex() const
{
    return m_stack->cleanIndex();
}

void QUndoStackAdapter::setClean()
{
    m_stack->setClean();
}

void QUndoStackAdapter::beginMacro(const QString &text)
{
    m_stack->beginMacro(text);
}

void QUndoStackAdapter::endMacro()
{
    m_stack->endMacro();
}

void QUndoStackAdapter::setUndoLimit(int limit)
{
    m_stack->setUndoLimit(limit);
}

int QUndoStackAdapter::undoLimit() const
{
    return m_stack->undoLimit();
}

const IUndoableCommand *QUndoStackAdapter::command(int index) const
{
    const QUndoCommandAdapter* adapter = dynamic_cast<const QUndoCommandAdapter*>(m_stack->command(index));
    if (adapter == nullptr) {
        return nullptr;
    }

    return adapter->wrapped();
}

void QUndoStackAdapter::undo()
{
    m_stack->undo();
}

void QUndoStackAdapter::redo()
{
    m_stack->redo();
}
