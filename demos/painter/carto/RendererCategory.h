/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <memory>

class ILegendClass;

class RendererCategory : public QObject
{
    Q_OBJECT
public:
    explicit RendererCategory(QObject *parent = nullptr);
    RendererCategory(const QVariant& value, ILegendClass *legendClass, QObject *parent = nullptr);

    QVariant value() const;
    void setValue(const QVariant &value);

    QString label() const;
    void setLabel(const QString &label);

    const ILegendClass *legendClass() const;
    void setLegendClass(ILegendClass *legendClass);

    bool match(const QVariant &value) const;

    RendererCategory* clone() const;

private:
    RendererCategory(const RendererCategory& other);
    RendererCategory& operator=(const RendererCategory& other);

private:
    QVariant m_value;
    ILegendClass *m_legendClass; // does't take ownership
};

typedef std::unique_ptr<RendererCategory> RendererCategoryUPtr;
