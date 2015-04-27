/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include "cartoUI/CategorizedRendererWidget.h"
#include "ui_CategorizedRendererWidget.h"

#include <geodatabase/IFeatureClass.h>
#include <geodatabase/ITable.h>
#include <geodatabase/IField.h>
#include <geodatabase/IFields.h>

CategorizedRendererWidget::CategorizedRendererWidget(const CategorizedRenderer *renderer, const FeatureLayer &layer, QWidget *parent)
    : FeatureRendererWidget(parent)
    , m_ui(new Ui::CategorizedRendererWidget())
    , m_renderer(static_cast<CategorizedRenderer*>(renderer->clone()))
    , m_columns(nullptr)
    , m_layer(layer)
{
    const ITable* table = layer.featureClass()->table();
    Q_ASSERT(table != nullptr);
    const IFields* fields = table->fields();
    QStringList columns;
    for (const IField* field : *fields)
    {
        columns.push_back(field->name());
    }

    m_columns.reset(new QStringListModel(columns));
    m_ui->setupUi(this);
    m_ui->columnNameCbox->setModel(m_columns.get());
}

CategorizedRendererWidget::~CategorizedRendererWidget()
{
    delete m_ui;
    m_ui = nullptr;
}

void CategorizedRendererWidget::applyChanges()
{
}

void CategorizedRendererWidget::prepareForEmbedding()
{
    m_ui->verticalLayout->setContentsMargins(QMargins());
}
