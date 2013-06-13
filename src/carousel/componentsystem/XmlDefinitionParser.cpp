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

#include "XmlDefinitionParser.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("XmlDefinitionParser");
}

//------------------------------------------------------------------------------
static const char *COMPONENT_NAME_ATTRIBUTE = "name";
static const char *COMPONENT_ID_ATTRIBUTE = "id";
static const char *PARENT_COMPONENT_NAME_ATTRIBUTE = "name";

static const char *COMPONENT_TAG = "component";
static const char *COMPONENT_LOCATION_TAG = "location";
static const char *DESCRIPTION_TAG = "description";
static const char *PRODUCT_NAME_TAG = "productName";
static const char *PROVIDER_NAME_TAG = "provider";
static const char *PARENT_COMPONENT_TAG = "parentComponent";
static const char *PARENTS_TAG = "parents";

//------------------------------------------------------------------------------
XmlDefinitionParser::XmlDefinitionParser(QObject *parent)
    : QObject(parent)
    , m_componentName("")
    , m_componentId("")
    , m_componentLocation("")
    , m_description("")
    , m_productName("")
    , m_provider("")
    , m_error("")
    , m_parents()
{
}

//------------------------------------------------------------------------------
XmlDefinitionParser::~XmlDefinitionParser()
{
    clear();
}

//------------------------------------------------------------------------------
const QString &XmlDefinitionParser::error() const
{
    return m_error;
}

//------------------------------------------------------------------------------
bool XmlDefinitionParser::read(const QString &text)
{
    clear();
    QDomDocument doc("ComponentDescriptionDocument");
    if (!doc.setContent(text, &m_error)) {
        Log.e(QString("Cannot read definition. %1").arg(m_error));
        return false;
    }

    return parseXml(doc);
}

//------------------------------------------------------------------------------
bool XmlDefinitionParser::read(const QByteArray &text)
{
    clear();
    QDomDocument doc("ComponentDescriptionDocument");
    if (!doc.setContent(text, &m_error)) {
        Log.e(QString("Cannot read definition. %1").arg(m_error));
        return false;
    }

    return parseXml(doc);
}

//------------------------------------------------------------------------------
bool XmlDefinitionParser::read(QIODevice *dev)
{
    clear();
    QDomDocument doc("ComponentDescriptionDocument");
    if (!doc.setContent(dev, &m_error)) {
        Log.e(QString("Cannot read definition. %1").arg(m_error));
        return false;
    }

    return parseXml(doc);
}

//------------------------------------------------------------------------------
const QString &XmlDefinitionParser::componentId() const
{
    return m_componentId;
}

//------------------------------------------------------------------------------
const QString &XmlDefinitionParser::componentName() const
{
    return m_componentName;
}

//------------------------------------------------------------------------------
const QString &XmlDefinitionParser::componentLocation() const
{
    return m_componentLocation;
}

//------------------------------------------------------------------------------
const QString &XmlDefinitionParser::description() const
{
    return m_description;
}

//------------------------------------------------------------------------------
const QStringList &XmlDefinitionParser::parents() const
{
    return m_parents;
}

//------------------------------------------------------------------------------
const QString &XmlDefinitionParser::productName() const
{
    return m_productName;
}

//------------------------------------------------------------------------------
const QString &XmlDefinitionParser::provider() const
{
    return m_provider;
}

//------------------------------------------------------------------------------
bool XmlDefinitionParser::parseXml(QDomDocument &document)
{
    QDomElement root = document.documentElement();
    if (root.nodeName() != COMPONENT_TAG) {
        m_error = QString("Root tag is wrong. \"%1\" is expected").arg(COMPONENT_TAG);
        Log.e(QString("Error during definition parsing. %1").arg(m_error));
        return false;
    }

    if (!root.hasAttribute(COMPONENT_ID_ATTRIBUTE)){
        m_error = QString("Component Id attribute is wrong. \"%1\" is expected").arg(COMPONENT_ID_ATTRIBUTE);
        Log.e(QString("Error during definition parsing. %1").arg(m_error));
        return false;
    }

    m_componentId = root.attribute(COMPONENT_ID_ATTRIBUTE).trimmed();
    if (m_componentId.isEmpty()){
        m_error = "Component Id is empty";
        Log.e(QString("Error during definition parsing. %1").arg(m_error));
        return false;
    }

    if (!root.hasAttribute(COMPONENT_NAME_ATTRIBUTE)){
        m_error = QString("Component name attribute is wrong. \"%1\" is expected").arg(COMPONENT_NAME_ATTRIBUTE);
        Log.e(QString("Error during definition parsing. %1").arg(m_error));
        return false;
    }

    m_componentName = root.attribute(COMPONENT_NAME_ATTRIBUTE).trimmed();
    if (m_componentName.isEmpty()){
        m_error = "Component name is empty";
        Log.e(QString("Error during definition parsing. %1").arg(m_error));
        return false;
    }

    QDomNode description = root.elementsByTagName(DESCRIPTION_TAG).at(0);
    m_description = description.toElement().text();

    QDomNode productName = root.elementsByTagName(PRODUCT_NAME_TAG).at(0);
    m_productName = productName.toElement().text();

    QDomNode provider = root.elementsByTagName(PROVIDER_NAME_TAG).at(0);
    m_provider = provider.toElement().text();

    QDomNode location = root.elementsByTagName(COMPONENT_LOCATION_TAG).at(0);
    m_componentLocation = location.toElement().text();

    QDomNode parents = root.elementsByTagName(PARENTS_TAG).at(0);
    QDomNodeList parentsNode = parents.toElement().elementsByTagName(PARENT_COMPONENT_TAG);
    for (int i = 0; i < parentsNode.size(); ++i)
        m_parents.append(parentsNode.at(i).toElement().attribute(PARENT_COMPONENT_NAME_ATTRIBUTE));

    return true;
}

//------------------------------------------------------------------------------
void XmlDefinitionParser::clear()
{
    m_componentName = "";
    m_componentLocation = "";
    m_description = "";
    m_productName = "";
    m_error = "";
    m_parents.clear();
}

//------------------------------------------------------------------------------
