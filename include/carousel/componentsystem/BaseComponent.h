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

#pragma once
#include <carousel/componentsystem/IComponent.h>
#include <carousel/componentsystem/ComponentDefinition.h>

template<typename TValue>
class TypeObjectsMap;

/*!
 * @brief
 *   It is a base unit of the carousel, that can contain UI and/or logic features, provides or
 *   exposes some services for the other components.
 * @details
 *   See ComponentDefinition interface, if your component will be have a dependencies from the
 *   other application components.
 *
 *   The BaseComponent also serves as a base class for the custom Components. It sets objectName
 *   to the QObject, provides defensive invokes of startup() and shutdown(), and exposes the
 *   registerExtension() template method to register component extensions while deriving.
 *
 *   If availability was changed during last application's start, it will be
 *   loaded and ovewrite default value.
 */
class CAROUSEL_API BaseComponent : public IComponent
{
    Q_OBJECT
public:
    ~BaseComponent();

    /*!
     * @details
     *   Gets the value specified whether this component is enabled, disabled, or unavailable.
     *   When the availability is enabled, the component is checked in the Components dialog.
     * @sa setAvailability
     */
    Availability availability() const override;

    /*!
     * @details
     *   Gets the state in which the component currently is. See the description of the
     *   IComponent::State enum for details.
     * @sa setState
     */
    State state() const override;

    /*!
     * @details
     *   Gets the component definition that can specify component dependencies
     *   and also describes the component.
     *
     *   Note, that component takes ownership for its defition.
     */
    const ComponentDefinition *definition() const override;

    /*!
     * @details
     *   Finds extension's pointer associated with it type id
     *   in inner objects dictionary.
     * @return The raw pointer corresponded with specified type id if such found. Null pointer otherwise.
     */
    void *getExtension(const QString &byTypeId) const override;

    /*!
     * @details
     *   Returns @a true if component version is compatible with @a all @a parent component
     *   versions, e.g. if they are equal. Otherwise, returns @a false.
     *
     * @sa ComponentDefinition::isCompatible()
     */
    bool isCompatible(const IComponent *withOther) const override;

    /*!
     * @details
     *   The name of the component. This name should be unique and used for the resolving component
     *   dependencies.
     *
     *   It is a shortcut for the definition()->name().
     */
    const QString &name() const override;

    /*!
     * @details
     *   Sets the value specified whether this component is enabled or disabled.
     *   The checked state of the component is saved in the user settings.
     * @sa availability
     */
    void setAvailability(Availability newMode) override;

    /*!
     * @details
     *   Sets the value specified the component current state.
     *
     * @note You should not use this method directly, it is for internal goals only.
     *
     * @sa state
     */
    void setState(State newState) override;

    /*!
     * @details
     *   Shuts down the component.
     *   Implement this method to perform some action when the component gets unloaded.
     *
     * @note You should not use this method directly, use IComponentManager::shutdownComponent()
     *   instead.
     */
    void shutdown(IServiceLocator *serviceLocator) override;

    /*!
     * @details
     *   Gets the value determined whether component is already started or not.
     */
    bool started() const override;

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
    bool startup(IServiceLocator *serviceLocator) override;

protected:
    /*!
     * @details
     *   Initializes a new instance of the BaseComponent class using specified component
     *   name and IComponent::Enabled availability.
     * @param name
     *   the name of your component class. In derived classes you should pass the unique 
     *   name for the your component (not per instance, but per class!).
     */
    explicit BaseComponent(const QString &name, QObject *parent = nullptr);

    /*!
     * @details
     *   Initializes a new instance of the BaseComponent class using specified component
     *   definition  and IComponent::Enabled availability..
     * @param definition
     *   This paramter cannot be null.
     */
    explicit BaseComponent(ComponentDefinition *definition, QObject *parent = nullptr);

    /*!
     * @details
     *   Registers an extension instance.
     *   It might be necessary to specify typename @a TExtension explicitly due to the static binding:
     * @code
     *   MyExtension extension;
     *   this->registerExtension(&extension);                              // will be registered "class MyExtension" - seems not what you expected
     *   IMyExtension *locatedExtension = this->extension<IMyExtension>()  // returns null, because asked "class IMyExtension" does not found
     * @endcode
     *   To avoid this you should explicitly specify registered typename:
     * @code
     *   MyExtension extension;
     *   this->registerInstance<IMyExtension>(&extension);                 // will be registered "class IMyExtension" - good
     *   IMyExtension *locatedExtension = this->extension<IMyExtension>()  // returns extension pointer
     * @endcode
     *   or register pointer to the extension interface:
     * @code
     *   IMyExtension *extensionInterface = new MyExtension();
     *   this->registerInstance(extensionInterface);                       // will be registered "class IMyExtension" - good
     *   IMyExtension *locatedExtension = this->extension<IMyExtension>()  // returns extension pointer
     * @endcode
     * @tparam TExtension
     *   The type of extension, which @a instance name should be associated while registered.
     *
     * @note it does not take ownership for registered extension.
     */
    template<typename TExtension>
    void registerExtension(TExtension *instance);

    /*!
     * @details
     *   It is a defensive declaration of the public shutdown() method, that invokes only after startup().
     *   When override in derived classes shuts down the component. Nothing to do by default.
     */
    virtual void onShutdown(IServiceLocator *serviceLocator);

    /*!
     * @details
     *   It is a defensive declaration of the public startup() method, that invokes only if component is 
     *   not started.
     *   When override in derived classes starts up the component. Nothing to do by default.
     * @param serviceLocator is a reference to the services pool. It is needed to register/locate to
     *   common services and other components' services.
     */
    virtual bool onStartup(IServiceLocator *serviceLocator);

    /*!
     * @details
     *   Adds a parent component name and version as a dependency for defined component.
     */
    void addParent(const QString &parentName, int major_version, int minor_version, int build_version = 0, int revision_version = 0);

    /*!
     * @details
     *   Loads component availability using QSettings and component name.
     */
    void loadAvailability();

    /*!
     * @details
     *   Saves component availability using QSettings and component name.
     */
    void saveAvailability();

    /*!
     * @details
     *   Sets the component description.
     */
    void setDescription(const QString &description);

    void setError(const QString &error);

    /*!
     * @details
     *   Sets the short component name.
     */
    void setShortName(const QString &name);

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
     *   Sets the version of a component.
     */
    void setVersion(int major_version, int minor_version, int build_version = 0, int revision_version = 0);

    /*!
     * @details
     *   This method emits availabilityChanged() signal when extension's
     *   availability changed.
     * @sa setAvailability, availabilityChanged
     */
    virtual void onAvailabilityChanged(Availability newMode);

private:
    Q_DISABLE_COPY(BaseComponent)
    void registerExtensionInstance(void *instance, const QString &forTypeId);

private:
    ComponentDefinition *m_definition;
    Availability m_availability;
    State m_state;
    TypeObjectsMap<void *> *m_typeObjectsMap;
};

template<typename TExtension>
void BaseComponent::registerExtension(TExtension *instance)
{
    const QString &extension_name = typeid(TExtension).name();
    registerExtensionInstance(reinterpret_cast<void *>(instance), extension_name);
}

