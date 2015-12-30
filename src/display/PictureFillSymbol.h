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

#include <display/FillSymbol.h>

#include <QtGui/QPixmap>
#include <QtGui/QBrush>

class DISPLAY_API PictureFillSymbol : public FillSymbol
{
    Q_OBJECT
public:
    explicit PictureFillSymbol(QObject *parent = nullptr);
    ~PictureFillSymbol();

    static PictureFillSymbol* createFromFilePicture(const QString& filePath);

    SymbolType type() const override;
    void accept(ISymbolVisitor& visitor) override;

    ISymbol* clone(QObject* parent = nullptr) const override;

    /*!
     * @details
     *   Prepares the display for drawing the symbol by setting pen and brush.
     */
    void setupPainter(QPainter *painter) override;
    void resetPainter(QPainter *painter) override;

    QPixmap picture() const;
    void setPicture(const QPixmap& picture);
    bool loadFromFile(const QString& filePath);

    QString source() const;

protected:
    PictureFillSymbol(const PictureFillSymbol& o, QObject *parent = nullptr);

    void drawPolygon(const Polygon &polygon, QPainter &painter) override;

private:
    QPixmap m_picture;
    QString m_source;
    QBrush m_oldBrush;
};

typedef std::unique_ptr<PictureFillSymbol> PictureFillSymbolUPtr;
