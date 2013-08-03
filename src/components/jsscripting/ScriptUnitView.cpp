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
#include "ScriptUnit.h"

#include <QtGui/QSyntaxHighlighter>

//------------------------------------------------------------------------------
ScriptUnitView::ScriptUnitView(ScriptUnit *data, QSyntaxHighlighter *highlighter, QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::ScriptUnitView())
    , m_data(data)
{
    m_ui->setupUi(this);
    m_ui->scriptEditor->setDocument(m_data->script());

    highlighter->setParent(this);
    highlighter->setDocument(m_data->script());
}

//------------------------------------------------------------------------------
ScriptUnitView::~ScriptUnitView()
{
    delete m_ui;
    m_ui = nullptr;
}

//------------------------------------------------------------------------------
ScriptUnit *ScriptUnitView::data()
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
