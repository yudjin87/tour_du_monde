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

#include "carto/SimpleRenderer.h"
#include "carto/LegendGroup.h"
#include "carto/LegendClass.h"
#include "carto/IFeatureRendererVisitor.h"
#include "carto/DefaultSymbol.h"

#include <display/ISymbol.h>
#include <geodatabase/IFeature.h>

#include <QtGui/QPainter>

SimpleRenderer::SimpleRenderer(QObject *parent)
    : IFeatureRenderer(parent)
    , m_legend(new LegendGroup())
{
}

SimpleRenderer::SimpleRenderer(const Geometry::Type forType, QObject *parent)
    : IFeatureRenderer(parent)
    , m_legend(new LegendGroup())
{
    ISymbol* defaultSymbol = StyleGallery::defaultSymbol(forType);
    setSymbol(defaultSymbol);
}

SimpleRenderer::SimpleRenderer(const SimpleRenderer &other)
    : IFeatureRenderer()
    , m_legend(other.m_legend->clone())
{
}

SimpleRenderer &SimpleRenderer::operator=(const SimpleRenderer &other)
{
    if (this == &other)
    {
        return *this;
    }

    m_legend.reset(other.m_legend->clone());

    return *this;
}

SimpleRenderer::~SimpleRenderer()
{
}

void SimpleRenderer::draw(const QVector<IFeature *> &features, QPainter *painter)
{
    ISymbol *symb = symbol();
    if (symb == nullptr)
    {
        return;
    }

    symb->setupPainter(painter);
    for (const IFeature *feature : features) {
        symb->draw(feature->geometry(), painter);
    }

    symb->resetPainter(painter);
}

ISymbol *SimpleRenderer::symbol()
{
    return const_cast<ISymbol *>(const_cast<const SimpleRenderer*>(this)->symbol());
}

const ISymbol *SimpleRenderer::symbol() const
{
    if (m_legend->classCount() == 0)
    {
        return nullptr;
    }

    return m_legend->getClass(0)->symbol();
}

void SimpleRenderer::setSymbol(ISymbol *symbol)
{
    m_legend->clearClasses();
    m_legend->addClass(new LegendClass(symbol));
    //emit symbolChanged(symbol);
}

ILegendGroup *SimpleRenderer::legend()
{
    return m_legend.get();
}

const ILegendGroup *SimpleRenderer::legend() const
{
    return m_legend.get();
}

void SimpleRenderer::accept(IFeatureRendererVisitor &visitor)
{
    visitor.visit(*this);
}

IFeatureRenderer *SimpleRenderer::clone() const
{
    return new SimpleRenderer(*this);
}
