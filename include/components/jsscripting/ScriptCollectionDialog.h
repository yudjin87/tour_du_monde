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

#ifndef SCRIPTCOLLECTIONVIEW_H
#define SCRIPTCOLLECTIONVIEW_H

#include <components/jsscripting/jsscripting_global.h>

#include <QtCore/QMap>
#include <QtWidgets/QDialog>

namespace Ui
{
class ScriptCollectionDialog;
}

class ScriptCollectionModel;
class ScriptUnitView;
class IScriptUnit;

class JSSCRIPTING_API ScriptCollectionDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * @details
     */
    explicit ScriptCollectionDialog(ScriptCollectionModel *model, QWidget *parent = nullptr);
    ~ScriptCollectionDialog();

private slots:
    void onScriptAdded(IScriptUnit *script);
    void onScriptRemoved(IScriptUnit *script);
    void onRun();
    void onSave();
    void onCurrentScriptModificationChanged(bool changed);
    void onScriptFileNameChanged();
    void onTabCloseRequested(int index);

private:
    ScriptUnitView *getCurrentView();
    void clearModifiedMark(int index);
    void setModifiedMark(int index);
    int indexByScript(IScriptUnit *script) const;
    void setActionsEnabled(bool enable);

private:
    Ui::ScriptCollectionDialog *m_ui;
    ScriptCollectionModel *m_model;
};

#endif // SCRIPTCOLLECTIONVIEW_H
