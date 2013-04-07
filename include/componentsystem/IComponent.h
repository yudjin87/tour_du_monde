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

#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "componentsystem/componentsystem_global.h"
#include "componentsystem/IComponentExtension.h"

#include <QtCore/QObject>
#include <QtCore/QString>

#include <typeinfo>

class ComponentDefinition;
/*!
 * @brief
 *   The abstract IComponent class defines contract for the components deployed in the application.
 * @details
 *   It is a base unit of the carousel, that can contain UI and/or logic features, provides or
 *   exposes some services for the other components. The instances of the IComponent class could
 *   be registered statically in code or discovered by other way - e.g., loaded from the specified
 *   pathes by DirectoryComponentProvider. Regardless of how you register new components, they will be passed
 *   to the IComponentManager after bootloading sequence and will be started.
 *
 *   The IComponent also stores its extensions, that could be handled by other components
 *   pr by carousel core (like IInteractiveExtension).
 *
 *   See ComponentDefinition interface, if your component will have a dependencies from the
 *   other application components.
 *
 *   Consider deriving from the BaseComponent class instead of implement this interface directly.
 */
class COMP_API IComponent : public QObject
{
    Q_OBJECT
    Q_ENUMS(Availability)

    /*!
     * @details
     *   Gets or sets the value specified whether this component is enabled, disabled, or unavailable.
     *   When the availability is enabled, the component is checked in the Components dialog.
     */
    Q_PROPERTY(Availability availability READ availability WRITE setAvailability NOTIFY availabilityChanged)

public:
    /*!
     * @details
     *   Component availability states.
     */
    enum Availability
    {
        /*!
         * @details
         *   Enabled for use.
         */
        Enabled,

        /*!
         * @details
         *   Disabled by the user. If component is disabled, child
         *   components that have dependency from this component,
         *   cannot be started.
         */
        Disabled,

        /*!
         * @details
         *   Unavailable - not licensed. If component is unavailable, child
         *   components that have dependency from this component,
         *   cannot be started.
         */
        Unavailable
    };

    virtual ~IComponent(){}

    /*!
     * @details
     *   Gets the value specified whether this component is enabled, disabled, or unavailable.
     *   When the availability is enabled, the component is checked in the Components dialog.
     * @sa setAvailability
     */
    virtual Availability availability() const = 0;

    /*!
     * @details
     *   Gets the component definition that can specify component dependencies
     *   and also describes the component.
     *
     *   Note, that component takes ownership for its defition.
     */
    virtual const ComponentDefinition *definition() const = 0;

    /*!
     * @details
     *   Finds a registered in derived class extension by its type, if any.
     *   If extension with such type was not registered, returns nullptr.
     */
    template<typename TExtension>
    TExtension *extension();

    /*!
     * @details
     *   Finds a registered in derived class extension by its type, if any.
     *   If extension with such type was not registered, returns nullptr.
     */
    template<typename TExtension>
    const TExtension *extension() const;


    /*!
     * @details
     *   When overridden in derived classes finds pointer associated with specified type id
     *   in inner objects dictionary.
     * @return The raw pointer corresponded with specified type id if such found. Null pointer otherwise.
     */
    virtual void *getExtension(const QString &i_byTypeId) const = 0;

    /*!
     * @details
     *   The name of the component. This name should be unique and used for the resolving component
     *   dependencies.
     *
     *   It is a shortcut for the definition()->name().
     */
    virtual const QString &name() const = 0;

    /*!
     * @details
     *   Sets the value specified whether this component is enabled or disabled.
     *   The checked state of the component is saved in the user settings.
     * @sa availability
     */
    virtual void setAvailability(Availability newMode) = 0;

    /*!
     * @details
     *   Shuts down the component. Use this method to perform some action when the component gets unloaded.
     */
    virtual void shutdown() = 0;

    /*!
     * @details
     *   Gets the value determined whether component is already started or not.
     */
    virtual bool started() const = 0;

    /*!
     * @details
     *   When all components are registered, each component started up with given initialization
     *   data.
     * @param ip_initData is a reference to the object with which this component is started. Usually
     *   it will be reference to your own AbstractApplication root object, through you can obtain any data.
     * @return @a true, if component started up successful. Otherwise - return @a false. E.g. if component
     *   started twice - it is return @a false on the second time, because it is already started.
     */
    virtual bool startup(QObject *ip_initData) = 0;

signals:
    /*!
     * @details
     *   This signal is emited when extension's availability changed.
     * @sa setAvailability
     */
    void availabilityChanged(IComponent::Availability);
};

//------------------------------------------------------------------------------
template<typename TExtension>
TExtension *IComponent::extension()
{
    // TODO: take IComponentExtension into account
    return const_cast<TExtension *>(
                static_cast<const IComponent *>(this)->extension<TExtension>());
}

//------------------------------------------------------------------------------
template<typename TExtension>
const TExtension *IComponent::extension() const
{
    const QString &extensionTypeName = typeid(TExtension).name();
    void *p_extension = getExtension(extensionTypeName);

    return reinterpret_cast<TExtension *>(p_extension);
}

//------------------------------------------------------------------------------
#endif // ICOMPONENT_H
