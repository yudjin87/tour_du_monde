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
#include <carto/ILegendGroup.h>
#include <carto/ILegendClass.h>

#include <vector>

class CARTO_API LegendGroup : public ILegendGroup
{
    Q_OBJECT
public:
    LegendGroup();
    ~LegendGroup();

    QString heading() const override;
    void setHeading(const QString& heading) override;

    bool isEditable() const override;
    void setEditable(const bool editable) override;

    bool isVisible() const override;
    void setVisible(const bool visible) override;

    size_t classCount() const override;

    ILegendGroup* clone() const override;

    ILegendClassVector::const_iterator begin() const override;
    ILegendClassVector::const_iterator end() const override;

public slots:
    ILegendClass* getClass(const size_t index) override;
    const ILegendClass* getClass(const size_t index) const override;
    ILegendClass* getClass(const QString& label) override;
    const ILegendClass* getClass(const QString& label) const override;

    void addClass(ILegendClass* legendClass) override;
    void insertClass(const int index, ILegendClass* legendClass) override;
    void clearClasses() override;
    void removeClass(ILegendClass *legendClass) override;
    ILegendClass* takeClass(const int index) override;

private:
    LegendGroup(const LegendGroup& other);
    LegendGroup& operator=(const LegendGroup& other);

private:
    std::vector<ILegendClassUPtr> m_legendClasses;
    bool m_editable;
    bool m_visible;
    QString m_heading;

};

typedef std::unique_ptr<LegendGroup> LegendGroupUPtr;
