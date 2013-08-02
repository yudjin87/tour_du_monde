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

#include "ScriptManagerDialog.h"
#include "ui_ScriptManagerDialog.h"
#include "CodeHighlighter.h"
#include "ScriptUnitView.h"
#include "ScriptUnit.h"
#include "ScriptManagerModel.h"
#include "ColorTheme.h"

#include <carousel/logging/LoggerFacade.h>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptManagerDialog");
}

//------------------------------------------------------------------------------
ScriptManagerDialog::ScriptManagerDialog(ScriptManagerModel *model, QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::ScriptManagerDialog())
    , m_model(model)
{
    m_ui->setupUi(this);

    connect(m_ui->actionLoadScript, &QAction::triggered, m_model, &ScriptManagerModel::onLoad);
    connect(m_ui->actionRun, &QAction::triggered, this, &ScriptManagerDialog::onRun);
    connect(m_ui->actionSave, &QAction::triggered, this, &ScriptManagerDialog::onSave);
    connect(m_model, &ScriptManagerModel::scriptAdded, this, &ScriptManagerDialog::onScriptAdded);

    for (ScriptUnit *script : m_model->scripts())
        onScriptAdded(script);
}

//------------------------------------------------------------------------------
ScriptManagerDialog::~ScriptManagerDialog()
{
    delete m_ui;
    m_ui = nullptr;
}

//------------------------------------------------------------------------------
void ScriptManagerDialog::onScriptAdded(ScriptUnit *script)
{
    ScriptUnitView *scriptView = new ScriptUnitView(script, new CodeHighlighter(ColorTheme::getDefault(), this));
    m_ui->tabWidget->addTab(scriptView, script->fileName());
}

//------------------------------------------------------------------------------
void ScriptManagerDialog::onRun()
{
    ScriptUnitView *scriptView = static_cast<ScriptUnitView *>(m_ui->tabWidget->currentWidget());
    m_model->onRun(scriptView->data());
}

//------------------------------------------------------------------------------
void ScriptManagerDialog::onSave()
{
    ScriptUnitView *scriptView = static_cast<ScriptUnitView *>(m_ui->tabWidget->currentWidget());
    m_model->onSave(scriptView->data());
}

//------------------------------------------------------------------------------
