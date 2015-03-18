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

#include "display/SymbolWidgetCreator.h"
#include "display/SimpleFillSymbol.h"
#include "display/SimpleLineSymbol.h"
#include "display/SimpleMarkerSymbol.h"

#include "display/SimpleFillSymbolWidget.h"
#include "display/SimpleLineSymbolWidget.h"
#include "display/SimpleMarkerSymbolWidget.h"

#include <QtWidgets/QWidget>

SymbolWidgetCreator::SymbolWidgetCreator()
    : m_widget(nullptr)
{
}

SymbolWidgetCreator::~SymbolWidgetCreator()
{
    delete m_widget;
    m_widget = nullptr;
}

SymbolWidget *SymbolWidgetCreator::createWidget(ISymbol *forSymbol, QWidget *parent)
{
    forSymbol->accept(*this);
    m_widget->setParent(parent);
    SymbolWidget *tmp = m_widget;
    m_widget = nullptr;
    return tmp;
}

void SymbolWidgetCreator::visit(SimpleFillSymbol &symbol)
{
    delete m_widget;
    SymbolWidgetCreator lineWidgetCreator;
    SymbolWidget *lineWidget = lineWidgetCreator.createWidget(symbol.outline(), nullptr);
    lineWidget->prepareForEmbedding();

    m_widget = new SimpleFillSymbolWidget(&symbol, lineWidget);
}

void SymbolWidgetCreator::visit(SimpleLineSymbol &symbol)
{
    delete m_widget;
    m_widget = new SimpleLineSymbolWidget(&symbol);
}

void SymbolWidgetCreator::visit(SimpleMarkerSymbol &symbol)
{
    delete m_widget;
    m_widget = new SimpleMarkerSymbolWidget(&symbol);
}
