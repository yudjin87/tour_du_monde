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

#include "SimpleLineSymbolWidget.h"
#include "ui_SimpleLineSymbolWidget.h"
#include <display/SimpleLineSymbol.h>

#include <QtGui/QPixmap>
#include <QtGui/QIcon>
#include <QtGui/QDoubleValidator>

SimpleLineSymbolWidget::SimpleLineSymbolWidget(const SimpleLineSymbol *symbol, QWidget *parent)
    : SymbolWidget(Geometry::Type::Polyline, parent)
    , m_ui(new Ui::SimpleLineSymbolWidget)
    , m_symbol(static_cast<SimpleLineSymbol*>(symbol->clone()))
    , m_lineStyles(QStringList{"No pen", "Solid line", "Dash line", "Dot line", "Dash dot line", "Dash dot dot line"})
    , m_wasChanged(false)
{
    m_ui->setupUi(this);
    m_ui->gridLayout->setColumnMinimumWidth(0, LABEL_COLUMN_WIDHT);

    m_ui->lineStyles->setModel(&m_lineStyles);
    m_ui->lineStyles->setCurrentIndex(m_symbol->style());
    connect(m_ui->lineStyles, SIGNAL(currentIndexChanged(int)),this, SLOT(onLineStyleChanged(int)));

    m_ui->lineWidth->setText(QString::number(m_symbol->width()));
    m_ui->lineWidth->setValidator(new QDoubleValidator(0, 99, 1, this));
    connect(m_ui->lineWidth, &QLineEdit::editingFinished, this, &SimpleLineSymbolWidget::onWidthEditingFinished);

    m_ui->colorBtn->setColor(m_symbol->color());
    connect(m_ui->colorBtn, &ColorPickerButtont::colorChanged, this, &SimpleLineSymbolWidget::onColorChanged);
}

SimpleLineSymbolWidget::~SimpleLineSymbolWidget()
{
    delete m_ui;
}

void SimpleLineSymbolWidget::prepareForEmbedding()
{
    m_ui->gridLayout->setContentsMargins(0, 0, 0, 0);
    this->setContentsMargins(0, 0, 0, 0);
}

void SimpleLineSymbolWidget::onColorChanged(const QColor &newColor)
{
    if (newColor == m_symbol->color())
    {
        return;
    }

    m_symbol->setColor(newColor);
    notifySymbolChanged();
}

void SimpleLineSymbolWidget::onWidthEditingFinished()
{
    bool ok = false;
    const QString text = m_ui->lineWidth->text();
    double newWidth = text.toDouble(&ok);
    if (!ok)
    {
        return;
    }

    if (newWidth == m_symbol->width())
    {
        return;
    }

    m_symbol->setWidth(newWidth);
    notifySymbolChanged();
}

void SimpleLineSymbolWidget::onLineStyleChanged(const int index)
{
    const Qt::PenStyle newStyle = static_cast<Qt::PenStyle>(index);
    if (newStyle == m_symbol->style())
    {
        return;
    }

    switch (newStyle)
    {
    case Qt::NoPen:
    case Qt::SolidLine:
    case Qt::DashLine:
    case Qt::DotLine:
    case Qt::DashDotLine:
    case Qt::DashDotDotLine:
        m_symbol->setStyle(newStyle);
        notifySymbolChanged();
        break;
    case Qt::CustomDashLine:
    case Qt::MPenStyle:
        break; // unsupported
    }
}

void SimpleLineSymbolWidget::notifySymbolChanged()
{
    m_wasChanged = true;
    emit symbolChanged(m_symbol.get());
}


ISymbol *SimpleLineSymbolWidget::symbol()
{
    return m_symbol.get();
}

const ISymbol *SimpleLineSymbolWidget::symbol() const
{
    return m_symbol.get();
}

bool SimpleLineSymbolWidget::wasChanged() const
{
    return m_wasChanged;
}

void SimpleLineSymbolWidget::insertSampleWidget(QWidget *sample)
{
    const int SAMPLE_ROW = 3;
    QLabel* label = new QLabel(this);
    label->setText("Sample");
    m_ui->gridLayout->addWidget(label, SAMPLE_ROW, 0);
    m_ui->gridLayout->addWidget(sample, SAMPLE_ROW, 1);
}
