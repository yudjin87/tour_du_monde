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

#pragma once
#include <components/interactivity/PropertiesWidget.h>
#include <geometry/GeometryType.h>
#include <QtCore/QStringListModel>

#include <memory>

namespace Ui
{
class FeatureLayerPropertiesWidget;
}

class FeatureLayer;
class IFeatureRenderer;
class FeatureRendererWidget;

class FeatureLayerPropertiesWidget : public PropertiesWidget
{
    Q_OBJECT
public:
    explicit FeatureLayerPropertiesWidget(FeatureLayer *layer, QWidget *parent = nullptr);
    ~FeatureLayerPropertiesWidget();

    void applyChanges(IServiceLocator *serviceLocator) override;

private slots:
    void onRendererChanged(const IFeatureRenderer* renderer);
    void onLayerNameEditingFinished();
    void onSymbolCategoryChanged(int index);

private:
    void installRendererWidget(FeatureRendererWidget *rendererWidget);

private:
    QStringListModel m_symbolCategories;
    Ui::FeatureLayerPropertiesWidget *m_ui;
    std::unique_ptr<IFeatureRenderer> m_renderer;
    FeatureLayer *m_layer;
    QString m_newName;
};

