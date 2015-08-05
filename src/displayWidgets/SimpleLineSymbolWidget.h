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
#include <displayWidgets/SymbolWidget.h>
#include <QtCore/QStringListModel>
#include <memory>

namespace Ui
{
class SimpleLineSymbolWidget;
}

class SimpleLineSymbol;

class DISPLAY_WIDGETS_API SimpleLineSymbolWidget : public SymbolWidget
{
    Q_OBJECT

public:
    explicit SimpleLineSymbolWidget(const SimpleLineSymbol* symbol, QWidget *parent = nullptr);
    ~SimpleLineSymbolWidget();

    void prepareForEmbedding() override;

    const ISymbol *symbol() const override;
    bool wasChanged() const override;

protected:
    void insertSampleWidget(QWidget* sample) override;
    ISymbol* symbol() override;

private slots:
    void onColorChanged(const QColor& newColor);
    void onWidthEditingFinished();
    void onLineStyleChanged(const int index);

private:
    void notifySymbolChanged();

private:
    Ui::SimpleLineSymbolWidget *m_ui;
    std::unique_ptr<SimpleLineSymbol> m_symbol;
    QStringListModel m_lineStyles;
    bool m_wasChanged;

};

