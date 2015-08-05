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

#include "displayWidgets/MarkerSymbolEditorWidget.h"

#include <display/SimpleMarkerSymbol.h>
#include <display/PictureMarkerSymbol.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtWidgets/QComboBox>

MarkerSymbolEditorWidget::MarkerSymbolEditorWidget(const MarkerSymbol *initialSymbol, QWidget *parent)
    : SymbolEditorWidget(parent)
    , m_symbols({"Simple marker symbol", "Picture marker symbol"})
    , m_symbol(static_cast<MarkerSymbol*>(initialSymbol->clone()))
{
    symbolsCbox()->setModel(&m_symbols);
    m_symbol->accept(*this);

    installSymbolWidget(m_symbol.get());

    connect(symbolsCbox(), SIGNAL(currentIndexChanged(int)),this, SLOT(onSymbolStyleChanged(int)));
}

MarkerSymbolEditorWidget::~MarkerSymbolEditorWidget()
{

}

void MarkerSymbolEditorWidget::onSymbolStyleChanged(const int index)
{
    switch (index)
    {
    case 0:
        m_symbol.reset(new SimpleMarkerSymbol());
        break;
    case 1:
        QDir appDir(QCoreApplication::applicationDirPath());
        appDir.cd("markers");
        m_symbol.reset(PictureMarkerSymbol::createFromFilePicture(appDir.absoluteFilePath("hotel.png")));
        break;
    }

    installSymbolWidget(m_symbol.get());
    emit symbolChanged(m_symbol.get());
}

void MarkerSymbolEditorWidget::visit(SimpleFillSymbol &)
{
    Q_ASSERT(false && "This is a marker symbol editor!");
}

void MarkerSymbolEditorWidget::visit(PictureFillSymbol &symbol)
{
    Q_ASSERT(false && "This is a marker symbol editor!");
}

void MarkerSymbolEditorWidget::visit(SimpleLineSymbol &)
{
    Q_ASSERT(false && "This is a marker symbol editor!");
}

void MarkerSymbolEditorWidget::visit(SimpleMarkerSymbol &)
{
    symbolsCbox()->setCurrentIndex(0);
}

void MarkerSymbolEditorWidget::visit(PictureMarkerSymbol &)
{
    symbolsCbox()->setCurrentIndex(1);
}

