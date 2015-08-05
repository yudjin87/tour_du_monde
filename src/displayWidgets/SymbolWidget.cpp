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

#include "SymbolWidget.h"
#include <display/SymbolThumbnail.h>
#include <display/ISymbol.h>

#include <QtWidgets/QLabel>

SymbolWidget::SymbolWidget(const Geometry::Type type, QWidget *parent)
    : QWidget(parent)
    , m_type(type)
    , m_sample(nullptr)
{
    connect(this, &SymbolWidget::symbolChanged, this, &SymbolWidget::onSymbolChanged);
}

SymbolWidget::~SymbolWidget()
{
}

void SymbolWidget::initializeSample()
{
    m_sample = new QLabel(this);
    insertSampleWidget(m_sample);
    updateSample();
}

void SymbolWidget::onSymbolChanged(const ISymbol *newSymbol)
{
    Q_UNUSED(newSymbol);

    if (m_sample == nullptr)
    {
        return;
    }

    updateSample();
}

void SymbolWidget::updateSample()
{
    SymbolThumbnail thumbnailCreator(60, 4);
    thumbnailCreator.setBackground(Qt::white);
    QPixmap sample = thumbnailCreator.createSymbolThumbnail(symbol(), m_type);
    m_sample->setPixmap(sample);
    m_sample->setMinimumSize(sample.rect().size());
}

