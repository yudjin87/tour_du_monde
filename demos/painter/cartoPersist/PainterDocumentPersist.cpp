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

#include "cartoPersist/PainterDocumentPersist.h"
#include "cartoPersist/MapPersist.h"
#include <carto/IMap.h>
#include <carto/PainterDocument.h>
#include <carousel/utils/IServiceLocator.h>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

PainterDocumentPersist::PainterDocumentPersist(IServiceLocator &serviceLocator)
    : m_serviceLocator(serviceLocator)
{
}

void PainterDocumentPersist::save(QJsonObject &obj, const IPainterDocument &document)
{
    obj.insert("documentName", document.name());

    QJsonObject jsonMap;
    MapPersist mapPersist(m_serviceLocator);
    mapPersist.save(jsonMap, *document.map());

    obj.insert("map", jsonMap);
}

IPainterDocumentUPtr PainterDocumentPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "PainterDocumentPersist: empty object";
        return nullptr;
    }

    IPainterDocumentUPtr document(new PainterDocument());
    const QVariant docName = obj.value("documentName");
    if (!docName.isValid())
    {
        if (error) *error = "Invalid document name";
        return nullptr;
    }

    document->setName(docName.toString());

    const QJsonValue jsonMap = obj.value("map");
    if (!jsonMap.isObject())
    {
        if (error) *error = "Invalid \"map\" object";
        return nullptr;
    }

    MapPersist mapPersist(m_serviceLocator);
    IMapUPtr map = mapPersist.load(jsonMap.toObject(), error);
    if (map == nullptr)
    {
        return nullptr;
    }

    document->addMap(map.release());

    return document;
}
