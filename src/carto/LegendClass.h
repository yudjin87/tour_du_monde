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
#include <carto/ILegendClass.h>
#include <display/ISymbol.h>

class CARTO_API LegendClass : public ILegendClass
{
public:
    LegendClass();
    LegendClass(ISymbol* symbol);
    LegendClass(ISymbol* symbol, const QString& label);
    ~LegendClass();

    QString description() const override;
    void setDescription(const QString& description) override;

    QString label() const override;
    void setLabel(const QString& label) override;

    bool isVisible() const override;
    void setVisible(const bool isVisible) override;

    ISymbol* symbol() override;
    const ISymbol* symbol() const override;
    void setSymbol(ISymbol* symbol) override;

    ILegendClass* clone() const override;

private:
    LegendClass(const LegendClass& other);
    LegendClass& operator=(const LegendClass& other);

private:
    ISymbolUPtr m_symbol;
    QString m_description;
    QString m_label;
    bool m_visible;
};

typedef std::unique_ptr<LegendClass> LegendClassUPtr;
