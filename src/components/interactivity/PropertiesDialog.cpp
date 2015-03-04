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

#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

PropertiesDialog::PropertiesDialog(IServiceLocator *serviceLocator, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , m_isDirty(false)
    , m_ui(new Ui::PropertiesDialog())
    , m_buttonBox(new QDialogButtonBox(this))
    , m_serviceLocator(serviceLocator)
    , m_propertiesWidget(nullptr)
{
    m_ui->setupUi(this);

    m_buttonBox->setOrientation(Qt::Horizontal);
    m_buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

    m_ui->verticalLayout->addWidget(m_buttonBox);

    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &PropertiesDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &PropertiesDialog::reject);

    QPushButton* applyButton = m_buttonBox->button(QDialogButtonBox::Apply);
    connect(applyButton, &QPushButton::clicked, this, &PropertiesDialog::apply);
    applyButton->setEnabled(false);
}

PropertiesDialog::~PropertiesDialog()
{
    delete m_ui;
    m_ui = nullptr;
}

void PropertiesDialog::installCentralWidget(PropertiesWidget *propertiesWidget)
{
    Q_ASSERT(propertiesWidget != nullptr);

    propertiesWidget->setParent(this);
    m_propertiesWidget = propertiesWidget;
    m_ui->widgetPlaceholder->addWidget(propertiesWidget);

    connect(m_propertiesWidget, &PropertiesWidget::propertyChanged, this, &PropertiesDialog::onPropertyChanged);
}

void PropertiesDialog::accept()
{
    apply();
    QDialog::accept();
}

void PropertiesDialog::reject()
{
    QDialog::reject();
}

void PropertiesDialog::apply()
{
    if (m_isDirty)
    {
        m_propertiesWidget->applyChanges(m_serviceLocator);
        m_isDirty = false;
        m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
    }
}

void PropertiesDialog::onPropertyChanged()
{
    m_isDirty = true;
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}
