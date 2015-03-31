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
#include <components/interactivity/Operation.h>

class QAction;

/*!
 * @brief
 *   The RedoOperation class is a wrapper for the redo action of QUndoStack.
 * @details
 *   A wrapping is needed for access undo action as Operation sub-class to show it,
 *   for example, in the customization dialog.
 */
class RedoOperation : public Operation
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{RedoOperation}.
     */
    RedoOperation();

    /*!
     * @details
     *   Calls wrapped action for redo.
     */
    void execute() override;

    /*!
     * @details
     *   Retrieves a wrapped action from the QUndoStack.
     */
    void initialize(IServiceLocator *serviceLocator) override;

private slots:
    void onActionChanged();

private:
    QAction *m_action;
};

