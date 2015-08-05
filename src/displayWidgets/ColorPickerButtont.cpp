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

#include "displayWidgets/ColorPickerButtont.h"
#include <QtWidgets/QColorDialog>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtGui/QBrush>

ColorPickerButtont::ColorPickerButtont(QWidget *parent)
    : QPushButton(parent)
    , m_currentColor()
{
    this->setMinimumWidth(50);
    connect(this, SIGNAL(clicked()), this, SLOT(chooseColor()));
}

ColorPickerButtont::~ColorPickerButtont()
{
}

QColor ColorPickerButtont::color() const
{
    return m_currentColor;
}

void ColorPickerButtont::setColor(const QColor &newColor)
{
    m_currentColor = newColor;
    emit colorChanged(m_currentColor);
}

void ColorPickerButtont::chooseColor()
{
    QColor color = QColorDialog::getColor(m_currentColor, this);
    if (color.isValid())
    {
        setColor(color);
    }
}

void ColorPickerButtont::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    const int colorPadding = 5;

    QRect rect = event->rect();
    QPainter painter(this);
    painter.setBrush(QBrush(m_currentColor));
    painter.setPen("#CECECE");
    rect.adjust(colorPadding, colorPadding, -1 -colorPadding, -1 -colorPadding);
    painter.drawRect(rect);
}

