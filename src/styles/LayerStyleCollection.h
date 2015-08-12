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

#include <styles/ILayerStyleCollection.h>

class LayerStyleCollection : public ILayerStyleCollection
{
    Q_OBJECT
public:
    LayerStyleCollection();
    ILayerStyleCollection* clone() const override;

    void add(IFeatureLayerStyleUPtr layerStyle) override;

    ILayerStyleVector::const_iterator begin() const override;
    ILayerStyleVector::const_iterator end() const override;

public slots:
    void add(IFeatureLayerStyle* layerStyle) override;
    IFeatureLayerStyle* styleByName(const QString& name) const override;
    IFeatureLayerStyle* styleByLayerName(const QString& layerName) const override;

private:
    LayerStyleCollection(const LayerStyleCollection& other);
    LayerStyleCollection& operator=(const LayerStyleCollection& other);

private:
    ILayerStyleVector m_styles;
};

typedef std::unique_ptr<LayerStyleCollection> LayerStyleCollectionUPtr;
