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

#include "SimpleMarkerSymbolWidget.h"
#include <display/SimpleMarkerSymbol.h>
#include <display/LineSymbol.h>
#include "ui_SimpleMarkerSymbolWidget.h"

#include <QtGui/QPixmap>
#include <QtGui/QIcon>
#include <QtGui/QDoubleValidator>

SimpleMarkerSymbolWidget::SimpleMarkerSymbolWidget(const SimpleMarkerSymbol *symbol,  QWidget *parent)
    : SymbolWidget(Geometry::Type::Point, parent)
    , m_ui(new Ui::SimpleMarkerSymbolWidget)
    , m_symbol(static_cast<SimpleMarkerSymbol*>(symbol->clone()))
    , m_styles(QStringList{"Circle", "Square", "Cross", "X", "Diamond"})
    , m_wasChanged(false)
{
    m_ui->setupUi(this);

    m_ui->markerStyleCBox->setModel(&m_styles);
    m_ui->markerStyleCBox->setCurrentIndex(static_cast<int>(m_symbol->style()));
    connect(m_ui->markerStyleCBox, SIGNAL(currentIndexChanged(int)),this, SLOT(onStyleChanged(int)));

    m_ui->colorBtn->setColor(m_symbol->color());
    connect(m_ui->colorBtn, &ColorPickerButtont::colorChanged, this, &SimpleMarkerSymbolWidget::onColorChanged);

    m_ui->outlineColorBtn->setColor(m_symbol->outlineColor());
    connect(m_ui->outlineColorBtn, &ColorPickerButtont::colorChanged, this, &SimpleMarkerSymbolWidget::onOutlineColorChanged);

    m_ui->markerSizeEdit->setText(QString::number(m_symbol->size()));
    m_ui->markerSizeEdit->setValidator(new QDoubleValidator(0, 99, 1, this));
    connect(m_ui->markerSizeEdit, &QLineEdit::editingFinished, this, &SimpleMarkerSymbolWidget::onSizeEditingFinished);

    m_ui->outlineWidthEdit->setText(QString::number(m_symbol->outlineSize()));
    m_ui->outlineWidthEdit->setValidator(new QDoubleValidator(0, 99, 1, this));
    connect(m_ui->outlineWidthEdit, &QLineEdit::editingFinished, this, &SimpleMarkerSymbolWidget::onOutlineSizeEditingFinished);
}

SimpleMarkerSymbolWidget::~SimpleMarkerSymbolWidget()
{
    delete m_ui;
}

void SimpleMarkerSymbolWidget::prepareForEmbedding()
{
    m_ui->verticalLayout->setContentsMargins(QMargins());
}

void SimpleMarkerSymbolWidget::onColorChanged(const QColor &newColor)
{
    if (newColor == m_symbol->color())
    {
        return;
    }

    m_symbol->setColor(newColor);
    notifySymbolChanged();
}

void SimpleMarkerSymbolWidget::onOutlineColorChanged(const QColor &newColor)
{
    if (newColor == m_symbol->outlineColor())
    {
        return;
    }

    m_symbol->setOutlineColor(newColor);
    notifySymbolChanged();
}

void SimpleMarkerSymbolWidget::onSizeEditingFinished()
{
    bool ok = false;
    const QString text = m_ui->markerSizeEdit->text();
    double newSize = text.toDouble(&ok);
    if (!ok)
    {
        return;
    }

    if (newSize == m_symbol->size())
    {
        return;
    }

    m_symbol->setSize(newSize);
    notifySymbolChanged();
}

void SimpleMarkerSymbolWidget::onOutlineSizeEditingFinished()
{
    bool ok = false;
    const QString text = m_ui->outlineWidthEdit->text();
    double newSize = text.toDouble(&ok);
    if (!ok)
    {
        return;
    }

    if (newSize == m_symbol->outlineSize())
    {
        return;
    }

    m_symbol->setOutlineSize(newSize);
    notifySymbolChanged();
}

void SimpleMarkerSymbolWidget::onStyleChanged(const int index)
{
    const SimpleMarkerSymbol::Style newStyle = static_cast<SimpleMarkerSymbol::Style>(index);
    if (newStyle == m_symbol->style())
    {
        return;
    }

    switch (newStyle)
    {
    case SimpleMarkerSymbol::Style::Circle:
    case SimpleMarkerSymbol::Style::Cross:
    case SimpleMarkerSymbol::Style::Diamond:
    case SimpleMarkerSymbol::Style::Square:
    case SimpleMarkerSymbol::Style::X:
        m_symbol->setStyle(newStyle);
        notifySymbolChanged();
        break;
    }
}

void SimpleMarkerSymbolWidget::notifySymbolChanged()
{
    m_wasChanged = true;
    emit symbolChanged(m_symbol.get());
}

ISymbol *SimpleMarkerSymbolWidget::symbol()
{
    return m_symbol.get();
}

const ISymbol *SimpleMarkerSymbolWidget::symbol() const
{
    return m_symbol.get();
}

bool SimpleMarkerSymbolWidget::wasChanged() const
{
    return m_wasChanged;
}

void SimpleMarkerSymbolWidget::insertSampleWidget(QWidget *sample)
{
    const int SAMPLE_ROW = 5;
    QLabel* label = new QLabel(this);
    label->setText("Sample");
    m_ui->gridLayout->addWidget(label, SAMPLE_ROW, 0);
    m_ui->gridLayout->addWidget(sample, SAMPLE_ROW, 1);
}
