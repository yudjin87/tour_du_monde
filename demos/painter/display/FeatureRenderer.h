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

#ifndef FEATURERENDERER_H
#define FEATURERENDERER_H

#include "display_api.h"

#include <QtCore/QVector>
#include <QtCore/QObject>

class IFeature;
class ISymbol;
class QPainter;

class DISPLAY_API FeatureRenderer : public QObject
{
    Q_OBJECT

    /*!
     * @details
     *   Gets or sets the symbol used to draw all features in a layer.
     *
     *   The symbol type matches the geometry of the layer being rendered,
     *   so marker symbols are used to draw point layers, line symbols are used
     *   to draw line features, and fill symbols are used to draw polygon features.
     *
     * @note that renderer does not take ownership for the symbol.
     */
    Q_PROPERTY(ISymbol *symbol READ symbol WRITE setSymbol)

public:
    FeatureRenderer(QObject *parent = nullptr);
    ~FeatureRenderer();

    /*!
     * @details
     *   Draws features from the specified cursor on the given device.
     *
     *   This method is typically called by the framework to renderer features
     *   to a device. This could be in response to a refresh on the map.
     *   This method typically iterates through all the features and renders each
     *   feature with an appropriate symbol.
     */
    void draw(const QVector<IFeature *> &features, QPainter *painter);

    ISymbol *symbol();
    const ISymbol *symbol() const;
    void setSymbol(ISymbol *symbol);

private:
    ISymbol *m_symbol;
};

#endif // FEATURERENDERER_H

