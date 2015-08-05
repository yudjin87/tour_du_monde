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

#include "SimpleFillSymbolWidget.h"
#include <display/SimpleFillSymbol.h>
#include <display/LineSymbol.h>
#include "ui_SimpleFillSymbolWidget.h"

#include <QtGui/QPixmap>
#include <QtGui/QIcon>
#include <QtGui/QDoubleValidator>

SimpleFillSymbolWidget::SimpleFillSymbolWidget(const SimpleFillSymbol *symbol, SymbolWidget *lineWidget, QWidget *parent)
    : SymbolWidget(Geometry::Type::Polygon, parent)
    , m_ui(new Ui::SimpleFillSymbolWidget)
    , m_lineWidget(lineWidget)
    , m_symbol(static_cast<SimpleFillSymbol*>(symbol->clone()))
    , m_patternStyles(QStringList{"NoBrush",
                      "Solid",
                      "Dense #1",
                      "Dense #2",
                      "Dense #3",
                      "Dense #4",
                      "Dense #5",
                      "Dense #6",
                      "Dense #7",
                      "Horisontal",
                      "Vertical",
                      "Cross",
                      "Backward diagonal",
                      "Forward diagonal",
                      "Cross diagonal"})
    , m_wasChanged(false)
{
    lineWidget->setParent(this);
    connect(lineWidget, &SymbolWidget::symbolChanged, this, &SimpleFillSymbolWidget::onOutlineSymbolChanged);

    m_ui->setupUi(this);
    m_ui->gridLayout->setColumnMinimumWidth(0, LABEL_COLUMN_WIDHT);
    const int SECOND_COLUMN_WEIGHT = 100;
    m_ui->gridLayout->setColumnStretch(1, SECOND_COLUMN_WEIGHT);

    m_ui->verticalLayout->insertWidget(0, lineWidget);

    m_ui->patternCbox->setModel(&m_patternStyles);
    m_ui->patternCbox->setCurrentIndex(m_symbol->style());
    connect(m_ui->patternCbox, SIGNAL(currentIndexChanged(int)),this, SLOT(onPattertStyleChanged(int)));

    m_ui->colorBtn->setColor(m_symbol->color());
    connect(m_ui->colorBtn, &ColorPickerButtont::colorChanged, this, &SimpleFillSymbolWidget::onColorChanged);

}

SimpleFillSymbolWidget::~SimpleFillSymbolWidget()
{
    delete m_ui;
}

void SimpleFillSymbolWidget::prepareForEmbedding()
{
    m_ui->verticalLayout->setContentsMargins(QMargins());
}

void SimpleFillSymbolWidget::onColorChanged(const QColor &newColor)
{
    if (newColor == m_symbol->color())
    {
        return;
    }

    m_symbol->setColor(newColor);
    notifySymbolChanged();
}

void SimpleFillSymbolWidget::onPattertStyleChanged(const int index)
{
    const Qt::BrushStyle newStyle = static_cast<Qt::BrushStyle>(index);
    if (newStyle == m_symbol->style())
    {
        return;
    }

    switch (newStyle)
    {
    case Qt::NoBrush:
    case Qt::SolidPattern:
    case Qt::Dense1Pattern:
    case Qt::Dense2Pattern:
    case Qt::Dense3Pattern:
    case Qt::Dense4Pattern:
    case Qt::Dense5Pattern:
    case Qt::Dense6Pattern:
    case Qt::Dense7Pattern:
    case Qt::HorPattern:
    case Qt::VerPattern:
    case Qt::CrossPattern:
    case Qt::BDiagPattern:
    case Qt::FDiagPattern:
    case Qt::DiagCrossPattern:
        m_symbol->setStyle(newStyle);
        notifySymbolChanged();
        break;
    case Qt::LinearGradientPattern:
    case Qt::RadialGradientPattern:
    case Qt::ConicalGradientPattern:
    case Qt::TexturePattern:
        break; // unsupported
    }
}

void SimpleFillSymbolWidget::onOutlineSymbolChanged(const ISymbol *newSymbol)
{
    m_symbol->setOutline(dynamic_cast<LineSymbol*>(newSymbol->clone()));
    notifySymbolChanged();
}

void SimpleFillSymbolWidget::notifySymbolChanged()
{
    m_wasChanged = true;
    emit symbolChanged(m_symbol.get());
}

ISymbol *SimpleFillSymbolWidget::symbol()
{
    return m_symbol.get();
}

const ISymbol *SimpleFillSymbolWidget::symbol() const
{
    return m_symbol.get();
}

bool SimpleFillSymbolWidget::wasChanged() const
{
    return m_wasChanged;
}

void SimpleFillSymbolWidget::insertSampleWidget(QWidget *sample)
{
    const int SAMPLE_ROW = 2;
    QLabel* label = new QLabel(this);
    label->setText("Sample");
    m_ui->gridLayout->addWidget(label, SAMPLE_ROW, 0);
    m_ui->gridLayout->addWidget(sample, SAMPLE_ROW, 1);
}
