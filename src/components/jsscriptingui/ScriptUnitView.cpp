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

#include "ScriptUnitView.h"
#include "ui_ScriptUnitView.h"

#include <components/jsscripting/IScriptUnit.h>

#include <QtGui/QKeyEvent>
#include <QtGui/QSyntaxHighlighter>
#include <QtWidgets/QFileDialog>

//------------------------------------------------------------------------------
ScriptUnitView::ScriptUnitView(IScriptUnit *data, QSyntaxHighlighter *highlighter, QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::ScriptUnitView())
    , m_data(data)
{
    m_ui->setupUi(this);
    m_ui->scriptEditor->setDocument(m_data->script());
    m_ui->scriptEditor->installEventFilter(this);

    highlighter->setParent(this);
    highlighter->setDocument(m_data->script());

    // TODO: merge the same functionality with Console view
    connect(data, &IScriptUnit::printed, this, &ScriptUnitView::printOutput);
    connect(data, &IScriptUnit::error, this, &ScriptUnitView::printError);
    connect(data, &IScriptUnit::aborted, this, &ScriptUnitView::onAborted);
}

//------------------------------------------------------------------------------
ScriptUnitView::~ScriptUnitView()
{
    delete m_ui;
    m_ui = nullptr;
}

//------------------------------------------------------------------------------
IScriptUnit *ScriptUnitView::data()
{
    return m_data;
}

//------------------------------------------------------------------------------
void ScriptUnitView::clear()
{
    m_ui->outputEditor->clear();
}

//------------------------------------------------------------------------------
void ScriptUnitView::printError(const QString &error)
{
    // TODO: merge same functional with Console View
    m_ui->outputEditor->setTextColor(Qt::red);
    m_ui->outputEditor->append(error);
    m_ui->outputEditor->setTextColor(Qt::black);
}

//------------------------------------------------------------------------------
void ScriptUnitView::printOutput(const QString &output)
{
    m_ui->outputEditor->append(output);
}

//------------------------------------------------------------------------------
void ScriptUnitView::onAbort()
{
    m_data->abort();
}

//------------------------------------------------------------------------------
void ScriptUnitView::onRun()
{
    clear();
    m_data->run();
}

//------------------------------------------------------------------------------
bool ScriptUnitView::onSave()
{
    // for saveAs:
    if (m_data->fileName().isEmpty()) {
        QFileDialog fileDialog(parentWidget(), "Save script");
        fileDialog.setNameFilter("JavaScript Files (*.js)");
        fileDialog.setFileMode(QFileDialog::AnyFile);
        fileDialog.setDefaultSuffix("js");
        fileDialog.setDirectory(QCoreApplication::applicationDirPath() + "/scripts");  // TODO: get last selected directory from settings
        if (!fileDialog.exec())
            return false;

        QString fileName = fileDialog.selectedFiles().first();
        return m_data->saveAs(fileName);
    }

    return m_data->save();
}

//------------------------------------------------------------------------------
bool ScriptUnitView::eventFilter(QObject *sender, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        if (onKeyPressed(key))
            return true;
    }

    // standard event processing
    return QObject::eventFilter(sender, event);
}

//------------------------------------------------------------------------------
bool ScriptUnitView::onKeyPressed(QKeyEvent *event)
{
    int key = event->key();
    if (event->modifiers().testFlag(Qt::ControlModifier) && processControlKey(key)) {
        event->accept();
        return true;
    }

    if (key == Qt::Key_Tab) {
        insertIndent();
        event->accept();
        return true;
    }

    return false;
}

//------------------------------------------------------------------------------
bool ScriptUnitView::processControlKey(int key)
{
    switch (key) {
    case Qt::Key_Space:
        //start completition
        return true;

    default:
        break;
    }

    return false;
}

//------------------------------------------------------------------------------
void ScriptUnitView::insertIndent()
{
    static const int indent_size = 4;
    int position = indent_size - m_ui->scriptEditor->textCursor().positionInBlock() % indent_size;
    if (position == 0)
        position = indent_size;

    m_ui->scriptEditor->insertPlainText(QString(position, ' '));
}

//------------------------------------------------------------------------------
void ScriptUnitView::onAborted()
{
    printError("Aborted by user...");
}

//------------------------------------------------------------------------------
