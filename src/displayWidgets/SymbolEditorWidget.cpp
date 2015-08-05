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

#include "displayWidgets/SymbolEditorWidget.h"
#include "displayWidgets/SymbolWidgetCreator.h"
#include "displayWidgets/SymbolWidget.h"
#include <display/ISymbol.h>

#include "ui_SymbolEditorWidget.h"

SymbolEditorWidget::SymbolEditorWidget(QWidget *parent)
    : PropertiesWidget(parent)
    , m_ui(new Ui::SymbolEditorWidget())
{
    m_ui->setupUi(this);
}

void SymbolEditorWidget::applyChanges(IServiceLocator *)
{
   // Q_ASSERT(false && "Implemente me!");
}

QComboBox *SymbolEditorWidget::symbolsCbox()
{
    return m_ui->symbolsCb;
}

void SymbolEditorWidget::installSymbolWidget(ISymbol *forSymbol)
{
    SymbolWidgetCreator symbolWidgetCreator;
    SymbolWidget* symbolWidget = symbolWidgetCreator.createWidget(forSymbol, this);
    symbolWidget->initializeSample();
    symbolWidget->prepareForEmbedding();

    connect(symbolWidget, &SymbolWidget::symbolChanged, this, &SymbolEditorWidget::symbolChanged);
    connect(symbolWidget, &SymbolWidget::symbolChanged, this, &SymbolEditorWidget::propertyChanged);

    m_ui->verticalLayout->removeWidget(m_ui->placeholder);
    m_ui->verticalLayout->addWidget(symbolWidget);
    m_ui->placeholder->setParent(nullptr);
    delete m_ui->placeholder;
    m_ui->placeholder = symbolWidget;
}

SymbolEditorWidget::~SymbolEditorWidget()
{
    delete m_ui;
    m_ui = nullptr;
}

void SymbolEditorWidget::prepareForEmbedding()
{
    m_ui->verticalLayout->setContentsMargins(QMargins());
}
