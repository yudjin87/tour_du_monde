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

#include "displayWidgets/SymbolWidgetCreator.h"
#include <display/SimpleFillSymbol.h>
#include <display/PictureFillSymbol.h>
#include <display/SimpleLineSymbol.h>
#include <display/SimpleMarkerSymbol.h>
#include <display/PictureMarkerSymbol.h>

#include "displayWidgets/SimpleFillSymbolWidget.h"
#include "displayWidgets/PictureFillSymbolWidget.h"
#include "displayWidgets/SimpleLineSymbolWidget.h"
#include "displayWidgets/SimpleMarkerSymbolWidget.h"
#include "displayWidgets/PictureMarkerSymbolWidget.h"

#include "displayWidgets/MarkerSymbolEditorWidget.h"
#include "displayWidgets/LineSymbolEditorWidget.h"
#include "displayWidgets/FillSymbolEditorWidget.h"

#include <QtWidgets/QWidget>

SymbolWidgetCreator::SymbolWidgetCreator()
    : m_widget(nullptr)
    , m_editor(nullptr)
    , m_state(CreationState::Widget)
{
}

SymbolWidgetCreator::~SymbolWidgetCreator()
{
    delete m_widget;
    m_widget = nullptr;

    delete m_editor;
    m_editor = nullptr;
}

SymbolWidget *SymbolWidgetCreator::createWidget(ISymbol *forSymbol, QWidget *parent)
{
    m_state = CreationState::Widget;

    forSymbol->accept(*this);
    m_widget->setParent(parent);
    SymbolWidget *tmp = m_widget;
    m_widget = nullptr;
    return tmp;
}

SymbolEditorWidget *SymbolWidgetCreator::createEditorWidget(ISymbol *forSymbol, QWidget *parent)
{
    m_state = CreationState::Editor;

    forSymbol->accept(*this);
    m_editor->setParent(parent);
    SymbolEditorWidget *tmp = m_editor;
    m_editor = nullptr;
    return tmp;
}

void SymbolWidgetCreator::visit(SimpleFillSymbol &symbol)
{
    switch (m_state)
    {
    case CreationState::Widget:
    {
        delete m_widget;
        SymbolWidgetCreator lineWidgetCreator;
        SymbolWidget *lineWidget = lineWidgetCreator.createWidget(symbol.outline(), nullptr);
        lineWidget->prepareForEmbedding();

        m_widget = new SimpleFillSymbolWidget(&symbol, lineWidget);
        break;
    }

    case CreationState::Editor:
        delete m_editor;
        m_editor = new FillSymbolEditorWidget(&symbol);
        break;
    }
}

void SymbolWidgetCreator::visit(PictureFillSymbol &symbol)
{
    switch (m_state)
    {
    case CreationState::Widget:
    {
        delete m_widget;
        SymbolWidgetCreator lineWidgetCreator;
        SymbolWidget *lineWidget = lineWidgetCreator.createWidget(symbol.outline(), nullptr);
        lineWidget->prepareForEmbedding();

        m_widget = new PictureFillSymbolWidget(&symbol, lineWidget);
        break;
    }

    case CreationState::Editor:
        delete m_editor;
        m_editor = new FillSymbolEditorWidget(&symbol);
        break;
    }
}

void SymbolWidgetCreator::visit(SimpleLineSymbol &symbol)
{
    switch (m_state)
    {
    case CreationState::Widget:
        delete m_widget;
        m_widget = new SimpleLineSymbolWidget(&symbol);
        break;
    case CreationState::Editor:
        delete m_editor;
        m_editor = new LineSymbolEditorWidget(&symbol);
        break;
    }
}

void SymbolWidgetCreator::visit(SimpleMarkerSymbol &symbol)
{
    switch (m_state)
    {
    case CreationState::Widget:
        delete m_widget;
        m_widget = new SimpleMarkerSymbolWidget(&symbol);
        break;

    case CreationState::Editor:
        delete m_editor;
        m_editor = new MarkerSymbolEditorWidget(&symbol);
        break;
    }
}

void SymbolWidgetCreator::visit(PictureMarkerSymbol &symbol)
{
    switch (m_state)
    {
    case CreationState::Widget:
        delete m_widget;
        m_widget = new PictureMarkerSymbolWidget(&symbol);
        break;

    case CreationState::Editor:
        delete m_editor;
        m_editor = new MarkerSymbolEditorWidget(&symbol);
        break;
    }
}
