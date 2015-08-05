/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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
#include "cartoUI/RendererCategoryCollectionModel.h"
#include "ui_CategorizedRendererWidget.h"

#include <carto/DefaultSymbol.h>
#include <displayWidgets/SymbolWidgetCreator.h>
#include <displayWidgets/SymbolEditorWidget.h>
#include <geodatabase/IFeatureClass.h>
#include <geodatabase/ITable.h>
#include <geodatabase/IField.h>
#include <geodatabase/IFields.h>
#include <geodatabase/ColumnClassificator.h>
#include <components/interactivity/PropertiesDialog.h>
#include <components/interactivity/PropertiesWidget.h>

#include <QtWidgets/QMessageBox>

CategorizedRendererWidget::CategorizedRendererWidget(const CategorizedRenderer *renderer, FeatureLayer &layer, QWidget *parent)
    : FeatureRendererWidget(parent)
    , m_ui(new Ui::CategorizedRendererWidget())
    , m_renderer(static_cast<CategorizedRenderer*>(renderer->clone()))
    , m_tableModel(new RendererCategoryCollectionModel(m_renderer->categories(), layer.featureClass()->shapeType(), this))
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

    connect(m_ui->classifyBtn, &QPushButton::clicked, this, &CategorizedRendererWidget::onClassifyBtnClicked);
    connect(m_ui->changeBtn, &QPushButton::clicked, this, &CategorizedRendererWidget::onChangeBtnClicked);

    m_ui->columnNameCbox->setModel(m_columns.get());
    m_ui->columnNameCbox->setCurrentIndex(m_renderer->categoryFieldIndex());
    connect(m_ui->columnNameCbox, SIGNAL(currentIndexChanged(int)),this, SLOT(onCategoryColumnChanged(int)));

    m_ui->symbolTable->setModel(m_tableModel);
}

CategorizedRendererWidget::~CategorizedRendererWidget()
{
    delete m_ui;
    m_ui = nullptr;
}

void CategorizedRendererWidget::applyChanges()
{
    // TODO: what for??
}

void CategorizedRendererWidget::prepareForEmbedding()
{
    m_ui->verticalLayout->setContentsMargins(QMargins());
}

void CategorizedRendererWidget::onCategoryColumnChanged(int index)
{
    m_renderer->setCategoryFieldIndex(index);

    emit rendererChanged(m_renderer.get());
}

void CategorizedRendererWidget::onClassifyBtnClicked()
{
    const ITable* table = m_layer.featureClass()->table();
    const IFields* fields = table->fields();
    const QString selectedName = fields->field(m_ui->columnNameCbox->currentIndex())->name();

    ColumnClassificator classificator(*table);
    QStringList columnValues = classificator.classify(selectedName);
    if (columnValues.size() > 200) // someone misses the column name?
    {
        QMessageBox::StandardButton reply = QMessageBox::question(
                    this,
                    "Cassification",
                    QString("There are %1 possible categories. Are you sure you want to classify them (will take some time)?").arg(columnValues.size()),
                    QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::No)
        {
            return;
        }
    }

    for (const QString& uniqueValue : columnValues)
    {
        m_renderer->addCategory(uniqueValue, uniqueValue, StyleGallery::defaultSymbol(m_layer.shapeType()));
    }

    emit rendererChanged(m_renderer.get());
}

void CategorizedRendererWidget::onChangeBtnClicked()
{
    const QModelIndex& selectedRow = m_ui->symbolTable->selectionModel()->currentIndex();
    IRendererCategory* category = m_tableModel->category(selectedRow);
    Q_ASSERT(category != nullptr);

    SymbolWidgetCreator creator;
    SymbolEditorWidget* widget = creator.createEditorWidget(category->symbol(), nullptr);
    connect(widget, &SymbolEditorWidget::symbolChanged, this, [this, selectedRow](const ISymbol* s){onSymbolChanged(s, selectedRow);});

    PropertiesDialog dlg(this);
    dlg.installCentralWidget(widget);

    dlg.exec();
}

void CategorizedRendererWidget::onSymbolChanged(const ISymbol *symbol, const QModelIndex &selectedRow)
{
    IRendererCategory* category = m_tableModel->category(selectedRow);
    Q_ASSERT(category != nullptr);

    category->setSymbol(symbol->clone());

    emit rendererChanged(m_renderer.get());
}
