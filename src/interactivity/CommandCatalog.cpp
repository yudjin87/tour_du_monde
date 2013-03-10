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

#include "CommandCatalog.h"

#include "Command.h"

#include <QtCore/QtAlgorithms>
//------------------------------------------------------------------------------
CommandCatalog::CommandCatalog()
    : mp_startupData(nullptr)
{
}

//------------------------------------------------------------------------------
CommandCatalog::~CommandCatalog()
{
    qDeleteAll(m_commands);
}

//------------------------------------------------------------------------------
Command *CommandCatalog::add(Command *ip_newCommand)
{
    m_commands.push_back(ip_newCommand);
    ip_newCommand->initialize(mp_startupData);

    onCommandAdded(ip_newCommand);

    return ip_newCommand;
}

//------------------------------------------------------------------------------
QList<Command *> CommandCatalog::commands() const
{
    return m_commands;
}

//------------------------------------------------------------------------------
QList<Command *> CommandCatalog::commands(const QString &i_byCategory) const
{
    QList<Command *> commands;
    foreach(Command *p_command, m_commands)
        if (p_command->category() == i_byCategory)
            commands.push_back(p_command);

    return commands;
}

//------------------------------------------------------------------------------
void CommandCatalog::deleteCommand(const QString &i_name)
{
    Command *command = find(i_name);
    deleteCommand(command);
}

//------------------------------------------------------------------------------
void CommandCatalog::deleteCommand(Command *ip_command)
{
    if(m_commands.removeOne(ip_command))
        delete ip_command;
}

//------------------------------------------------------------------------------
Command *CommandCatalog::find(const QString &i_name)
{
    return const_cast<Command *>(static_cast<const CommandCatalog &>(*this).find(i_name));
}

//------------------------------------------------------------------------------
const Command *CommandCatalog::find(const QString &i_name) const
{
    foreach(Command *p_command, m_commands)
        if (p_command->name() == i_name)
            return p_command;

    return nullptr;
}

//------------------------------------------------------------------------------
void CommandCatalog::setStartupData(QObject *ip_startupData)
{
    mp_startupData = ip_startupData;
}

//------------------------------------------------------------------------------
void CommandCatalog::onCommandAdded(Command *ip_command)
{
    emit commandAdded(ip_command);
}

//------------------------------------------------------------------------------

