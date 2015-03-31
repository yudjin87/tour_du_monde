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

#pragma once
#include <carousel/commands/IUndoStack.h>
#include <components/undo/undo_global.h>

class QUndoStack;

class QUndoStackAdapter : public IUndoStack
{
    Q_OBJECT
public:
    QUndoStackAdapter(QObject* parent = nullptr);

    QUndoStack* wrappedStack();
    const QUndoStack* wrappedStack() const;

    void clear() override;

    void push(IUndoableCommand *cmd) override;

    bool canUndo() const override;
    bool canRedo() const override;
    QString undoText() const override;
    QString redoText() const override;

    int count() const override;
    int index() const override;
    QString text(int idx) const override;

    bool isActive() const override;
    bool isClean() const override;
    int cleanIndex() const override;
    void setClean() override;

    void beginMacro(const QString &text) override;
    void endMacro() override;

    void setUndoLimit(int limit) override;
    int undoLimit() const override;

    const IUndoableCommand *command(int index) const override;

    void undo() override;
    void redo() override;

private:
    QUndoStack *m_stack;
};


