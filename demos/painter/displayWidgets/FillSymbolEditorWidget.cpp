/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include "displayWidgets/FillSymbolEditorWidget.h"

#include <display/SimpleFillSymbol.h>
#include <display/PictureMarkerSymbol.h>

#include <QtWidgets/QComboBox>

FillSymbolEditorWidget::FillSymbolEditorWidget(const FillSymbol *initialSymbol, QWidget *parent)
    : SymbolEditorWidget(parent)
    , m_symbols({"Simple fill symbol"})
    , m_symbol(static_cast<FillSymbol*>(initialSymbol->clone()))
{
    symbolsCbox()->setModel(&m_symbols);
    m_symbol->accept(*this);

    installSymbolWidget(m_symbol.get());

    connect(symbolsCbox(), SIGNAL(currentIndexChanged(int)),this, SLOT(onSymbolStyleChanged(int)));
}

FillSymbolEditorWidget::~FillSymbolEditorWidget()
{
}

void FillSymbolEditorWidget::onSymbolStyleChanged(const int index)
{
    installSymbolWidget(m_symbol.get());
    emit symbolChanged(m_symbol.get());
}

void FillSymbolEditorWidget::visit(SimpleFillSymbol &)
{
}

void FillSymbolEditorWidget::visit(SimpleLineSymbol &)
{
    Q_ASSERT(false && "This is a marker symbol editor!");
}

void FillSymbolEditorWidget::visit(SimpleMarkerSymbol &)
{
    Q_ASSERT(false && "This is a marker symbol editor!");
}

void FillSymbolEditorWidget::visit(PictureMarkerSymbol &)
{
    Q_ASSERT(false && "This is a marker symbol editor!");
}

