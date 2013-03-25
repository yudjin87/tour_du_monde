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

#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include "componentsystem/IComponent.h"
#include "componentsystem/ComponentDefinition.h"

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
 */
class COMP_API BaseComponent : public IComponent
{
    Q_OBJECT
public:
    ~BaseComponent();

    /*!
     * @details
     *   Gets the component definition that can specify component dependencies
     *   and also describes the component.
     *
     *   Note, that component takes ownership for its defition.
     */
    const ComponentDefinition *definition() const;

    /*!
     * @details
     *   Finds extension's pointer associated with it type id
     *   in inner objects dictionary.
     * @return The raw pointer corresponded with specified type id if such found. Null pointer otherwise.
     */
    void *getExtension(const QString &i_byTypeId) const;

    /*!
     * @details
     *   The name of the component. This name should be unique and used for the resolving component
     *   dependencies.
     *
     *   It is a shortcut for the definition()->name().
     */
    const QString &name() const;

    /*!
     * @details
     *   Shuts down the component. Use this method to perform some action when the component gets unloaded.
     */
    void shutdown();

    /*!
     * @details
     *   Gets the value determined whether component is already started or not.
     */
    bool started() const;

    /*!
     * @details
     *   When all components are registered, each component started up with given initialization
     *   data.
     * @param ip_initData is a reference to the object with which this component is started. Usually
     *   it will be reference to your own AbstractApplication root object, through you can obtain any data.
     * @return @a true, if component started up successful. Otherwise - return @a false. E.g. if component
     *   started twice - it is return @a false on the second time, because it is already started.
     */
    bool startup(QObject *ip_initData);

protected:
    /*!
     * @details
     *   Initializes a new instance of the BaseComponent class using specified component
     *   name. 
     * @param ip_name
     *   the name of your component class. In derived classes you should pass the unique 
     *   name for the your component (not per instance, but per class!).
     */
    explicit BaseComponent(const char *ip_name, QObject *parent = nullptr);

    /*!
     * @details
     *   Initializes a new instance of the BaseComponent class using specified component
     *   name. 
     * @param i_name
     *   the name of your component class. In derived classes you should pass the unique 
     *   name for the your component (not per instance, but per class!).
     */
    explicit BaseComponent(const QString &i_name, QObject *parent = nullptr);

    /*!
     * @details
     *   Initializes a new instance of the BaseComponent class using specified component
     *   definition.
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
     *   The type of extension, which @a ip_instance name should be associated while registered.
     *
     * @note it does not take ownership for registered extension.
     */
    template<typename TExtension>
    void registerExtension(TExtension *ip_instance);

    /*!
     * @details
     *   It is a defensive declaration of the public shutdown() method, that invokes only after startup().
     *   When override in derived classes shuts down the component. Nothing to do by default.
     */
    virtual void _onShutdown();

    /*!
     * @details
     *   It is a defensive declaration of the public startup() method, that invokes only if component is 
     *   not started.
     *   When override in derived classes starts up the component. Nothing to do by default.
     * @param ip_initData is a reference to the object with which this component is started. Usually
     *   it will be reference to your own AbstractApplication root object, through you can obtain any data.
     */
    virtual bool _onStartup(QObject *ip_initData);

    void addParent(const QString &parent);

    void loadAvailability();

    void setAvailability(ComponentDefinition::Availability newMode);

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

private:
    Q_DISABLE_COPY(BaseComponent)
    void registerExtensionInstance(void *ip_instance, const QString &i_forTypeId);

private:
    ComponentDefinition *mp_definition;
    bool m_isStarted;
    TypeObjectsMap<void *> *mp_typeObjectsMap;
};

//------------------------------------------------------------------------------
template<typename TExtension>
void BaseComponent::registerExtension(TExtension *ip_instance)
{
    const QString &extension_name = typeid(TExtension).name();
    registerExtensionInstance(reinterpret_cast<void *>(ip_instance), extension_name);
}

//------------------------------------------------------------------------------
#endif // BASECOMPONENT_H
