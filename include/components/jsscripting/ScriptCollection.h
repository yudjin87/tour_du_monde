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
#include <components/jsscripting/IScriptCollection.h>

class IScriptEngineFactory;

/*!
 * @brief
 *   It is a base implementation of the IScriptCollection interface
 * @details
 *   Usig this interface you can add scripts from files or even directories.
 *   All scripts that are loaded into application should be loaded using this
 *   interface.
 *
 *   You can get reference to the IScriptCollection using IScriptingService::scripts().
 *
 * @sa ScriptConsoleView
 */
class JSSCRIPTING_API ScriptCollection : public IScriptCollection
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{ScriptCollection} using specified @a factory to create QScriptEngine
     *   for created units.
     *
     *   It does not takes ownership for factory;
     */
    ScriptCollection(IScriptEngineFactory *factory, QObject *parent = nullptr);
    ~ScriptCollection();

    /*!
     * @details
     *   Gets all loaded scripts.
     */
    Scripts scripts() const override;

public slots:
    /*!
     * @details
     *   Creates a new script unit and adds it to the collection.
     *   Note, that it takes ownership for the created script.
     *
     * @sa scriptAdded
     */
    IScriptUnit *create() override;

    /*!
     * @details
     *   Tries to read script from the file and create a script unit,
     *   based on that script.
     *   Note, that it takes ownership for the created script.
     *
     * @sa scriptAdded
     */
    IScriptUnit *createFromFile(const QString &fileName) override;

    /*!
     * @details
     *   Removes and deallocates a @a script from the collection;
     *
     * @sa scriptRemoved
     */
    void remove(IScriptUnit *script) override;

    /*!
     * @details
     *   Tries to read all script files, ended with .js from the directory and create
     *   script units, based on that scripts.
     *   Note, that it takes ownership for the created scripts.
     *
     * @sa scriptAdded
     */
    Scripts createFromDirectory(const QString &directory) override;

    /*!
     * @details
     *   Gets script by its file name (if any);
     */
    IScriptUnit *scriptByFileName(const QString &fileName) override;

protected:
    /*!
     * @details
     *   Creates a new ScriptUnit instance using @a fileName if any.
     */
    virtual IScriptUnit *createNewScript(const QString *fileName = nullptr);

private:
    IScriptEngineFactory *m_factory;
    Scripts m_scripts;
};

