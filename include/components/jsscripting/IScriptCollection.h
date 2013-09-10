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

#ifndef ISCRIPTCOLLECTION_H
#define ISCRIPTCOLLECTION_H

#include <components/jsscripting/jsscripting_global.h>

#include <QtCore/QObject>
#include <QtCore/QList>

class IScriptUnit;

/*!
 * @brief
 *   This abstract class provides methods for the script manipulations.
 * @details
 *   Usig this interface you can add scripts from files or even directories.
 *   All scripts that are loaded into application should be loaded using this
 *   interface.
 *
 *   You can get reference to the IScriptCollection using IScriptingService::scripts().
 *
 * @sa ScriptConsoleView
 */
class JSSCRIPTING_API IScriptCollection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<IScriptUnit *> scripts READ scripts)
public:
    /*!
     * @details
     *   A script unit collection.
     */
    typedef QList<IScriptUnit *> Scripts;

public:
    /*!
     * @details
     * @constructor{IScriptCollection}.
     */
    IScriptCollection(){}

    /*!
     * @details
     *   Gets all loaded scripts.
     */
    virtual Scripts scripts() const = 0;

public slots:
    /*!
     * @details
     *   Creates a new script unit and adds it to the collection.
     *   Note, that it takes ownership for the created script.
     *
     * @sa scriptAdded
     */
    virtual IScriptUnit *create() = 0;

    /*!
     * @details
     *   Tries to read script from the file and create a script unit,
     *   based on that script.
     *   Note, that it takes ownership for the created script.
     *
     * @sa scriptAdded
     */
    virtual IScriptUnit *createFromFile(const QString &fileName) = 0;

    /*!
     * @details
     *   Removes and deallocates a @a script from the collection;
     *
     * @sa scriptRemoved
     */
    virtual void remove(IScriptUnit *script) = 0;

    /*!
     * @details
     *   Tries to read all script files, ended with .js from the directory and create
     *   script units, based on that scripts.
     *   Note, that it takes ownership for the created scripts.
     *
     * @sa scriptAdded
     */
    virtual Scripts createFromDirectory(const QString &directory) = 0;

    /*!
     * @details
     *   Gets script by its file name (if any);
     */
    virtual IScriptUnit *scriptByFileName(const QString &fileName) = 0;

signals:
    /*!
     * @details
     *   This signal is emitted when a @a script is added to the collection.
     * @sa createFromDirectory, createFromFile, create
     */
    void scriptAdded(IScriptUnit *script);

    /*!
     * @details
     *   This signal is emitted when a @a script is removed from the collection.
     * @sa remove
     */
    void scriptRemoved(IScriptUnit *script);

private:
    Q_DISABLE_COPY(IScriptCollection)
};

#endif // ISCRIPTCOLLECTION_H
