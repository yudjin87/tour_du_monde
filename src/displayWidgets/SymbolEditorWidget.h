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
#include <displayWidgets/displayWidgets_api.h>
#include <components/interactivity/PropertiesWidget.h>

#include <memory>

class ISymbol;
class QComboBox;

namespace Ui
{
class SymbolEditorWidget;
}

class DISPLAY_WIDGETS_API SymbolEditorWidget : public PropertiesWidget
{
    Q_OBJECT
public:
    ~SymbolEditorWidget();

    void applyChanges(IServiceLocator *serviceLocator) override;

    void prepareForEmbedding();

protected:
    explicit SymbolEditorWidget(QWidget *parent = nullptr);

    QComboBox* symbolsCbox();
    void installSymbolWidget(ISymbol *forSymbol);

protected slots:
    virtual void onSymbolStyleChanged(const int index) = 0;

signals:
    void symbolChanged(const ISymbol* newSymbol);

private:
    Ui::SymbolEditorWidget *m_ui;
};
