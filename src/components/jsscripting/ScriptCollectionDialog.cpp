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

#include <QtCore/QSettings>
#include <QtGui/QKeyEvent>
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

    connect(m_ui->actionNewScript, &QAction::triggered, m_model, &ScriptCollectionModel::onCreateScript);
    connect(m_ui->actionLoadScript, &QAction::triggered, m_model, &ScriptCollectionModel::onLoad);
    connect(m_ui->actionRun, &QAction::triggered, this, &ScriptCollectionDialog::onRun);
    connect(m_ui->actionSave, &QAction::triggered, this, &ScriptCollectionDialog::onSave);
    connect(m_ui->tabWidget, &QTabWidget::tabCloseRequested, this, &ScriptCollectionDialog::onTabCloseRequested);
    connect(m_model, &ScriptCollectionModel::scriptAdded, this, &ScriptCollectionDialog::onScriptAdded);

    for (IScriptUnit *script : m_model->scripts())
        onScriptAdded(script);

    QSettings settings;
    restoreGeometry(settings.value(QString(metaObject()->className()) +"/geometry").toByteArray());
}

//------------------------------------------------------------------------------
ScriptCollectionDialog::~ScriptCollectionDialog()
{
    for (int i = 0; i < m_ui->tabWidget->count(); ++i) {
        delete m_ui->tabWidget->widget(i);
    }

    delete m_ui;
    m_ui = nullptr;

    QSettings settings;
    settings.setValue(QString(metaObject()->className()) +"/geometry", saveGeometry());
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::onScriptAdded(IScriptUnit *script)
{
    ScriptUnitView *scriptView = new ScriptUnitView(script, new CodeHighlighter(ColorTheme::getDefault(), this), this);
    bool savable = !script->fileName().isEmpty();
    int index = m_ui->tabWidget->addTab(scriptView, savable
                                        ? script->fileName()
                                        : "Untitled");

    m_ui->tabWidget->setCurrentIndex(index);

    bool modified = scriptView->data()->script()->isModified();
    if (modified || !savable) // script in memory always marked as unsaved
        setModifiedMark(index);

    connect(scriptView->data()->script(), &QTextDocument::modificationChanged,
            this, &ScriptCollectionDialog::onCurrentScriptModificationChanged);

    connect(scriptView->data(), &IScriptUnit::fileNameChanged,
            this, &ScriptCollectionDialog::onScriptFileNameChanged);
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::onScriptRemoved(IScriptUnit *script)
{
    int index = indexByScript(script);
    m_ui->tabWidget->removeTab(index);
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::onRun()
{
    ScriptUnitView *scriptView = getCurrentView();
    if (scriptView == nullptr)
        return;

    scriptView->onRun();
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::onSave()
{
    ScriptUnitView *scriptView = getCurrentView();
    if (scriptView == nullptr)
        return;

    if (scriptView->onSave())
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
void ScriptCollectionDialog::onScriptFileNameChanged()
{
    IScriptUnit *script = qobject_cast<IScriptUnit *>(sender());
    int index = indexByScript(script);
    m_ui->tabWidget->setTabText(index, script->fileName());
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::onTabCloseRequested(int index)
{
    ScriptUnitView *view = qobject_cast<ScriptUnitView *>(m_ui->tabWidget->widget(index));
    m_ui->tabWidget->removeTab(index);
    m_model->onScriptRemoved(view->data());
    delete view;
}

//------------------------------------------------------------------------------
ScriptUnitView *ScriptCollectionDialog::getCurrentView()
{
    return qobject_cast<ScriptUnitView *>(m_ui->tabWidget->currentWidget());
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::clearModifiedMark(int index)
{
    QString tabTitle = m_ui->tabWidget->tabText(index);
    if (!tabTitle.endsWith("*"))
        return;

    tabTitle.remove(tabTitle.length() - 1, 1);
    m_ui->tabWidget->setTabText(index, tabTitle);
}

//------------------------------------------------------------------------------
void ScriptCollectionDialog::setModifiedMark(int index)
{
    QString tabTitle = m_ui->tabWidget->tabText(index);
    if (tabTitle.endsWith("*"))
        return;

    tabTitle.append("*");
    m_ui->tabWidget->setTabText(index, tabTitle);
}

//------------------------------------------------------------------------------
int ScriptCollectionDialog::indexByScript(IScriptUnit *script) const
{
    for (int i = 0; i < m_ui->tabWidget->count(); ++i) {
        ScriptUnitView *scriptView = qobject_cast<ScriptUnitView *>(m_ui->tabWidget->widget(i));
        if (scriptView->data() == script)
            return i;
    }

    return -1;
}

//------------------------------------------------------------------------------
