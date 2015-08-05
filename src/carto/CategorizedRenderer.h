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
#include <carto/IFeatureRenderer.h>
#include <carto/ILegendGroup.h>
#include <carto/IRendererCategoryCollection.h>

#include <display/ISymbol.h>

class CARTO_API CategorizedRenderer : public IFeatureRenderer
{
    Q_OBJECT
public:
    CategorizedRenderer(QObject *parent = nullptr);
    CategorizedRenderer(ILegendGroupUPtr legend, IRendererCategoryCollectionUPtr categories);

    ~CategorizedRenderer();

    RendererType type() const override;

    void draw(const QVector<IFeature *> &features, QPainter *painter) override;

    const IRendererCategoryCollection& categories() const;

    ILegendGroup *legend() override;
    const ILegendGroup *legend() const override;

    void accept(IFeatureRendererVisitor& visitor) override;

    IFeatureRenderer* clone() const override;

    void setCategoryFieldIndex(const int index);
    int categoryFieldIndex() const;

public slots:
    // takes ownership for symbol
    void addCategory(const QVariant& value, const QString& label, ISymbol *symbol);

    ISymbol* symbol(const QVariant& value);
    const ISymbol* symbol(const QVariant& value) const;

    ILegendClass *legendClass(const QVariant& value);
    const ILegendClass *legendClass(const QVariant& value) const;

signals:
    void categoryAdded();
    void categoryRemoved();

private:
    CategorizedRenderer(const CategorizedRenderer& other);
    CategorizedRenderer& operator=(const CategorizedRenderer& other);

private:
    ILegendGroupUPtr m_legend;
    int m_categoryFieldIndex;
    IRendererCategoryCollectionUPtr m_categories;
};

typedef std::unique_ptr<CategorizedRenderer> CategorizedRendererUPtr;
