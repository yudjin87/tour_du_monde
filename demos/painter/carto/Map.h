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

#pragma once
#include <carto/IMap.h>

class DisplayTransformation;
class IDisplay;

class CARTO_API Map : public IMap
{
    Q_OBJECT
public:
    Map(IDisplay *display);
    Map(IPainterDocument *parentDocument, IDisplay *display);
    ~Map();

    QList<AbstractLayer *> layers() const override;

    IPainterDocument *document() override;
    const IPainterDocument *document() const override;
    void setDocument(IPainterDocument *parentDocument);

public slots:
    void refresh() override;
    void addLayer(AbstractLayer *layer) override;
    void insertLayer(const int index, AbstractLayer *layer) override;
    int removeLayer(AbstractLayer *layer) override;
    int getLayerIndex(const AbstractLayer *layer) const override;
    int moveLayer(AbstractLayer *layer, const int index) override;

    AbstractLayer *takeLayer(const int index) override; // removes layer without deleting it
    AbstractLayer *takeLayer(AbstractLayer *layer) override; // removes layer without deleting it
    AbstractLayer *getLayer(const int index) override;
    const AbstractLayer *getLayer(const int index) const override;
    AbstractLayer *getLayer(const QString& name) override;
    const AbstractLayer *getLayer(const QString& name) const override;

private slots:
    void onDeviceFrameChanged(const QRectF &deviceFrame);

private:
    IPainterDocument *m_parentDocument;
    IDisplay *m_display;
    QList<AbstractLayer *> m_layers;    
};

