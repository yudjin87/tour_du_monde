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

#include "FeatureLayerPropertiesWidget.h"
#include "ui_FeatureLayerPropertiesWidget.h"
#include "cartoUI/FeatureRendererWidgetCreator.h"

#include <carto/commands/RenameLayerCommand.h>
#include <carto/commands/ChangeLayerStyleCommand.h>
#include <carto/CategorizedRenderer.h>
#include <carto/SimpleRenderer.h>
#include <carto/FeatureLayer.h>
#include <geodatabase/IFeatureClass.h>
#include <geometry/GeometryType.h>

#include <carousel/commands/GroupUndoableCommand.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtGui/QIcon>

FeatureLayerPropertiesWidget::FeatureLayerPropertiesWidget(FeatureLayer *layer, QWidget *parent)
    : PropertiesWidget(parent)
    , m_symbolCategories({"Simple symbol", "Categorized"})
    , m_ui(new Ui::FeatureLayerPropertiesWidget())
    , m_renderer(nullptr)
    , m_layer(layer)
    , m_newName(m_layer->name())
{
    m_ui->setupUi(this);

    m_ui->layerName->setText(m_newName);
    connect(m_ui->layerName, &QLineEdit::editingFinished, this, &FeatureLayerPropertiesWidget::onLayerNameEditingFinished);

    IFeatureRenderer *renderer = m_layer->renderer();
    FeatureRendererWidgetCreator creator;
    FeatureRendererWidget *rendererWidget = creator.createWidget(renderer, m_layer, this);
    installRendererWidget(rendererWidget);

    const int type = static_cast<int>(renderer->type());
    m_ui->symbolCategoryCbox->setModel(&m_symbolCategories);
    m_ui->symbolCategoryCbox->setCurrentIndex(type);
    connect(m_ui->symbolCategoryCbox, SIGNAL(currentIndexChanged(int)),this, SLOT(onSymbolCategoryChanged(int)));

    // install widget
//    rendererWidget->prepareForEmbedding();
//    connect(rendererWidget, &FeatureRendererWidget::rendererChanged, this, &FeatureLayerPropertiesWidget::onRendererChanged);

//    m_ui->rendererLayout->insertWidget(0, rendererWidget);
//    m_ui->rendererLayout->removeWidget(m_ui->rendererWidgetPlaceholder);
//    m_ui->rendererWidgetPlaceholder->setParent(nullptr);
//    delete m_ui->rendererWidgetPlaceholder;
//    m_ui->rendererWidgetPlaceholder = rendererWidget;
}

FeatureLayerPropertiesWidget::~FeatureLayerPropertiesWidget()
{
    delete m_ui;
    m_ui = nullptr;
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
    switch (index)
    {
    case 0:
        m_renderer.reset(new SimpleRenderer(m_layer->featureClass()->shapeType()));
        break;
    case 1:
        m_renderer.reset(new CategorizedRenderer());
        break;
    }

    FeatureRendererWidgetCreator creator;
    FeatureRendererWidget *rendererWidget = creator.createWidget(m_renderer.get(), m_layer,this);
    installRendererWidget(rendererWidget);

    emit propertyChanged();
}

void FeatureLayerPropertiesWidget::installRendererWidget(FeatureRendererWidget *rendererWidget)
{
    rendererWidget->prepareForEmbedding();

    // install widget
    connect(rendererWidget, &FeatureRendererWidget::rendererChanged, this, &FeatureLayerPropertiesWidget::onRendererChanged);

    m_ui->rendererLayout->insertWidget(0, rendererWidget);
    m_ui->rendererLayout->removeWidget(m_ui->rendererWidgetPlaceholder);
    m_ui->rendererWidgetPlaceholder->setParent(nullptr);
    delete m_ui->rendererWidgetPlaceholder;
    m_ui->rendererWidgetPlaceholder = rendererWidget;
}
