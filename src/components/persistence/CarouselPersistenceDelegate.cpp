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

#include "CarouselPersistenceDelegate.h"
#include "IPersistExtension.h"

#include <carousel/componentsystem/IComponent.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("CarouselPersistenceDelegate");
}

//------------------------------------------------------------------------------
CarouselPersistenceDelegate::CarouselPersistenceDelegate(QObject *parent)
    : IPersistenceDelegate()
{
    setParent(parent);
}

//------------------------------------------------------------------------------
void CarouselPersistenceDelegate::save(IServiceLocator *locator, const QList<IComponent *> &components, QByteArray &saveStream)
{
    QJsonDocument document;
    QJsonObject root;
    root.insert("projectInfo", QCoreApplication::applicationName());
    QJsonArray componentsJson;

    for (IComponent *component : components) {
        IPersistExtension *extension = component->extension<IPersistExtension>();
        if (extension == nullptr)
            continue;

        QJsonObject componentJson;
        componentJson.insert("name", component->name());
        QJsonObject data;
        saveExtension(locator, extension, data);
        componentJson.insert("data", data);
        componentsJson.append(componentJson);
    }

    root.insert("components", componentsJson);
    document.setObject(root);
    saveStream = document.toJson();
}

//------------------------------------------------------------------------------
void CarouselPersistenceDelegate::load(IServiceLocator *locator, const QList<IComponent *> &components, const QByteArray &loadStream)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(loadStream, &error);
    if (error.error != QJsonParseError::NoError) {
        Log.e(error.errorString());
        return;
    }

    QJsonObject root = doc.object();
    QJsonArray componentsJson = root.value("components").toArray();

    for (int i = 0; i < componentsJson.count(); ++i) {
        QJsonObject compJson = componentsJson.at(i).toObject();
        QString compName = compJson.value("name").toString();
        IPersistExtension *extension = extensionByName(components, compName);
        if (extension != nullptr)
            loadExtension(locator, extension, compJson.value("data").toObject());
    }
}

//------------------------------------------------------------------------------
void CarouselPersistenceDelegate::saveExtension(IServiceLocator *locator, IPersistExtension *extension, QJsonObject &toWrite)
{
    extension->save(locator, toWrite);
}

//------------------------------------------------------------------------------
void CarouselPersistenceDelegate::loadExtension(IServiceLocator *locator, IPersistExtension *extension, const QJsonObject &json)
{
    extension->load(locator, json);
}

//------------------------------------------------------------------------------
IPersistExtension *CarouselPersistenceDelegate::extensionByName(const QList<IComponent *> &components, const QString &compName)
{
    for (IComponent *component : components)
        if (component->name() == compName)
            return component->extension<IPersistExtension>();
}

//------------------------------------------------------------------------------

