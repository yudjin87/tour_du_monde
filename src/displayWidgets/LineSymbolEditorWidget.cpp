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

#include "displayWidgets/LineSymbolEditorWidget.h"

#include <display/SimpleFillSymbol.h>
#include <display/SimpleLineSymbol.h>
#include <display/SimpleMarkerSymbol.h>
#include <display/SimpleTextSymbol.h>
#include <display/PictureFillSymbol.h>
#include <display/PictureMarkerSymbol.h>
#include <display/GradientFillSymbol.h>

#include <QtWidgets/QComboBox>

LineSymbolEditorWidget::LineSymbolEditorWidget(const ISymbol *initialSymbol, QWidget *parent)
    : SymbolEditorWidget(parent)
    , m_symbols({"Simple line symbol"})
    , m_symbol(initialSymbol->clone())
{
    symbolsCbox()->setModel(&m_symbols);
    m_symbol->accept(*this);

    installSymbolWidget(m_symbol.get());

    connect(symbolsCbox(), SIGNAL(currentIndexChanged(int)),this, SLOT(onSymbolStyleChanged(int)));
}

LineSymbolEditorWidget::~LineSymbolEditorWidget()
{

}

void LineSymbolEditorWidget::onSymbolStyleChanged(const int index)
{
    Q_UNUSED(index)
    installSymbolWidget(m_symbol.get());
    emit symbolChanged(m_symbol.get());
}

void LineSymbolEditorWidget::visit(SimpleFillSymbol &symbol)
{
    Q_UNUSED(symbol)
    Q_ASSERT(false && "This is a line symbol editor!");
}

void LineSymbolEditorWidget::visit(PictureFillSymbol &symbol)
{
    Q_UNUSED(symbol)
    Q_ASSERT(false && "This is a line symbol editor!");
}

void LineSymbolEditorWidget::visit(GradientFillSymbol &symbol)
{
    Q_UNUSED(symbol)
    Q_ASSERT(false && "This is a line symbol editor!");
}

void LineSymbolEditorWidget::visit(SimpleLineSymbol &symbol)
{
    Q_UNUSED(symbol)
    symbolsCbox()->setCurrentIndex(0);
}

void LineSymbolEditorWidget::visit(SimpleMarkerSymbol &symbol)
{
    Q_UNUSED(symbol)
    Q_ASSERT(false && "This is a line symbol editor!");
}

void LineSymbolEditorWidget::visit(PictureMarkerSymbol &symbol)
{
    Q_UNUSED(symbol)
    Q_ASSERT(false && "This is a line symbol editor!");
}

void LineSymbolEditorWidget::visit(SimpleTextSymbol &symbol)
{
    Q_UNUSED(symbol)
    Q_ASSERT(false && "This is a line symbol editor!");
}
