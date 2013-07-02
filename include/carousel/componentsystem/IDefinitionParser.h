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

#ifndef IDEFINITIONPARSER_H
#define IDEFINITIONPARSER_H

#include <carousel/componentsystem/componentsystem_global.h>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMap>

class QByteArray;
class QIODevice;

/*!
 * @brief
 *   The IDefinitionParser interface provides easy-to-use interface to read and parse
 *   component description information.
 * @details
 *   This interface is used by the ProxyComponent to obtain meta information about
 *   the loaded component. If read() returns @a true you can use parsed information
 *   through the accessor methods.
 *
 *   Known realizations: XmlDefinitionParser.
 *   Further realizations: JsonDefinitionParser.
 *
 * @todo write about <>Provider, who instantiates IDefinitionParser using service locator.
 */
class COMP_API IDefinitionParser
{
public:
    typedef QMap<QString, QString> ParentsList;

    IDefinitionParser(){}
    virtual ~IDefinitionParser(){}

    /*!
     * @details
     *   Gets the error occurred during reading (method read()).
     *   Returns empty string if error was not occurred.
     */
    virtual const QString &error() const = 0;

    /*!
     * @details
     *   Gets the component Id.
     */
    virtual const QString &componentShortName() const = 0;

    /*!
     * @details
     *   Gets the parsed component name.
     */
    virtual const QString &componentName() const = 0;

    /*!
     * @details
     *   Gets the parsed component location (relative or absolyte) without library extension.
     */
    virtual const QString &componentLocation() const = 0;

    /*!
     * @details
     *   Gets the parsed component description.
     *   @a Optional, can be empty string.
     */
    virtual const QString &description() const = 0;

    /*!
     * @details
     *   Gets the parsed component parents names and versions.
     *   @a Optional, can be empty list.
     */
    virtual const ParentsList &parents() const = 0;

    /*!
     * @details
     *   Gets the parsed product name.
     *   @a Optional, can be empty string.
     */
    virtual const QString &productName() const = 0;

    /*!
     * @details
     *   Gets the the name of component's provider, the person or company,
     *   who creates this component.
     */
    virtual const QString &provider() const = 0;

    /*!
     * @details
     *   Gets the string representation of version of a component.
     */
    virtual const QString &version() const = 0;

    /*!
     * @details
     *   This function parses the string @a text and sets component meta information.
     *
     *   If a parse error occurs (incorrect format, required information is missed, etc),
     *   this function returns @a false. The error message could be got through error() method.
     */
    virtual bool read(const QString &text) = 0;

    /*!
     * @details
     * @overload
     */
    virtual bool read(const QByteArray &data) = 0;

    /*!
     * @details
     * @overload
     */
    virtual bool read(QIODevice* dev) = 0;
};

#endif // IDEFINITIONPARSER_H
