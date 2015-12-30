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

#include "carto/CategorizedRenderer.h"
#include "carto/IFeatureRendererVisitor.h"
#include "carto/IFeatureRendererVisitor.h"
#include "carto/LegendGroup.h"
#include "carto/LegendClass.h"
#include "carto/RendererCategory.h"
#include "carto/RendererCategoryCollection.h"

#include <geodatabase/IFeatureClass.h>
#include <geodatabase/IFeature.h>
#include <geodatabase/IRecord.h>

#include <carousel/logging/LoggerFacade.h>

#include <algorithm>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("Cat.Renderer");
}

CategorizedRenderer::CategorizedRenderer(QObject *parent)
    : IFeatureRenderer(parent)
    , m_legend(new LegendGroup())
    , m_categoryFieldIndex(0)
    , m_categories(new RendererCategoryCollection())
{
}

CategorizedRenderer::CategorizedRenderer(ILegendGroupUPtr legend, IRendererCategoryCollectionUPtr categories)
    : IFeatureRenderer()
    , m_legend(std::move(legend))
    , m_categoryFieldIndex(0)
    , m_categories(std::move(categories))
{
}

CategorizedRenderer::CategorizedRenderer(const CategorizedRenderer &other)
    : IFeatureRenderer()
    , m_legend(other.m_legend->clone())
    , m_categoryFieldIndex(other.m_categoryFieldIndex)
    , m_categories(other.m_categories->clone(*m_legend))
{
}

CategorizedRenderer &CategorizedRenderer::operator=(const CategorizedRenderer &other)
{
    if (this == &other)
    {
        return *this;
    }

    m_legend.reset(other.m_legend->clone());
    m_categoryFieldIndex = other.m_categoryFieldIndex;
    m_categories = IRendererCategoryCollectionUPtr(other.m_categories->clone(*m_legend));

    return *this;
}

CategorizedRenderer::~CategorizedRenderer()
{
}

RendererType CategorizedRenderer::type() const
{
    return RendererType::Categorized;
}

void CategorizedRenderer::draw(const QVector<IFeature *> &features, QPainter *painter)
{
    for (const IFeature *feature : features)
    {
        const IRecord* rec = feature->record();
        const QVariant& featureValue = rec->value(m_categoryFieldIndex);
        ILegendClass* legend = legendClass(featureValue);
        if (legend == nullptr)
        {
            Log.d(QString("No symbol for value \"%1\"").arg(featureValue.toString()));
            continue;
        }

        if (!legend->isVisible())
        {
            continue;
        }

        ISymbol *symbolForCategory = legend->symbol();
        symbolForCategory->setupPainter(painter);
        symbolForCategory->draw(feature->geometry(), painter);
        symbolForCategory->resetPainter(painter);
    }
}

const IRendererCategoryCollection &CategorizedRenderer::categories() const
{
    return *m_categories;
}

ILegendGroup *CategorizedRenderer::legend()
{
    return m_legend.get();
}

const ILegendGroup *CategorizedRenderer::legend() const
{
    return m_legend.get();
}

void CategorizedRenderer::accept(IFeatureRendererVisitor &visitor)
{
    visitor.visit(*this);
}

IFeatureRenderer *CategorizedRenderer::clone() const
{
    return new CategorizedRenderer(*this);
}

void CategorizedRenderer::setCategoryFieldIndex(const int index)
{
    m_categoryFieldIndex = index;
}

int CategorizedRenderer::categoryFieldIndex() const
{
    return m_categoryFieldIndex;
}

void CategorizedRenderer::addCategory(const QVariant &value, const QString &label, ISymbol *symbol)
{
    const IRendererCategory* existedCategory = m_categories->findByValue(value);
    if (existedCategory != nullptr)
    {
        Log.w(QString("Value \"%1\" is already existed. Symbol won't be changed").arg(value.toString()));
        return;
    }

    ILegendClass* legendClass = new LegendClass(symbol, label);
    m_categories->addCategory(new RendererCategory(value, legendClass));
    m_legend->addClass(legendClass);
}

ISymbol *CategorizedRenderer::symbol(const QVariant &value)
{
    return const_cast<ISymbol *>(const_cast<const CategorizedRenderer*>(this)->symbol(value));
}

const ISymbol *CategorizedRenderer::symbol(const QVariant &value) const
{
    const ILegendClass* legend= legendClass(value);
    if (legend == nullptr)
    {
        return nullptr;
    }

    return legend->symbol();
}

ILegendClass *CategorizedRenderer::legendClass(const QVariant &value)
{
    return const_cast<ILegendClass*>(const_cast<const CategorizedRenderer*>(this)->legendClass(value));
}

const ILegendClass *CategorizedRenderer::legendClass(const QVariant &value) const
{
    const IRendererCategory* category = m_categories->findByValue(value);
    if (category == nullptr)
    {
        return nullptr;
    }

    const ILegendClass* legendClass = category->legendClass();
    return legendClass;
}


