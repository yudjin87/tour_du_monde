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

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("CarouselPersistenceDelegate");
}

CarouselPersistenceDelegate::CarouselPersistenceDelegate(IServiceLocator *locator, QObject *parent)
    : IPersistenceDelegate()
    , m_locator(locator)
{
    setParent(parent);
}

bool CarouselPersistenceDelegate::save(const QList<IComponent *> &components, QByteArray &saveStream)
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

        bool result = saveExtension(extension, data);
        Log.d(QString("Saving \"%1\" component... %2").arg(component->name()).arg(result ? "Success" : "Fail"));

        if (!result)
            return false;

        componentJson.insert("data", data);
        componentsJson.append(componentJson);
    }

    root.insert("components", componentsJson);
    document.setObject(root);
    saveStream = document.toJson();

    return true;
}

bool CarouselPersistenceDelegate::load(const QList<IComponent *> &components, const QByteArray &loadStream)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(loadStream, &error);
    if (error.error != QJsonParseError::NoError) {
        Log.e(error.errorString());
        return false;
    }

    QJsonObject root = doc.object();
    QJsonArray componentsJson = root.value("components").toArray();

    for (int i = 0; i < componentsJson.count(); ++i) {
        QJsonObject compJson = componentsJson.at(i).toObject();
        QString compName = compJson.value("name").toString();
        IPersistExtension *extension = extensionByName(components, compName);
        if (extension == nullptr)
            continue;

        bool result = loadExtension(extension, compJson.value("data").toObject());
        Log.d(QString("Loading \"%1\" component... %2").arg(compName).arg(result ? "Success" : "Fail"));

        if (!result)
            return false;
    }

    return true;
}

bool CarouselPersistenceDelegate::saveExtension(IPersistExtension *extension, QJsonObject &toWrite)
{
    QString error;
    if (extension->save(m_locator, toWrite, &error))
        return true;

    Log.e(QString("Failed to load component: %1").arg(error));
    return false;
}

bool CarouselPersistenceDelegate::loadExtension(IPersistExtension *extension, const QJsonObject &json)
{
    QString error;
    if (extension->load(m_locator, json, &error))
        return true;

    Log.e(QString("Failed to load component: %1").arg(error));
    return false;
}

IPersistExtension *CarouselPersistenceDelegate::extensionByName(const QList<IComponent *> &components, const QString &compName)
{
    for (IComponent *component : components)
        if (component->name() == compName)
            return component->extension<IPersistExtension>();

    return nullptr;
}

IServiceLocator *CarouselPersistenceDelegate::locator()
{
    return m_locator;
}


