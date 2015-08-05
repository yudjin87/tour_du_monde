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
#include "cartoPersist/TourDeMondeDocumentPersist.h"

#include <carto/AbstractLayer.h>
#include <carto/ITourDeMondeDocument.h>
#include <carto/IMap.h>
#include <carto/ITourDeMondeDocumentController.h>
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

    ITourDeMondeDocumentController* controller = locator->locate<ITourDeMondeDocumentController>();
    controller->document()->setName(name);
    TourDeMondeDocumentPersist documentPersist(*locator);
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
        return nullptr;
    }

    TourDeMondeDocumentPersist documentPersist(*locator);
    ITourDeMondeDocumentUPtr document = documentPersist.load(obj, error);
    if (document == nullptr)
    {
        return false;
    }

    ITourDeMondeDocumentController* controller = locator->locate<ITourDeMondeDocumentController>();
    controller->setDocument(document.release());
    controller->document()->map()->refresh();
    return true;
}
