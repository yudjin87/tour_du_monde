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

#ifndef FEATURELAYERPROPERTIESWIDGET_H
#define FEATURELAYERPROPERTIESWIDGET_H

#include <components/interactivity/PropertiesWidget.h>
#include <geometry/GeometryType.h>
#include <display/ISymbol.h>

namespace Ui
{
class FeatureLayerPropertiesWidget;
}

class FeatureLayer;
class ISymbol;

class FeatureLayerPropertiesWidget : public PropertiesWidget
{
    Q_OBJECT
public:
    explicit FeatureLayerPropertiesWidget(FeatureLayer *layer, QWidget *parent = nullptr);
    ~FeatureLayerPropertiesWidget();

    void applyChanges(IServiceLocator *serviceLocator) override;

private slots:
    void onSymbolChanged(const ISymbol* newSymbol);
    void onLayerNameEditingFinished();

private:
    Ui::FeatureLayerPropertiesWidget *m_ui;
    FeatureLayer *m_layer;
    ISymbolUPtr m_newSymbol;
    QString m_newName;
};

#endif // FEATURELAYERPROPERTIESWIDGET_H
