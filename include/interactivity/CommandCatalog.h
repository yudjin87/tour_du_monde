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

#ifndef COMMANDCATALOG_H
#define COMMANDCATALOG_H

#include "interactivity_global.h"

#include "ICommandCatalog.h"

class QObject;

/*!
 * @brief
 *   Use CommandCatalog class to adding and fetching application commands.
 * @details
 *   This class allows you to add new command that will be used
 *   in Custimozation dialog. Although you can add new commands/actions in the
 *   menus or toolbars directly, it is recomended to register all your commands
 *   in the catalog first - it's allow user to customize interface by adding
 *   your commands to the user defined toolbars.
 *
 *   Use IInteractionService::catalogs().commandCatalog() to get a reference to the command collection
 *   to add commands specific to your extensions.
 */
class INTERACTIVITY_API CommandCatalog : public ICommandCatalog
{
    Q_OBJECT
public:
    CommandCatalog();
    ~CommandCatalog();

    /*!
     * @details
     *   Adds new command to the catalog and initializes it
     *   with start up data. It takes ownership of the
     *   command.
     *
     *   This method returns specified command for the convenience.
     *   You can use returned value in the such way:
     * @code
     *   QMenu *fileMenu = menuCatalog.findMenuEverywhere(tr("File"));
     *   fileMenu->addAction(commandCatalog->add(new MyPrintCommand()));
     * @endcode
     */
    Command *add(Command *ip_newCommand);

    /*!
     * @details
     *   Returns all commands, added to the catalog.
     */
    QList<Command *> commands() const;

    /*!
     * @details
     *   Returns all commands with specified category.
     */
    QList<Command *> commands(const QString &i_byCategory) const;

    /*!
     * @details
     *   Searches for the command specified by @a i_name, removes if any
     *   from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     */
    void deleteCommand(const QString &i_name);

    /*!
     * @details
     *   Removes specified command from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     */
    void deleteCommand(Command *ip_command);

    /*!
     * @details
     *   Searches for the command specified by @a i_name. Note, that
     *   found name shold not be localized.
     *   @sa Command::name()
     * @return
     *   Found command. Null, if there are no commands with such name.
     */
    Command *find(const QString &i_name);

    /*!
     * @details
     *   Searches for the command specified by @a i_name. Note, that
     *   found name shold not be localized.
     *   @sa Command::name()
     * @return
     *   Found command. Null, if there are no commands with such name.
     */
    const Command *find(const QString &i_name) const;

    /*!
     * @details
     *   Sets the reference to the startup data commands
     *   will be initialized with.
     */
    void setStartupData(QObject *ip_startupData);

protected:
    /*!
     * @details
     *   Emits a commandAdded() signal when specified one is added to
     *   catalog.
     */
    virtual void onCommandAdded(Command *ip_command);

private:
    QList<Command *> m_commands;
    QObject *mp_startupData;
};

#endif // COMMANDCATALOG_H
