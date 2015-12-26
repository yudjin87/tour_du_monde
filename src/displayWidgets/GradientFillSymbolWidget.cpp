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

#include "GradientFillSymbolWidget.h"
#include <display/GradientFillSymbol.h>
#include <display/LineSymbol.h>
#include "ui_GradientFillSymbolWidget.h"

GradientFillSymbolWidget::GradientFillSymbolWidget(const GradientFillSymbol *symbol, SymbolWidget *lineWidget, QWidget *parent)
    : SymbolWidget(Geometry::Type::Polygon, parent)
    , m_ui(new Ui::GradientFillSymbolWidget)
    , m_lineWidget(lineWidget)
    , m_symbol(static_cast<GradientFillSymbol*>(symbol->clone()))
    , m_wasChanged(false)
{
    lineWidget->setParent(this);
    connect(lineWidget, &SymbolWidget::symbolChanged, this, &GradientFillSymbolWidget::onOutlineSymbolChanged);

    m_ui->setupUi(this);
    m_ui->gridLayout->setColumnMinimumWidth(0, LABEL_COLUMN_WIDHT);
    const int SECOND_COLUMN_WEIGHT = 100;
    m_ui->gridLayout->setColumnStretch(1, SECOND_COLUMN_WEIGHT);

    m_ui->verticalLayout->insertWidget(0, lineWidget);

    m_ui->centralColorBtn->setColor(m_symbol->centralColor());
    connect(m_ui->centralColorBtn, &ColorPickerButtont::colorChanged, this, &GradientFillSymbolWidget::onCentralColorChanged);

    m_ui->surroundColorBtn->setColor(m_symbol->surroundColor());
    connect(m_ui->surroundColorBtn, &ColorPickerButtont::colorChanged, this, &GradientFillSymbolWidget::onSurroundColorChanged);

    // gradient settings
    m_ui->blendTriangularBellShape_focus->setValue(m_symbol->triangularBellShapeFocus() * 100);
    connect(m_ui->blendTriangularBellShape_focus, &QSlider::valueChanged, this, &GradientFillSymbolWidget::onGradientSettingsChanged);

    m_ui->blendTriangularBellShape_scale->setValue(m_symbol->triangularBellShapeScale() * 100);
    connect(m_ui->blendTriangularBellShape_scale, &QSlider::valueChanged, this, &GradientFillSymbolWidget::onGradientSettingsChanged);

    m_ui->blendBellShape_focus->setValue(m_symbol->bellShapeFocus() * 100);
    connect(m_ui->blendBellShape_focus, &QSlider::valueChanged, this, &GradientFillSymbolWidget::onGradientSettingsChanged);

    m_ui->blendBellShape_scale->setValue(m_symbol->bellShapeScale() * 100);
    connect(m_ui->blendBellShape_scale, &QSlider::valueChanged, this, &GradientFillSymbolWidget::onGradientSettingsChanged);

    m_ui->blendFactor_1->setValue(m_symbol->blendFactor1() * 100);
    connect(m_ui->blendFactor_1, &QSlider::valueChanged, this, &GradientFillSymbolWidget::onGradientSettingsChanged);

    m_ui->blendFactor_2->setValue(m_symbol->blendFactor2() * 100);
    connect(m_ui->blendFactor_2, &QSlider::valueChanged, this, &GradientFillSymbolWidget::onGradientSettingsChanged);

    m_ui->blendPosition_1->setValue(symbol->blendPosition1() * 100);
    connect(m_ui->blendPosition_1, &QSlider::valueChanged, this, &GradientFillSymbolWidget::onGradientSettingsChanged);

    m_ui->blendPosition_2->setValue(symbol->blendPosition2() * 100);
    connect(m_ui->blendPosition_2, &QSlider::valueChanged, this, &GradientFillSymbolWidget::onGradientSettingsChanged);
}

GradientFillSymbolWidget::~GradientFillSymbolWidget()
{
    delete m_ui;
    m_ui = nullptr;
}

void GradientFillSymbolWidget::prepareForEmbedding()
{
    m_ui->verticalLayout->setContentsMargins(QMargins());
}

void GradientFillSymbolWidget::onCentralColorChanged(const QColor &newColor)
{
    if (newColor == m_symbol->centralColor())
    {
        return;
    }

    m_symbol->setCentralColor(newColor);
    notifySymbolChanged();
}

void GradientFillSymbolWidget::onSurroundColorChanged(const QColor &newColor)
{
    if (newColor == m_symbol->surroundColor())
    {
        return;
    }

    m_symbol->setSurroundColor(newColor);
    notifySymbolChanged();
}

void GradientFillSymbolWidget::onOutlineSymbolChanged(const ISymbol *newSymbol)
{
    m_symbol->setOutline(dynamic_cast<LineSymbol*>(newSymbol->clone()));
    notifySymbolChanged();
}

void GradientFillSymbolWidget::onGradientSettingsChanged(int)
{
    m_symbol->setBlendFactor1(static_cast<qreal>(m_ui->blendFactor_1->value()) / 100);
    m_symbol->setBlendFactor2(static_cast<qreal>(m_ui->blendFactor_2->value()) / 100);
    m_symbol->setBlendPosition1(static_cast<qreal>(m_ui->blendPosition_1->value()) / 100);
    m_symbol->setBlendPosition2(static_cast<qreal>(m_ui->blendPosition_2->value()) / 100);

    m_symbol->setTriangularBellShapeFocus(static_cast<qreal>(m_ui->blendTriangularBellShape_focus->value()) / 100);
    m_symbol->setTriangularBellShapeScale(static_cast<qreal>(m_ui->blendTriangularBellShape_scale->value()) / 100);
    m_symbol->setBellShapeFocus(static_cast<qreal>(m_ui->blendBellShape_focus->value()) / 100);
    m_symbol->setBellShapeScale(static_cast<qreal>(m_ui->blendBellShape_scale->value()) / 100);

    notifySymbolChanged();
}

void GradientFillSymbolWidget::notifySymbolChanged()
{
    m_wasChanged = true;
    emit symbolChanged(m_symbol.get());
}

ISymbol *GradientFillSymbolWidget::symbol()
{
    return m_symbol.get();
}

const ISymbol *GradientFillSymbolWidget::symbol() const
{
    return m_symbol.get();
}

bool GradientFillSymbolWidget::wasChanged() const
{
    return m_wasChanged;
}

void GradientFillSymbolWidget::insertSampleWidget(QWidget *sample)
{
    const int SAMPLE_ROW = 2;
    QLabel* label = new QLabel(this);
    label->setText("Sample");
    m_ui->gridLayout->addWidget(label, SAMPLE_ROW, 0);
    m_ui->gridLayout->addWidget(sample, SAMPLE_ROW, 1);
}
