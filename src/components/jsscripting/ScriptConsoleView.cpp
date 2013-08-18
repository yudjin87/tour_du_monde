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

#include "ScriptConsoleView.h"
#include "IScriptConsole.h"
#include "ui_ScriptConsoleView.h"

#include <QtGui/QKeyEvent>
#include <QtGui/QSyntaxHighlighter>
#include <QtWidgets/QScrollBar>

//------------------------------------------------------------------------------
ScriptConsoleView::ScriptConsoleView(IScriptConsole *console, QSyntaxHighlighter *hilighter, QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::ScriptConsoleView)
    , m_console(console)
    , m_hilighter(hilighter)
{
    m_ui->setupUi(this);
    m_hilighter->setParent(m_ui->commandsList->document());
    m_hilighter->setDocument(m_ui->commandsList->document());
    connectSignalsToSlots();
}

//------------------------------------------------------------------------------
ScriptConsoleView::~ScriptConsoleView()
{
    delete m_ui;
    m_ui = nullptr;
}

//------------------------------------------------------------------------------
void ScriptConsoleView::onEnter()
{
    QString command = m_ui->commandEdit->text();
    m_ui->commandEdit->clear();
    m_console->execCommand(command);
}

//------------------------------------------------------------------------------
void ScriptConsoleView::onAboutToExecute(const QString &command)
{
    printOutput(QString(">>> %1").arg(command));

    scrollDown();
}

//------------------------------------------------------------------------------
bool ScriptConsoleView::eventFilter(QObject *sender, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        switch (key->key())
        {
        case Qt::Key_Up: onPrevCommand();
            break;
        case Qt::Key_Down: onNextCommand();
            break;
        }
    }

    // standard event processing
    return QObject::eventFilter(sender, event);
}

//------------------------------------------------------------------------------
void ScriptConsoleView::printError(const QString &error)
{
    m_ui->commandsList->setTextColor(Qt::red);
    m_ui->commandsList->insertPlainText(error + "\n");
    m_ui->commandsList->setTextColor(Qt::black);

    scrollDown();
}

//------------------------------------------------------------------------------
void ScriptConsoleView::printOutput(const QString &output)
{
    if (!output.isEmpty())
        m_ui->commandsList->insertPlainText(output + "\n");

    scrollDown();
}

//------------------------------------------------------------------------------
void ScriptConsoleView::onPrevCommand()
{
    QString prev = m_console->prevCommand();
    m_ui->commandEdit->setText(prev);
}

//------------------------------------------------------------------------------
void ScriptConsoleView::onNextCommand()
{
    QString next = m_console->nextCommand();
    m_ui->commandEdit->setText(next);
}

//------------------------------------------------------------------------------
void ScriptConsoleView::scrollDown()
{
    QScrollBar *scroll = m_ui->commandsList->verticalScrollBar();
    scroll->setValue(scroll->maximum());
}

//------------------------------------------------------------------------------
void ScriptConsoleView::connectSignalsToSlots()
{
    m_ui->commandEdit->installEventFilter(this);
    connect(m_ui->commandEdit, &QLineEdit::returnPressed, this, &ScriptConsoleView::onEnter);

    connect(m_console, &IScriptConsole::aboutToExecute, this, &ScriptConsoleView::onAboutToExecute);
    connect(m_console, &IScriptConsole::printed, this, &ScriptConsoleView::printOutput);
    connect(m_console, &IScriptConsole::error, this, &ScriptConsoleView::printError);
}

//------------------------------------------------------------------------------
