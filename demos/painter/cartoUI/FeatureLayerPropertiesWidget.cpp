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

#include "FeatureLayerPropertiesWidget.h"
#include "ui_FeatureLayerPropertiesWidget.h"
#include "cartoUI/FeatureRendererWidgetCreator.h"

#include <carto/commands/RenameLayerCommand.h>
#include <carto/commands/ChangeLayerStyleCommand.h>
#include <carto/IFeatureRenderer.h>
#include <carto/FeatureLayer.h>

#include <carousel/commands/GroupUndoableCommand.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtGui/QIcon>

FeatureLayerPropertiesWidget::FeatureLayerPropertiesWidget(FeatureLayer *layer, QWidget *parent)
    : PropertiesWidget(parent)
    , m_symbolCategories({"Simple symbol", "Unique value symbols"})
    , m_ui(new Ui::FeatureLayerPropertiesWidget())
    , m_renderer(nullptr)
    , m_layer(layer)
    , m_newName(m_layer->name())
{
    m_ui->setupUi(this);

    m_ui->symbolCategoryCbox->setModel(&m_symbolCategories);
    connect(m_ui->symbolCategoryCbox, SIGNAL(currentIndexChanged(int)),this, SLOT(onSymbolCategoryChanged(int)));

    m_ui->layerName->setText(m_newName);
    connect(m_ui->layerName, &QLineEdit::editingFinished, this, &FeatureLayerPropertiesWidget::onLayerNameEditingFinished);

    IFeatureRenderer *renderer = m_layer->renderer();
    FeatureRendererWidgetCreator creator;
    FeatureRendererWidget *rendererWidget = creator.createWidget(renderer, this);

    // install widget
    connect(rendererWidget, &FeatureRendererWidget::rendererChanged, this, &FeatureLayerPropertiesWidget::onRendererChanged);

    m_ui->rendererLayout->removeWidget(m_ui->rendererWidgetPlaceholder);
    m_ui->rendererLayout->addWidget(rendererWidget);
    m_ui->rendererWidgetPlaceholder->setParent(nullptr);
    delete m_ui->rendererWidgetPlaceholder;
    m_ui->rendererWidgetPlaceholder = rendererWidget;
}

FeatureLayerPropertiesWidget::~FeatureLayerPropertiesWidget()
{
    delete m_ui;
}

void FeatureLayerPropertiesWidget::applyChanges(IServiceLocator *serviceLocator)
{
    GroupUndoableCommand* group = serviceLocator->buildInstance<GroupUndoableCommand>();
    group->setText("changing layer properties");
    if (m_newName != m_layer->name())
    {
        RenameLayerCommand* cmd = serviceLocator->buildInstance<RenameLayerCommand>();
        cmd->setLayer(m_layer);
        cmd->setNewName(m_newName);
        group->addChild(cmd);
    }

    if (m_renderer != nullptr)
    {
        ChangeLayerStyleCommand* cmd = serviceLocator->buildInstance<ChangeLayerStyleCommand>();
        cmd->setLayer(m_layer);
        cmd->setNewRenderer(m_renderer.get());
        group->addChild(cmd);
    }

    group->pushToStack();
}

void FeatureLayerPropertiesWidget::onRendererChanged(const IFeatureRenderer *renderer)
{
    m_renderer.reset(renderer->clone());
    emit propertyChanged();
}

void FeatureLayerPropertiesWidget::onLayerNameEditingFinished()
{
    if (m_layer->name() == m_ui->layerName->text())
    {
        return;
    }

    m_newName = m_ui->layerName->text();
    emit propertyChanged();
}

void FeatureLayerPropertiesWidget::onSymbolCategoryChanged(int index)
{

}
