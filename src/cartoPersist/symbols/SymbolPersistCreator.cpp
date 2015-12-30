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

#include "cartoPersist/symbols/SymbolPersistCreator.h"
#include "cartoPersist/symbols/SimpleFillSymbolPersist.h"
#include "cartoPersist/symbols/GradientFillSymbolPersist.h"
#include "cartoPersist/symbols/PictureFillSymbolPersist.h"
#include "cartoPersist/symbols/SimpleLineSymbolPersist.h"
#include "cartoPersist/symbols/SimpleMarkerSymbolPersist.h"
#include "cartoPersist/symbols/PictureMarkerSymbolPersist.h"
#include "cartoPersist/symbols/SimpleTextSymbolPersist.h"

#include <display/SimpleFillSymbol.h>
#include <display/PictureFillSymbol.h>
#include <display/GradientFillSymbol.h>
#include <display/SimpleLineSymbol.h>
#include <display/SimpleMarkerSymbol.h>
#include <display/PictureMarkerSymbol.h>

SymbolPersistCreator::SymbolPersistCreator()
    : ISymbolVisitor()
    , m_persist()
{
}

ISymbolPersistUPtr SymbolPersistCreator::create(const ISymbol &forSymbol)
{
    const_cast<ISymbol&>(forSymbol).accept(*this);
    return std::move(m_persist);
}

ISymbolPersistUPtr SymbolPersistCreator::create(const SymbolType type)
{
    switch (type)
    {
    case SymbolType::SimpleFillSymbol:
        return ISymbolPersistUPtr(new SimpleFillSymbolPersist());
    case SymbolType::PictureFillSymbol:
        return ISymbolPersistUPtr(new PictureFillSymbolPersist());
    case SymbolType::GradientFillSymbol:
        return ISymbolPersistUPtr(new GradientFillSymbolPersist());
    case SymbolType::SimpleLineSymbol:
        return ISymbolPersistUPtr(new SimpleLineSymbolPersist());
    case SymbolType::SimpleMarkerSymbol:
        return ISymbolPersistUPtr(new SimpleMarkerSymbolPersist());
    case SymbolType::PictureMarkerSymbol:
        return ISymbolPersistUPtr(new PictureMarkerSymbolPersist());
    case SymbolType::SimpleTextSymbol:
        return ISymbolPersistUPtr(new SimpleTextSymbolPersist());
    }

    return nullptr;
}

void SymbolPersistCreator::visit(SimpleFillSymbol &symbol)
{
    m_persist.reset(new SimpleFillSymbolPersist(symbol));
}

void SymbolPersistCreator::visit(PictureFillSymbol &symbol)
{
    m_persist.reset(new PictureFillSymbolPersist(symbol));
}

void SymbolPersistCreator::visit(GradientFillSymbol &symbol)
{
    m_persist.reset(new GradientFillSymbolPersist(symbol));
}

void SymbolPersistCreator::visit(SimpleLineSymbol &symbol)
{
    m_persist.reset(new SimpleLineSymbolPersist(symbol));
}

void SymbolPersistCreator::visit(SimpleMarkerSymbol &symbol)
{
    m_persist.reset(new SimpleMarkerSymbolPersist(symbol));
}

void SymbolPersistCreator::visit(PictureMarkerSymbol &symbol)
{
    m_persist.reset(new PictureMarkerSymbolPersist(symbol));
}

void SymbolPersistCreator::visit(SimpleTextSymbol &symbol)
{
    m_persist.reset(new SimpleTextSymbolPersist(symbol));
}

