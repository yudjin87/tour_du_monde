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

#pragma once
#include "display/SymbolBase.h"

#include <QtGui/QColor>
#include <QtGui/QFont>

class DISPLAY_API TextSymbol : public SymbolBase
{
    Q_OBJECT
    /*!
     * @details
     *   Gets or sets the size in points (approx. 1/72 inch).
     */
    Q_PROPERTY(qreal size READ size WRITE setSize)

    /*!
     * @details
     *   Gets or sets the angle in degrees that the entire line of text is displayed.
     */
    Q_PROPERTY(qreal angle READ angle WRITE setAngle NOTIFY angleChanged)

    /*!
     * @details
     *   Gets or sets the line symbol color.
     */
    Q_PROPERTY(QColor color READ color WRITE setColor)

    /*!
     * @details
     *   Gets or sets the font that symbols uses for rendering.
     */
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)

    /*!
     * @details
     *   Gets or sets the string that will be drawn using the other properties of the TextSymbol.
     */
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    QColor color() const;
    void setColor(const QColor &color);

    qreal size() const;
    void setSize(qreal size);

    qreal angle() const;
    void setAngle(qreal angle);

    QFont font() const;
    void setFont(QFont font);

    QString text() const;
    void setText(QString text);

    void setupPainter(QPainter *painter) override;
    void resetPainter(QPainter *painter) override;

public slots:
    void setColor(int r, int g, int b, int a = 255);

signals:
    void angleChanged(qreal angle);
    void fontChanged(QFont font);
    void textChanged(QString text);

protected:
    explicit TextSymbol(QObject *parent = nullptr);
    TextSymbol(const TextSymbol& o, QObject *parent = nullptr);

private:
    qreal m_size;
    QColor m_color;
    qreal m_angle;
    QFont m_font;
    QString m_text;
};


