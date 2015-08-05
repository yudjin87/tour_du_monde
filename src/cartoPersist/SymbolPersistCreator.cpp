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

#include "cartoPersist/SymbolPersistCreator.h"
#include "cartoPersist/SimpleFillSymbolPersist.h"
#include "cartoPersist/PictureFillSymbolPersist.h"
#include "cartoPersist/SimpleLineSymbolPersist.h"
#include "cartoPersist/SimpleMarkerSymbolPersist.h"
#include "cartoPersist/PictureMarkerSymbolPersist.h"

#include <display/SimpleFillSymbol.h>
#include <display/PictureFillSymbol.h>
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
    case SymbolType::SimpleLineSymbol:
        return ISymbolPersistUPtr(new SimpleLineSymbolPersist());
    case SymbolType::SimpleMarkerSymbol:
        return ISymbolPersistUPtr(new SimpleMarkerSymbolPersist());
    case SymbolType::PictureMarkerSymbol:
        return ISymbolPersistUPtr(new PictureMarkerSymbolPersist());
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

