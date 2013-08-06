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

#ifndef SCRIPTMANAGERMODEL_H
#define SCRIPTMANAGERMODEL_H

#include <components/jsscripting/jsscripting_global.h>
#include <components/jsscripting/IScriptManager.h>

#include <QtCore/QObject>

class IServiceLocator;
class IScriptUnit;
class IScriptManager;

class JSSCRIPTING_API ScriptManagerModel : public QObject
{
    Q_OBJECT
public:
    /*!
     * @details
     *   Does not takes ownership
     */
    explicit ScriptManagerModel(IScriptManager *data, QObject *parent = nullptr);
    ~ScriptManagerModel();

    void injectServiceLocator(IServiceLocator *locator);

    IScriptManager::Scripts scripts() const;

public slots:
    void onLoad();
    void onSave(IScriptUnit *script);
    void onSaveAll();
    bool onRun(IScriptUnit *script, QString *output = nullptr);

signals:
    void scriptAdded(IScriptUnit *script);
    void scriptRemoved(IScriptUnit *script);

private:
    IScriptManager *m_data;
    IServiceLocator *m_locator;
};

#endif // SCRIPTMANAGERMODEL_H
