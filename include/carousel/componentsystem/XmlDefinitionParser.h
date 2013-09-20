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

#ifndef XMLDEFINITIONPARSER_H
#define XMLDEFINITIONPARSER_H

#include <carousel/componentsystem/IDefinitionParser.h>

#include <QtCore/QObject>
#include <QtCore/QString>

class QDomDocument;

/*!
 * @brief
 *   The XmlDefinitionParser class parses component definition using xml format.
 * @details
 *   The XML should be like such one:
 * @code
 *   <component name="MyComponent" shortName="Visible name of component">
 *     <version>1.2.3.4</version>
 *     <productName>My super product</productName>
 *     <provider>CarouselTeam</provider>
 *     <description>Ultra feature</description>
 *     <location>./MyComponent</location>
 *     <parents>
 *         <parentComponent name="ComponentA"/>
 *         <parentComponent name="ComponentC"/>
 *         <parentComponent name="ComponentB"/>
 *     </parents>
 *   </component>
 * @endcode
 *   Where @a name attribute is a componentName(), @a productName tag is a
 *   productName(), and so on.
 *
 *   The XmlDefinitionParser expects that root element is named @a component and has
 *   non-empty attribute @a name. All other tags are optional,
 *   so minimalistic xml-definition is like
 * @code
 *   <component name="MyComponent>
 *   </component>
 * @endcode
 *
 *   If version was not set, a default one (1.0.0) will be set during a ComponentDefinition
 *   creation.
 */
class COMP_API XmlDefinitionParser : public QObject, public IDefinitionParser
{
    Q_OBJECT
public:
    explicit XmlDefinitionParser(QObject *parent = nullptr);
    ~XmlDefinitionParser();

    /*!
     * @details
     *   Gets the error occurred during reading (method read()).
     *   Returns empty string if error was not occurred.
     */
    const QString &error() const override;

    /*!
     * @details
     *   Gets the component Id.
     */
    const QString &componentShortName() const override;

    /*!
     * @details
     *   Gets the parsed component name.
     */
    const QString &componentName() const override;

    /*!
     * @details
     *   Gets the parsed component location (relative or absolyte) without library extension.
     */
    const QString &componentLocation() const override;

    /*!
     * @details
     *   Gets the parsed component description.
     *   @a Optional, can be empty string.
     */
    const QString &description() const override;

    /*!
     * @details
     *   Gets the parsed component parents names.
     *   @a Optional, can be empty list.
     */
    const ParentsList &parents() const override;

    /*!
     * @details
     *   Gets the parsed product name.
     *   @a Optional, can be empty string.
     */
    const QString &productName() const override;

    /*!
     * @details
     *   Gets the name of component's provider - the person or company,
     *   who created this component.
     */
    const QString &provider() const override;

    /*!
     * @details
     *   Gets the string representation of version of a component.
     */
    const QString &version() const override;

    /*!
     * @details
     *   This function parses the xml string @a text and sets component meta information.
     *
     *   If a parse error occurs (incorrect format, missing xml tags or attributes, etc),
     *   this function returns @a false. The error message could be got through error() method.
     */
    bool read(const QString &text) override;

    /*!
     * @details
     * @overload.
     */
    bool read(const QByteArray &data) override;

    /*!
     * @details
     * @overload
     */
    bool read(QIODevice* dev) override;

protected:
    /*!
     * @details
     *   Sets up component information using ready-to-use document.
     *
     *   If a parse error occurs (missing xml tags or attributes, etc),
     *   this function returns @a false.
     *
     * @sa read();
     */
    virtual bool parseXml(QDomDocument &document);

    void clear();

protected:
    QString m_componentName;
    QString m_shortName;
    QString m_componentLocation;
    QString m_description;
    QString m_productName;
    QString m_provider;
    QString m_error;
    QString m_version;
    ParentsList m_parents;
};

#endif // XMLDEFINITIONPARSER_H

