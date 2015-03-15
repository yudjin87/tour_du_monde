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

#include "ComponentsDialog.h"
#include "ui_ComponentsDialog.h"

#include "ComponentDefinitionsModel.h"

#include <QtCore/QSortFilterProxyModel>
#include <QtWidgets/QTableView>

ComponentsDialog::ComponentsDialog(ComponentDefinitionsModel *model, QWidget *parent)
    : QDialog(parent)
    , m_model(model)
    , m_ui(new Ui::ComponentsDialog())
{
    QSortFilterProxyModel *filterModel = new QSortFilterProxyModel(this);
    filterModel->setSourceModel(m_model);

    m_ui->setupUi(this);
    m_ui->tableView->setModel(filterModel);
    m_ui->tableView->selectRow(0);
    m_ui->tableView->resizeColumnsToContents();

    connect(m_ui->closeButton, &QPushButton::clicked, this, &ComponentsDialog::close);
    connect(m_ui->installButton, &QPushButton::clicked, m_model, &ComponentDefinitionsModel::onInstall);
}

ComponentsDialog::~ComponentsDialog()
{
    delete m_ui;
    m_ui = nullptr;
}

