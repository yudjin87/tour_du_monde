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

#include "displayWidgets/FillSymbolEditorWidget.h"

#include <display/SimpleFillSymbol.h>
#include <display/SimpleLineSymbol.h>
#include <display/SimpleMarkerSymbol.h>
#include <display/SimpleTextSymbol.h>
#include <display/PictureFillSymbol.h>
#include <display/PictureMarkerSymbol.h>
#include <display/GradientFillSymbol.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtWidgets/QComboBox>

FillSymbolEditorWidget::FillSymbolEditorWidget(const ISymbol *initialSymbol, QWidget *parent)
    : SymbolEditorWidget(parent)
    , m_symbols({"Simple fill symbol", "Picture fill symbol", "Gradient fill symbol"})
    , m_symbol(initialSymbol->clone())
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
    switch (index)
    {
    case 0:
    {
        m_symbol.reset(new SimpleFillSymbol());
        break;
    }
    case 1:
    {
        QDir appDir(QCoreApplication::applicationDirPath());
        appDir.cd("brushes");
        m_symbol.reset(PictureFillSymbol::createFromFilePicture(appDir.absoluteFilePath("forest.png")));
        break;
    }
    case 2:
    {
        m_symbol.reset(new GradientFillSymbol());
        break;
    }
    }

    installSymbolWidget(m_symbol.get());
    emit symbolChanged(m_symbol.get());
}

void FillSymbolEditorWidget::visit(SimpleFillSymbol &)
{
    symbolsCbox()->setCurrentIndex(0);
}

void FillSymbolEditorWidget::visit(PictureFillSymbol &)
{
    symbolsCbox()->setCurrentIndex(1);
}

void FillSymbolEditorWidget::visit(GradientFillSymbol &)
{
    symbolsCbox()->setCurrentIndex(2);
}

void FillSymbolEditorWidget::visit(SimpleLineSymbol &symbol)
{
    Q_UNUSED(symbol)
    Q_ASSERT(false && "This is a fill symbol editor!");
}

void FillSymbolEditorWidget::visit(SimpleMarkerSymbol &symbol)
{
    Q_UNUSED(symbol)
    Q_ASSERT(false && "This is a fill symbol editor!");
}

void FillSymbolEditorWidget::visit(PictureMarkerSymbol &symbol)
{
    Q_UNUSED(symbol)
    Q_ASSERT(false && "This is a fill symbol editor!");
}

void FillSymbolEditorWidget::visit(SimpleTextSymbol &symbol)
{
    Q_UNUSED(symbol)
    Q_ASSERT(false && "This is a fill symbol editor!");
}

