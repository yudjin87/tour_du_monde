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

#include "cartoUI/SimpleRendererWidget.h"
#include "ui_SimpleRendererWidget.h"

#include <carto/SimpleRenderer.h>
#include <displayWidgets/SymbolWidgetCreator.h>
#include <displayWidgets/SymbolEditorWidget.h>

SimpleRendererWidget::SimpleRendererWidget(SimpleRenderer *renderer, QWidget *parent)
    : FeatureRendererWidget(parent)
    , m_ui(new Ui::SimpleRendererWidget())
    , m_renderer(static_cast<SimpleRenderer*>(renderer->clone()))
{
    m_ui->setupUi(this);

    SymbolWidgetCreator symbolWidgetCreator;
    SymbolEditorWidget* symbolWidget = symbolWidgetCreator.createEditorWidget(m_renderer->symbol(), this);
    symbolWidget->prepareForEmbedding();

    // install widget
    connect(symbolWidget, &SymbolEditorWidget::symbolChanged, this, &SimpleRendererWidget::onSymbolChanged);
    m_ui->horizontalLayout->insertWidget(0, symbolWidget);
    m_ui->horizontalLayout->removeWidget(m_ui->symbolWidgetPlaceholder);

    m_ui->symbolWidgetPlaceholder->setParent(nullptr);
    delete m_ui->symbolWidgetPlaceholder;
    m_ui->symbolWidgetPlaceholder = symbolWidget;
}

SimpleRendererWidget::~SimpleRendererWidget()
{
    delete m_ui;
    m_ui = nullptr;
}

void SimpleRendererWidget::applyChanges()
{
}

void SimpleRendererWidget::prepareForEmbedding()
{
    m_ui->horizontalLayout->setContentsMargins(QMargins());
}

void SimpleRendererWidget::onSymbolChanged(const ISymbol *newSymbol)
{
    m_renderer->setSymbol(newSymbol->clone());
    emit rendererChanged(m_renderer.get());
}
