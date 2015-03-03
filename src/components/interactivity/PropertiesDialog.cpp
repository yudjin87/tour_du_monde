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

#include "components/interactivity/PropertiesDialog.h"
#include "components/interactivity/PropertiesWidget.h"
#include "ui_PropertiesDialog.h"

PropertiesDialog::PropertiesDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , m_ui(new Ui::PropertiesDialog())
    , m_propertiesWidget(nullptr)
{
    m_ui->setupUi(this);
    this->setModal(true);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

PropertiesDialog::~PropertiesDialog()
{
    delete m_ui;
    m_ui = nullptr;
}

void PropertiesDialog::installCentralWidget(PropertiesWidget *propertiesWidget)
{
    propertiesWidget->setParent(this);
    m_propertiesWidget = propertiesWidget;
    m_ui->widgetPlaceholder->addWidget(propertiesWidget);
}
