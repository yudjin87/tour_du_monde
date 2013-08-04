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

#ifndef SCRIPTMANAGERVIEW_H
#define SCRIPTMANAGERVIEW_H

#include <components/jsscripting/jsscripting_global.h>

#include <QtCore/QMap>
#include <QtWidgets/QDialog>

namespace Ui
{
class ScriptManagerDialog;
}

class ScriptManagerModel;
class ScriptUnitView;
class IScriptUnit;

class JSSCRIPTING_API ScriptManagerDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * @details
     */
    explicit ScriptManagerDialog(ScriptManagerModel *model, QWidget *parent = nullptr);
    ~ScriptManagerDialog();

private slots:
    void onScriptAdded(IScriptUnit *script);
    void onRun();
    void onSave();
    void onCurrentScriptModificationChanged(bool changed);

private:
    ScriptUnitView *getCurrentView();
    void clearModifiedMark(int index);
    void setModifiedMark(int index);

private:
    Ui::ScriptManagerDialog *m_ui;
    ScriptManagerModel *m_model;
    QMap<int, ScriptUnitView *> m_tabs;
};

#endif // SCRIPTMANAGERVIEW_H
