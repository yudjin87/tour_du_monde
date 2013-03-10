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

#ifndef COMMAND_H
#define COMMAND_H

#include "interactivity_global.h"

#include "ICommand.h"

#include <QtGui/QAction>

/*!
 * @brief
 *   Inherit this abstract class to create a commands provides user to interact
 *   with application.
 * @details
 *   One of the way of user interaction with Carousel based applications are the commands,
 *   which call application essentials.
 *   You can create the following types of commands:
 *   @li @a Buttons and @a menu @a items are the simplest types of commands.
 *   Buttons generally appear as icons on toolbars and menu items appear in menus. A simple
 *   action is performed when the button or menu item is clicked.
 *   @li @a Tools are similar to buttons but they also require interaction with the application's
 *   display. The "Zoom In" command is a good example of a tool - you click or drag a rectangle
 *   over a widget before the display is redrawn to show the widget contents in more detail.
 *
 *   When you are creating a new command, you must derived from the this class in your
 *   class code. This class determines the behavior and properties of simple commands
 *   such as buttons and menu items. For example, it declares command properties
 *   such as name, category, icon, desctiptive text that used in QAction subclass - Command
 *   and in the Customization dialog.
 *   It also defines what action happens when the command is clicked.
 *
 *   You should implement at least execute() method in the derived class.
 */
class INTERACTIVITY_API Command : public QAction, virtual public ICommand
{
    Q_OBJECT
public:
    /*!
     * @details
     *   Constructs a command with action group, if any.
     *   If the action group not null, this command
     *   will be automatically inserted into the group.
     */
    Command(QActionGroup *ip_actionGroup = nullptr);

    /*!
     * @details
     *   Constructs a command with action group, if any.
     *   If the action group not null, this command
     *   will be automatically inserted into the group.
     *
     *   The Command uses a stripped version of @a text (e.g. "&Menu Option..." becomes
     *   "Menu Option") as descriptive text for tool buttons. You can override
     *   this by setting a specific description with setText(). The same text will be
     *   used for tooltips unless you specify a different text using setToolTip().
     */
    Command(const QString &i_text, QActionGroup *ip_actionGroup = nullptr);

    /*!
     * @details
     *   Constructs a command with action group, if any.
     *   If the action group not null, this command
     *   will be automatically inserted into the group.
     *
     *   The Command uses a stripped version of @a text (e.g. "&Menu Option..." becomes
     *   "Menu Option") as descriptive text for tool buttons. You can override
     *   this by setting a specific description with setText(). The same text will be
     *   used for tooltips unless you specify a different text using setToolTip().
     */
    Command(const QIcon &i_icon, const QString &i_text, QActionGroup *ip_actionGroup = nullptr);
    ~Command();

    /*!
     * @details
     *   The name of the category with which this command is associated.
     *   It determines where the command will appear in the Commands panel
     *   of the Customize dialog.
     */
    QString category() const;

    /*!
     * @details
     *   If command is checkable, this method called after user switch off
     *   this command.
     *
     *   It is also emmits executingStopped() signal.
     */
    void stopExecuting();

    /*!
     * @details
     *   Called by carousel interactivity system to gives the command a hook into
     *   the application.
     *   When subclassing Command, use the initialize() method to get a hook to the
     *   application. When the final, complete boot loading takes place, the initialize()
     *   method gets called for every registered command.
     *
     *   Does nothing by default.
     */
    void initialize(QObject *ip_startUpData);

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
    QString name() const;

signals:
    /*!
     * @details
     *   This signal is emited when command is deactivated.
     */
    void executingStopped();

protected:
    /*!
     * @details
     *   Sets the name of the category with which this command is associated.
     *   It determines where the command will appear in the Commands panel
     *   of the Customize dialog.
     */
    void setCategory(const QString &i_category);

    /*!
     * @details
     *   Sets the programmatic identifying name string.
     *   By convention, a command's name should include its category name. The format of
     *   the @a name string should be <category>.<text>. Since it is an identifier of the
     *   command, this property should not be localized.
     *   This property used to store user's customization.
     *   @note the text() property of a command is the string that appears when the command
     *   is placed on a command bar.
     */
    void setName(const QString &i_name);

private:
    void _connectToSignals();

private slots:
    void _onTriggered(bool i_checked);
    void _onToggled(bool i_checked);

private:
    QString m_category;
    QString m_name;
};

#endif // COMMAND_H
