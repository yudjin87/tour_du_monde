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

#include "ScriptCollectionDialog.h"
#include "ui_ScriptCollectionDialog.h"
#include "CodeHighlighter.h"
#include "ScriptUnitView.h"
#include "IScriptUnit.h"
#include "ScriptCollectionModel.h"
#include "ColorTheme.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtGui/QTextDocument>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptCollectionDialog");
}

//------------------------------------------------------------------------------
ScriptCollectionDialog::ScriptCollectionDialog(ScriptCollectionModel *model, QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::ScriptCollectionDialog())
    , m_model(model)
{
    m_ui->setupUi(this);

    connect(m_ui->actionLoadScript, &QAction::triggered, m_model, &ScriptCollectionModel::onLoad);
    connect(m_ui->actionRun, &QAction::triggered, this, &ScriptCollectionDialog::onRun);
    connect(m_ui->actionSave, &QAction::triggered, this, &ScriptCollectionDialog::onSave);
    connect(m_model, &ScriptCollectionModel::scriptAdded, this, &ScriptCollectionDialog::onScriptAdded);

    for (IScriptUnit *script : m_model->scripts())
        onScriptAdded(script);
}

//------------------------------------------------------------------------------
ScriptCollectionDialog::~ScriptCollectionDialog()
{
    // Skip document signals
    for (ScriptUnitView *scriptView : m_tabs)
        scriptView->data()->script()->disconnect(this);

    delete m_ui;
    m_ui = nullptr;
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::onScriptAdded(IScriptUnit *script)
{
    ScriptUnitView *scriptView = new ScriptUnitView(script, new CodeHighlighter(ColorTheme::getDefault(), this));
    int index = m_ui->tabWidget->addTab(scriptView, script->fileName());
    m_tabs.insert(index, scriptView);

    bool modified = scriptView->data()->script()->isModified();
    if (modified)
        setModifiedMark(index);

    connect(scriptView->data()->script(), &QTextDocument::modificationChanged,
            this, &ScriptCollectionDialog::onCurrentScriptModificationChanged);
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::onScriptRemoved(IScriptUnit *script)
{
    ScriptUnitView *view = getView(script);
    int index = m_tabs.key(view);
    m_ui->tabWidget->removeTab(index);
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::onRun()
{
    ScriptUnitView *scriptView = getCurrentView();
    if (scriptView == nullptr)
        return;

    // TODO: scrip should run itself
    scriptView->clear();

    QString output;
    bool error = m_model->onRun(scriptView->data(), &output);

    // TODO: merge the same functionality with Console view
    if (output.isEmpty())
        return;

    if (error)
        scriptView->printError(output);
    else
        scriptView->printOutput(output);

    scriptView->printOutput("\n");
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::onSave()
{
    ScriptUnitView *scriptView = getCurrentView();
    if (scriptView == nullptr)
        return;

    m_model->onSave(scriptView->data());
    clearModifiedMark(m_ui->tabWidget->currentIndex());
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::onCurrentScriptModificationChanged(bool changed)
{
    if (changed)
        setModifiedMark(m_ui->tabWidget->currentIndex());
    else
        clearModifiedMark(m_ui->tabWidget->currentIndex());
}

//------------------------------------------------------------------------------
ScriptUnitView *ScriptCollectionDialog::getCurrentView()
{
    int index = m_ui->tabWidget->currentIndex();
    if (!m_tabs.contains(index))
        return nullptr;

    return m_tabs[m_ui->tabWidget->currentIndex()];
}

//------------------------------------------------------------------------------
ScriptUnitView *ScriptCollectionDialog::getView(IScriptUnit *script)
{
    for (ScriptUnitView *scriptView : m_tabs)
        if (scriptView->data() == script)
            return scriptView;

    return nullptr;
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::clearModifiedMark(int index)
{
    if (!m_tabs.contains(index))
        return;

    QString tabTitle = m_ui->tabWidget->tabText(index);
    if (!tabTitle.endsWith("*"))
        return;

    tabTitle.remove(tabTitle.length() - 1, 1);
    m_ui->tabWidget->setTabText(index, tabTitle);
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::setModifiedMark(int index)
{
    if (!m_tabs.contains(index))
        return;

    QString tabTitle = m_ui->tabWidget->tabText(index);
    if (tabTitle.endsWith("*"))
        return;

    tabTitle.append("*");
    m_ui->tabWidget->setTabText(index, tabTitle);
}

//------------------------------------------------------------------------------