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

#include "cartoPersist/CartoPersistExtension.h"
#include "cartoPersist/TourDuMondeDocumentPersist.h"

#include <carto/layers/AbstractLayer.h>
#include <carto/ITourDuMondeDocument.h>
#include <carto/IMap.h>
#include <carto/ITourDuMondeDocumentController.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtCore/QJsonObject>

CartoPersistExtension::CartoPersistExtension(QObject *parent)
    : QObject(parent)
{
}

bool CartoPersistExtension::save(IServiceLocator *locator, const QString &name, QJsonObject &obj, QString *error)
{
    if (error != nullptr)
    {
        error->clear();
    }

    ITourDuMondeDocumentController* controller = locator->locate<ITourDuMondeDocumentController>();
    controller->document()->setName(name);
    TourDuMondeDocumentPersist documentPersist(*locator);
    documentPersist.save(obj, *controller->document());

    return true;
}

bool CartoPersistExtension::load(IServiceLocator *locator, const QJsonObject &obj, QString *error)
{
    if (error != nullptr)
    {
        error->clear();
    }

    if (obj.isEmpty())
    {
        if (error) *error = "CartoPersistExtension: empty object";
        return false;
    }

    TourDuMondeDocumentPersist documentPersist(*locator);
    ITourDuMondeDocumentUPtr document = documentPersist.load(obj, error);
    if (document == nullptr)
    {
        return false;
    }

    ITourDuMondeDocumentController* controller = locator->locate<ITourDuMondeDocumentController>();
    controller->setDocument(document.release());
    controller->document()->map()->refresh();
    return true;
}
