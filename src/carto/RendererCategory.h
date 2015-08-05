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

#include <carto/IRendererCategory.h>

class CARTO_API RendererCategory : public IRendererCategory
{
    Q_OBJECT
public:
    explicit RendererCategory();
    RendererCategory(const QVariant& value, ILegendClass *legendClass);

    QVariant value() const override;
    void setValue(const QVariant &value) override;

    QString label() const override;
    void setLabel(const QString &label) override;

    ISymbol* symbol() override;
    const ISymbol* symbol() const override;
    void setSymbol(ISymbol* symbol) override;

    const ILegendClass *legendClass() const override;
    void setLegendClass(ILegendClass *legendClass) override;

    bool match(const QVariant &value) const override;

    RendererCategory* clone() const override;

private:
    RendererCategory(const RendererCategory& other);
    RendererCategory& operator=(const RendererCategory& other);

private:
    QVariant m_value;
    ILegendClass *m_legendClass; // does't take ownership
};

typedef std::unique_ptr<RendererCategory> RendererCategoryUPtr;
