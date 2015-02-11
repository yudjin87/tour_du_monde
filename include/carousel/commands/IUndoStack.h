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

#ifndef IUNDOSTACK_H
#define IUNDOSTACK_H

#include <carousel/carousel_global.h>
#include <QtCore/QObject>

class IUndoableCommand;

/*!
 * @details
 *   An interface for Undo Stack, compatible with QUndoStack.
 */
class CAROUSEL_API IUndoStack : public QObject
{
    Q_OBJECT
public:
    IUndoStack(QObject* parent = nullptr) : QObject(parent){}

    virtual void clear() = 0;

    virtual void push(IUndoableCommand *cmd) = 0;

    virtual bool canUndo() const = 0;
    virtual bool canRedo() const = 0;
    virtual QString undoText() const = 0;
    virtual QString redoText() const = 0;

    virtual int count() const = 0;
    virtual int index() const = 0;
    virtual QString text(int idx) const = 0;

    virtual bool isActive() const = 0;
    virtual bool isClean() const = 0;
    virtual int cleanIndex() const = 0;

    virtual void beginMacro(const QString &text) = 0;
    virtual void endMacro() = 0;

    virtual void setUndoLimit(int limit) = 0;
    virtual int undoLimit() const = 0;

    virtual const IUndoableCommand *command(int index) const = 0;

    virtual void undo() = 0;
    virtual void redo() = 0;
};

#endif // IUNDOSTACK_H
