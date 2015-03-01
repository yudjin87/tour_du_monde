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

#include "SimpleLineSymbolWidget.h"
#include "ui_SimpleLineSymbolWidget.h"

#include "display/SimpleLineSymbol.h"
#include "display/SymbolThumbnail.h"
#include <geometry/GeometryType.h>

#include <QtGui/QPixmap>
#include <QtGui/QIcon>



SimpleLineSymbolWidget::SimpleLineSymbolWidget(const SimpleLineSymbol *symbol, QWidget *parent)
    : SymbolWidget(parent)
    , m_ui(new Ui::SimpleLineSymbolWidget)
    , m_symbol(static_cast<SimpleLineSymbol*>(symbol->clone(this)))
    , m_lineStyles(QStringList{"No pen", "Solid line", "Dash line", "Dot line", "Dash dot line", "Dash dot dot line"})
    , m_wasChanged(false)
{
    m_ui->setupUi(this);
    m_ui->lineStyles->setModel(&m_lineStyles);
    m_ui->lineStyles->setCurrentIndex(m_symbol->style());
    //connect(m_ui->lineStyles, &QComboBox::currentIndexChanged, this, &SimpleLineSymbolWidget::onLineStyleChanged);
    connect(m_ui->lineStyles, SIGNAL(currentIndexChanged(int)),this, SLOT(onLineStyleChanged(int)));

    m_ui->lineWidth->setText(QString::number(m_symbol->width()));
    connect(m_ui->lineWidth, &QLineEdit::editingFinished, this, &SimpleLineSymbolWidget::onWidthEditingFinished);

    m_ui->colorBtn->setColor(m_symbol->color());
    connect(m_ui->colorBtn, &ColorPickerButtont::colorChanged, this, &SimpleLineSymbolWidget::onColorChanged);

    updateSample();
}

SimpleLineSymbolWidget::~SimpleLineSymbolWidget()
{
    delete m_ui;
}

void SimpleLineSymbolWidget::onColorChanged(const QColor &newColor)
{
    m_symbol->setColor(newColor);
    updateSample();
}

void SimpleLineSymbolWidget::onWidthEditingFinished()
{
    bool ok = false;
    const QString text = m_ui->lineWidth->text();
    double result = text.toDouble(&ok);
    if (!ok)
    {
        return;
    }

    m_symbol->setWidth(result);
    updateSample();
}

void SimpleLineSymbolWidget::onLineStyleChanged(const int index)
{
    const Qt::PenStyle newStyle = static_cast<Qt::PenStyle>(index);
    switch (newStyle)
    {
    case Qt::NoPen:
    case Qt::SolidLine:
    case Qt::DashLine:
    case Qt::DotLine:
    case Qt::DashDotLine:
    case Qt::DashDotDotLine:
        m_symbol->setStyle(newStyle);
        updateSample();
        break;
    case Qt::CustomDashLine:
    case Qt::MPenStyle:
        break; // unsupported
    }
}

void SimpleLineSymbolWidget::updateSample()
{
    m_wasChanged = true;

    SymbolThumbnail thumbnailCreator(60, 4);
    thumbnailCreator.setBackground(Qt::white);
    QPixmap sample = thumbnailCreator.createSymbolThumbnail(m_symbol, GeometryPolyline);
    m_ui->sample->setPixmap(sample);
    m_ui->sample->setMinimumSize(sample.rect().size());
}


const ISymbol *SimpleLineSymbolWidget::symbol() const
{
    return m_symbol;
}

bool SimpleLineSymbolWidget::wasChanged() const
{
    return m_wasChanged;
}
