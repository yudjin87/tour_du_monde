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

#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "interactivity_global.h"

#include <QtCore/QString>

class QObject;

/*!
 * @brief
 *   This interface describes a simple command that user interact with to
 *   work with application.
 * @details
 *   Use Command instead of directly implementation of this interface - it
 *   is just a contract.
 */
class INTERACTIVITY_API ICommand
{
public:
    ICommand(){}
    virtual ~ICommand(){}

    /*!
     * @details
     *   Called when this command is activated by user (button/menu is clicked,
     *   or shortkey pressed).
     *   Write the code that performs the action when the command is clicked in this method.
     */
    virtual void execute() = 0;

    /*!
     * @details
     *   The name of the category with which this command is associated.
     *   It determines where the command will appear in the Commands panel
     *   of the Customize dialog.
     */
    virtual QString category() const = 0;

    /*!
     * @details
     *   If command is checkable, this method called after user switch off
     *   this command.
     *
     *   Does nothing by default.
     */
    virtual void stopExecuting() = 0;

    /*!
     * @details
     *   Called by carousel interactivity system to gives the command a hook into
     *   the application.
     *   When subclassing ICommand, use the initialize() method to get a hook to the
     *   application. When the final, complete boot loading takes place, the initialize()
     *   method gets called for every registered command.
     *
     *   Does nothing by default.
     */
    virtual void initialize(QObject *ip_startUpData) = 0;

    /*!
     * @details
     *   This property of a command is a programmatic identifying name string.
     *   By convention, a command's name should include its category name. The format of
     *   the @a name string should be <category>.<text>. Since it is an identifier of the
     *   command, this property should not be localized.
     *   This property used to store user's customization.
     *   @note the text() property of a command is the string that appears when the command
     *   is placed on a command bar.
     */
    virtual QString name() const = 0;

    /*!
     * @details
     *   This signal is emited when command is deactivated.
     */
    virtual void executingStopped() = 0;

private:
    Q_DISABLE_COPY(ICommand)
};

#endif // ICOMMAND_H
