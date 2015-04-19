/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
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

#pragma once
#include <carto/IFeatureRenderer.h>
#include <carto/ILegendGroup.h>

#include <display/ISymbol.h>

#include <QtCore/QVector>

class CARTO_API SimpleRenderer : public IFeatureRenderer
{
    Q_OBJECT
public:
    SimpleRenderer(QObject *parent = nullptr);
    ~SimpleRenderer();

    void draw(const QVector<IFeature *> &features, QPainter *painter) override;

    ISymbol *symbol();
    const ISymbol *symbol() const;

    // takes ownership
    void setSymbol(ISymbol *symbol);

    ILegendGroup *legend() override;
    const ILegendGroup *legend() const override;

    void accept(IFeatureRendererVisitor& visitor) override;

    IFeatureRenderer* clone() const override;

private:
    SimpleRenderer(const SimpleRenderer& other);
    SimpleRenderer& operator=(const SimpleRenderer& other);

private:
    ILegendGroupUPtr m_legend;
};

