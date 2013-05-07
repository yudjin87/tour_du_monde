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

#ifndef COMPONENTDEFINITION_H
#define COMPONENTDEFINITION_H

#include "componentsystem/componentsystem_global.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>

class IComponent;

/*!
 * @brief
 *   This class describes the component meta information.
 * @details
 *   This class is used in the Components dialog to provide to user information about
 *   the component.
 *
 *   This class also specified that the current component has dependencies
 *   on another ones - on its 'parents'.
 *
 *   You should return names of the parent components in the parents() method
 *   if your component uses some services from another one - it is guaranteed
 *   that your component will be started up after all dependent components will.
 */
class COMP_API ComponentDefinition
{
public:
    /*!
     * @details
     *   Initialises a new empty instance of the ComponentDefinition class.
     */
    ComponentDefinition();

    /*!
     * @details
     *   Initialises a new instance of the ComponentDefinition class using
     *   specified component name and built-in flag which determines
     *   whether component registered statically in code (build-in) or
     *   dynamically (on start-time or run-time).
     */
    ComponentDefinition(const QString &componentName, bool isBuiltIn);

    ComponentDefinition(const ComponentDefinition &other);

    ~ComponentDefinition();

    /*!
     * @details
     *   Initializes an existing or creates and initializes a new instance of the
     *   DependenciesSolvingResult class using already existed instance.
     */
    ComponentDefinition &operator=(const ComponentDefinition &other);

public:
    void addParent(const QString &parent);

    /*!
     * @details
     *   Returns the defined component.
     */
    IComponent *component() const;

    /*!
     * @details
     *   Returns the component location (for loaded components). It might be absolute or
     *   relative path.
     *
     *   Returns empty string for explicitly loaded components (static components).
     */
    const QString &componentLocation() const;

    /*!
     * @details
     *   Returns the component name.
     */
    const QString &componentName() const;

    /*!
     * @details
     *   Returns the definition location (for loaded components). It might be absolute or
     *   relative path.
     *
     *   Returns empty string for explicitly loaded components (static components).
     */
    const QString &definitionLocation() const;

    /*!
     * @details
     *   Gets the detailed description text that is displayed for this component in the
     *   About this component box in the Components dialog.
     */
    const QString &description() const;

    /*!
     * @details
     *   Gets the flag which determines whether component registered statically in code
     *   (build-in) or dynamically (on start-time or run-time).
     */
    bool isBuiltIn() const;

    /*!
     * @details
     *   Gets the list of parent (dependent) components names.
     */
    const QStringList &parents() const;

    /*!
     * @details
     *   Gets the the name that is displayed for this component in the Components dialog.
     */
    const QString &productName() const;

    void setComponent(IComponent *component);

    /*!
     * @details
     *   Sets the component description.
     */
    void setComponentName(const QString &name);

    /*!
     * @details
     *   Sets the component description.
     */
    void setDescription(const QString &description);

    /*!
     * @details
     *   Sets the product name.
     */
    void setProductName(const QString &productName);

    /*!
     * @details
     *   Sets the component file location.
     */
    void setComponentLocation(const QString &componentLocation);

    /*!
     * @details
     *   Sets the definition file location.
     */
    void setDefinitionLocation(const QString &definitionLocation);

private:
    IComponent *m_component;
    QString m_componentName;
    QString m_description;
    QString m_productName;
    QString m_componentLocation;
    QString m_definitionLocation;
    QStringList m_parents;
    bool m_isBuiltIn;
};

#endif // COMPONENTDEFINITION_H
