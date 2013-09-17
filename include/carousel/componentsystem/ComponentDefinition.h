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
#include <carousel/componentsystem/ParentDefinitions.h>

#include <QtCore/QObject>
#include <QtCore/QStringList>

class IComponent;
class Version;

/*!
 * @brief
 *   This class describes the component meta information.
 * @details
 *   This class is used in the Components dialog to provide to user information about
 *   the component.
 *
 *   This class also specified that the current component has dependencies
 *   on another ones - on its 'parents'.
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

    ~ComponentDefinition();

public:
    /*!
     * @details
     *   Returns default component provider, which is Unknown.
     */
    static QString defaultProvider();

    /*!
     * @details
     *   Adds a parent component definition as a dependency for defined component.
     */
    void addParent(ParentDefinition *parent);

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
     *   Returns @a true if component version is compatible with @a all @a parent component
     *   versions, e.g. if they are equal. Otherwise, returns @a false.
     */
    bool isCompatible(const IComponent *parent) const;

    /*!
     * @details
     * @overload
     */
    bool isCompatible(const QString &name, const Version *version) const;

    /*!
     * @details
     * @overload
     */
    bool isCompatible(const ParentDefinitions &parents) const;

    /*!
     * @details
     *   Gets a list of parent (dependent) components names.
     */
    const ParentDefinitions &parents() const;

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
     *   Gets the arguments, passed to the application on start.
     */
    const QStringList &arguments() const;

    /*!
     * @details
     *   Gets the version of a component.
     */
    const Version *version() const;

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

    /*!
     * @details
     *   Sets the arguments, passed to the application on start. The BaseComponent
     *   sets all arguments right in startup.
     *
     * @todo: filter argumets for each component
     */
    void setArguments(const QStringList &arguments);

    /*!
     * @details
     *   Sets the version of a component.
     */
    void setVersion(int major_version, int minor_version, int build_version = 0, int revision_version = 0);

    /*!
     * @details
     *   Sets the version of a component. It takes ownership for the @a version pointer.
     */
    void setVersion(Version *version);

private:
    Q_DISABLE_COPY(ComponentDefinition)

private:
    IComponent *m_component;
    QString m_componentName;
    QString m_componentShortName;
    QString m_description;
    QString m_productName;
    QString m_provider;
    QString m_componentLocation;
    QString m_definitionLocation;
    QStringList m_arguments;
    Version *m_version;
    ParentDefinitions m_parents;
    bool m_isBuiltIn;
};

#endif // COMPONENTDEFINITION_H
