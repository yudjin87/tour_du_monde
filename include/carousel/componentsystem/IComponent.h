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

#include <carousel/carousel_global.h>
#include <carousel/componentsystem/IComponentExtension.h>

#include <QtCore/QMetaType>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include <typeinfo>

class ComponentDefinition;
class IServiceLocator;

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
class CAROUSEL_API IComponent : public QObject
{
    Q_OBJECT
    Q_ENUMS(Availability)
    Q_ENUMS(State)

    /*!
     * @details
     *   Gets or sets the value specified whether this component is enabled, disabled, or unavailable.
     *   When the availability is enabled, the component is checked in the Components dialog.
     */
    Q_PROPERTY(Availability availability READ availability NOTIFY availabilityChanged)
    Q_PROPERTY(State state READ state)
    Q_PROPERTY(bool started READ started)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(const ComponentDefinition *definition READ definition)
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

    /*!
     * @details
     *   The component goes through several steps while being loaded. The state gives a
     *   hint on what went wrong in case of an error.
     * @code
     *                                                 ┌────────┐
     *                                              ┌─>│ Orphan ├───────┐
     *                                              │  └────────┘       v
     *   ┌─────────┐  ┌────────────┐  ┌────────┐  ┌─┴───────────┐  ┌─────────┐
     *   │ Invalid ├─>│ Discovered ├─>│ Parsed ├─>│ Initialized ├─>│ Running │
     *   └─────────┘  └────────────┘  └────────┘  └─────────────┘  └─┬───────┘
     *                                                               v    ^
     *                                                             ┌──────┴──┐
     *                                                             │ Stopped │
     *                                                             └─────────┘
     * @endcode
     */
    enum State
    {
        Invalid = 0,  // definition path is invalid or don't have an read access
        Discovered, // definition is found and read
        Parsed,     // definition is parsed
        Initialized, // properties are set from the parsing definition, library file is found. Default value for statically registered components
        Running,
        Stopped,      // shutdown was called
        Orphan        // parents were not found or could not started
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
     *   Gets the state in which the component currently is. See the description of the
     *   IComponent::State enum for details.
     * @sa setState
     */
    virtual State state() const = 0;

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
    virtual void *getExtension(const QString &byTypeId) const = 0;

    /*!
     * @details
     *   The name of the component. This name should be unique and used for the resolving component
     *   dependencies.
     *
     *   It is a shortcut for the definition()->name().
     *
     * @sa toStringList
     */
    virtual const QString &name() const = 0;

    /*!
     * @details
     *   Returns @a true if component version is compatible with @a all @a parent component
     *   versions, e.g. if they are equal. Otherwise, returns @a false.
     *
     * @sa ComponentDefinition::isCompatible()
     */
    virtual bool isCompatible(const IComponent *withOther) const = 0;

    /*!
     * @details
     *   Sets the value specified whether this component is enabled or disabled.
     *   The checked state of the component is saved in the user settings.
     * @sa availability
     */
    virtual void setAvailability(Availability newMode) = 0;

    /*!
     * @details
     *   Sets the value specified the component current state.
     *
     * @note You should not use this method directly, it is for internal goals only.
     *
     * @sa state
     */
    virtual void setState(State newState) = 0;

    /*!
     * @details
     *   Shuts down the component.
     *   Implement this method to perform some action when the component gets unloaded.
     *
     * @note You should not use this method directly, use IComponentManager::shutdownComponent()
     *   instead.
     */
    virtual void shutdown(IServiceLocator *serviceLocator) = 0;

    /*!
     * @details
     *   Gets the value determined whether component is already started or not.
     */
    virtual bool started() const = 0;

    /*!
     * @details
     *   When all components are registered, each component started up with given initialization
     *   data.
     * @param serviceLocator is a reference to the services pool. It is needed to register/locate to
     *   common services and other components' services.
     * @return @a true, if component started up successful. Otherwise - return @a false. E.g. if component
     *   started twice - it is return @a false on the second time, because it is already started.
     *
     * @note You should not use this method directly, use IComponentManager::startupComponent()
     *   instead.
     */
    virtual bool startup(IServiceLocator *serviceLocator) = 0;

signals:
    /*!
     * @details
     *   This signal is emited when extension's availability changed.
     * @sa setAvailability
     */
    void availabilityChanged(IComponent::Availability);
};

/*!
 * @details
 *   Returns list of component names.
 */
QStringList toStringList(const QList<IComponent *> &components);

template<typename TExtension>
TExtension *IComponent::extension()
{
    // TODO: take IComponentExtension into account
    return const_cast<TExtension *>(
                static_cast<const IComponent *>(this)->extension<TExtension>());
}

template<typename TExtension>
const TExtension *IComponent::extension() const
{
    const QString &extensionTypeName = typeid(TExtension).name();
    void *extension = getExtension(extensionTypeName);

    return reinterpret_cast<TExtension *>(extension);
}

Q_DECLARE_METATYPE(IComponent*)
Q_DECLARE_METATYPE(IComponent::Availability)

#endif // ICOMPONENT_H
