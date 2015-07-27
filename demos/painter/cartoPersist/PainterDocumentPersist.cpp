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
#include <carto/IPainterDocument.h>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

PainterDocumentPersist::PainterDocumentPersist(QObject *parent)
    : QObject(parent)
{
}

void PainterDocumentPersist::save(QJsonObject &obj, const IPainterDocument &document)
{
    obj.insert("documentName", document.name());
}

bool PainterDocumentPersist::load(const QJsonObject &obj, IPainterDocument &document, QString *error)
{
    const QVariant docName = obj.value("documentName");
    if (!docName.isValid())
    {
        if (error) *error = "Invalid document name";
        return false;
    }

    document.setName(docName.toString());
    return true;
}

