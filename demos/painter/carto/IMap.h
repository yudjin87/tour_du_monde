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

#ifndef IMAP_H
#define IMAP_H

#include <carto/carto_api.h>

#include <QtCore/QList>
#include <QtCore/QObject>

class AbstractLayer;
class IPainterDocument;

class CARTO_API IMap : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IPainterDocument *document READ document)
    Q_PROPERTY(QList<AbstractLayer *> layers READ layers)
public:
    IMap(){}

    virtual QList<AbstractLayer *> layers() const = 0;

    virtual IPainterDocument *document() = 0;
    virtual const IPainterDocument *document() const = 0;

public slots:
    virtual void addLayer(AbstractLayer *layer) = 0;
    virtual void insertLayer(const int index, AbstractLayer *layer) = 0;
    virtual int removeLayer(AbstractLayer *layer) = 0;
    virtual AbstractLayer *takeLayer(const int index) = 0; // removes layer without deleting it
    virtual AbstractLayer *getLayer(const int index) = 0;
    virtual const AbstractLayer *getLayer(const int index) const = 0;
    virtual AbstractLayer *getLayer(const QString& name) = 0;
    virtual const AbstractLayer *getLayer(const QString& name) const = 0;
    virtual void moveLayer(AbstractLayer *layer, const int index) = 0;

    virtual void refresh() = 0;

signals:
    void layerAdded(AbstractLayer *layer, const int index);
    void layerRemoved(AbstractLayer *layer, const int index);
    void refreshed();

private:
    Q_DISABLE_COPY(IMap)
};

#endif // IMAP_H
