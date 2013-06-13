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

#include <carousel/componentsystem/componentsystem_global.h>

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
     * @constructor{ComponentDefinition}.
     */
    ComponentDefinition();

    /*!
     * @details
     * @constructor{ComponentDefinition} using specified component name and built-in flag
     *   which determines whether component registered statically in code (build-in) or
     *   dynamically (on start-time or run-time).
     */
    ComponentDefinition(const QString &componentName, bool isBuiltIn);

    /*!
     * @details
     * @constructor{ComponentDefinition} using copy-constructor.
     */
    ComponentDefinition(const ComponentDefinition &other);

    /*!
     * @details
     * @constructor{ComponentDefinition} using already existed instance.
     */
    ComponentDefinition &operator=(const ComponentDefinition &other);

    ~ComponentDefinition();

public:
    /*!
     * @details
     *   Returns default component provider, which is Unknown.
     */
    static QString defaultProvider();

    /*!
     * @details
     *   Adds a parent component name as a dependency for defined component.
     */
    void addParent(const QString &parent);

    /*!
     * @details
     *   Returns a defined component.
     */
    IComponent *component() const;

    /*!
     * @details
     *   Returns a component location (for loaded components). It might be absolute or
     *   relative path.
     *
     *   Returns empty string for explicitly loaded components (static components).
     */
    const QString &componentLocation() const;

    /*!
     * @details
     *   Returns a component short name.
     */
    const QString &shortComponentName() const;

    /*!
     * @details
     *   Returns a component name.
     */
    const QString &componentName() const;

    /*!
     * @details
     *   Returns a definition location (for loaded components). It might be absolute or
     *   relative path.
     *
     *   Returns empty string for explicitly loaded components (static components).
     */
    const QString &definitionLocation() const;

    /*!
     * @details
     *   Gets a detailed description text that is displayed for this component in the
     *   About this component box in the Components dialog.
     */
    const QString &description() const;

    /*!
     * @details
     *   Gets a flag which determines whether component registered statically in code
     *   (build-in) or dynamically (on start-time or run-time).
     */
    bool isBuiltIn() const;

    /*!
     * @details
     *   Gets a list of parent (dependent) components names.
     */
    const QStringList &parents() const;

    /*!
     * @details
     *   Gets a the name that is displayed for this component in the Components dialog.
     */
    const QString &productName() const;

    /*!
     * @details
     *   Gets a the name of component's provider, the person or company,
     *   who creates this component.
     *
     *   @a Unknown is by default.
     */
    const QString &provider() const;

    /*!
     * @details
     *   Sets a component.
     *
     * @note it does not have ownership for the component
     *   neither change description for the component.
     */
    void setComponent(IComponent *component);

    /*!
     * @details
     *   Sets the component name. The name should be unique in the application bounadaries,
     *   because components with the same name could not be added to the IComponentManager.
     */
    void setComponentName(const QString &name);

    /*!
     * @details
     *   Sets the component short name. This name will be shown to the user
     *   in the components dialog.
     */
    void setShortComponentName(const QString &name);

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
     *   Sets the provider name.
     */
    void setProvider(const QString &provider);

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
    QString m_componentShortName;
    QString m_description;
    QString m_productName;
    QString m_provider;
    QString m_componentLocation;
    QString m_definitionLocation;
    QStringList m_parents;
    bool m_isBuiltIn;
};

#endif // COMPONENTDEFINITION_H
