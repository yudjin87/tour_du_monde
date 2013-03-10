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

#ifndef BASESERVICELOCATOR_H
#define BASESERVICELOCATOR_H

#include "utils/utils_global.h"

#include <QtCore/QObject>
#include <QtCore/QString>

#include <functional>
#include <typeinfo>

typedef std::function<void*(void)> factoryMethod;

/*!
 * @brief
 *   The abstract IServiceLocator class provides central registry of the types and instances.
 * @details
 *   The main IServiceLocator purpose is application/library sections separating, so the only link
 *   between them becomes the service registry.
 *   User types and instances (services) may be added during loading sequence, or by components and
 *   can be accessed from application.
 *
 *   To register your own global services or type factories, you should to
 *   override BootloaderBase::_configureServiceLocator() function and register your own services (if you
 *   develop own application), or you can extend registry registering the component services
 *   and type factories at the IComponent::startup() member (if you develop extensions for the
 *   application). Further you can obtain current service through the template IServiceLocator::locate()
 *   member, where template parameter is the expected service typemor IServiceLocator::buildInstance()
 *   to create pure abstract class (interface) without knowledge of concrete class.
 *
 *   The services and type factories are unique in the registry, and this uniqueness is defined by
 *   the two parameters: registered type name (obtained through @a typeid() operator) and the tag.
 *   So, if you want to register existing service type or existing type factory you have to adding
 *   the unique tag for it.
 *   The service or type factory registered without special tag would be tagged with "" (empty
 *   string) in service locator implementation.
 *
 *   If you call CarouselBootloader::_configureServiceLocator() from your derived loader class, the IComponentProvider,
 *   ILogger and IComponentManager would be registered.
 *
 *   Here is simple example of service locator usage:
 * @code
 *   class IA {
 *     public: virtual ~IA(){}
 *     };
 *
 *   class A : public IA {
 *     public: A(){}
 *     };
 *
 *   class IB {
 *     public: virtual ~IB(){}
 *     };
 *
 *   class B : public IB {
 *     public:
 *       B(IA* a) : m_a(a) {}
 *
 *       IA* m_a;
 *     };
 *
 *   class IC {
 *     public: virtual ~IC(){}
 *     };
 *
 *   class C : public IC {
 *     public:
 *       C(IB* b, IA* a) : m_b(b) , m_a(a) {}
 *
 *       IB* m_b;
 *       IA* m_a;
 *     };
 * @endcode
 *
 *   Register type dependencies:
 * @code
 *   IServiceLocator *locator = new ServiceLocator();
 *   locator->bindType<IA, A>();
 *
 *   locator->registerType<IB>([locator]() -> IB*
 *     {
 *     IA* a = locator->buildInstance<IA>();
 *     IB* b = new B(a);
 *     return b;
 *     });
 *
 *   locator->registerType<IC>([locator]()-> IC*
 *     {
 *     IA* a = locator->buildInstance<IA>();
 *     IB* b = new B(a);
 *     IC* c = new C(b, a);
 *     return c;
 *     });
 * @endcode
 *
 *   Usage:
 * @code
 *   IC *c1 = locator->buildInstance<IC>();
 * @endcode
 *   Here the cliens does not know what exactly instance is instantiated, and also
 *   they avoid all complex constructor injections.
 *
 * @todo tell about achieving the IServiceLocator instance => from the AbstractApplication
 * @note Does not take ownership of the services or of the created by factories types.
 */
class UTILS_API IServiceLocator
{
public:
    IServiceLocator(){}
    virtual ~IServiceLocator(){}

public:
    /*!
     * @details
     *   Binds an interface type with concrete class and specified tag with the locator.
     *   An instance of the concrete class will be returned on each buildInstance()
     *   method call.
     *
     *   It is a convinient method for the classes with parameterless constructors
     *   This method calls registerType() with specified @a TInterface and functor
     *   that just returns a new @a TConcreteClass.
     */
    template<typename TInterface, typename TConcreteClass>
    void bindType(const QString &tag);

    /*!
     * @details
     *   This is overload method.
     *   Binds an interface type with concrete class and empty tag with the locator.
     */
    template<typename TInterface, typename TConcreteClass>
    void bindType();

    /*!
     * @details
     *   This is overload method.
     *   Creates and returns a @a TInterface pointer using empty tag and registered
     *   factory method, if any. Returns nullptr otherwise.
     * @note Does not take ownership of the created pointer.
     */
    template<typename TInterface>
    TInterface *buildInstance() const;

    /*!
     * @details
     *   Creates and returns a @a TInterface pointer using specified tag and registered
     *   factory method, if any. Returns nullptr otherwise.
     * @note Does not take ownership of the created pointer.
     */
    template<typename TInterface>
    TInterface *buildInstance(const QString &tag) const;

    /*!
     * @details
     *   Finds the service registered with @a TService type name and empty tag.
     * @return the corresponding service if such found. Null pointer otherwise.
     */
    template<typename TService>
    TService *locate();

    /*!
     * @details
     *   Finds the service registered with @a TService type name and specified @a i_tag.
     * @return the corresponding service if such found. Null pointer otherwise.
     */
    template<typename TService>
    TService *locate(const QString &i_tag);

    /*!
     * @details
     *   This is overload method.
     *   Registers a service instance with empty tag with the locator.
     */
    template<typename TService>
    void registerInstance(TService *ip_instance);

    /*!
     * @details
     *   Registers a service instance with specified tag with the locator.
     *   It might be necessary to specify typename @a TService explicitly due to the static binding:
     * @code
     *   MyService service;
     *   serviceLocator->registerInstance(&service);                        // will be registered "class MyService" - seems not what you expected
     *   IMyService *locatedService = serviceLocator->locate<IMyService>()  // returns null, because asked "class IMyService" does not found
     * @endcode
     *   To avoid this you should explicitly specify registered typename:
     * @code
     *   MyService service;
     *   serviceLocator->registerInstance<IMyService>(&service);            // will be registered "class IMyService" - good
     *   IMyService *locatedService = serviceLocator->locate<IMyService>()  // returns service pointer
     * @endcode
     *   or register pointer to the service interface:
     * @code
     *   IMyService *serviceInterface = new MyService();
     *   serviceLocator->registerInstance(serviceInterface);                // will be registered "class IMyService" - good
     *   IMyService *locatedService = serviceLocator->locate<IMyService>()  // returns service pointer
     * @endcode
     * @tparam TService
     *   The type which type name @a ip_instance should be associated while registered in locator with.
     */
    template<typename TService>
    void registerInstance(TService *ip_instance, const QString &i_tag);

    /*!
     * @details
     *   This is overload method.
     *   Registers a type with factory method and empty tag with the locator.
     */
    template<typename TInterface>
    void registerType(factoryMethod method);

    /*!
     * @details
     *   Registers a type with factory method and specified tag with the locator.
     *   The @a method should return new instance of the @a TInterface type.
     */
    template<typename TInterface>
    void registerType(factoryMethod method, const QString &tag);

protected:
    /*!
     * @details
     *   When overridden in derived classes finds the factory method associated with
     *   specified type id and specified @a i_tag in inner objects dictionary and
     *   creates instance of the interface using factory method
     * @return The raw pointer corresponded with specified interface id and tag if such found.
     *   Null pointer otherwise.
     */
    virtual void *_buildInstance(const QString &i_byTypeId, const QString &tag) const = 0;

    /*!
     * @details
     *   When overridden in derived classes finds the pointer associated with specified
     *   type id and specified @a i_tag in inner objects dictionary.
     * @return The raw pointer corresponded with specified type id and tag if such found.
     *   Null pointer otherwise.
     */
    virtual void *_getService(const QString &i_byTypeId, const QString &i_tag) const = 0;

    /*!
     * @details
     *   When overridden in derived classes registers a raw pointer with specified
     *   tag in inner objects dictionary.
     * @param i_forTypeId
     *   The name of type which @a ip_instance should be associated with.
     */
    virtual void _register(void *ip_instance, const QString &i_forTypeId, const QString &i_tag) = 0;

    /*!
     * @details
     *   When overridden in derived classes binds an interface type id with
     *   specified factory method (that should create instance of interface) and
     *   with specified tag in inner objects dictionary.
     * @param i_forTypeId
     *   The name of type which @a factory method should be associated with.
     */
    virtual void _registerType(const QString &typeIdName, factoryMethod method, const QString &tag) = 0;

private:
    Q_DISABLE_COPY(IServiceLocator)
};

//------------------------------------------------------------------------------
template<typename TInterface, typename TConcreteClass>
void IServiceLocator::bindType()
{
    this->bindType<TInterface, TConcreteClass>("");
}

//------------------------------------------------------------------------------
//TODO: replace to lambda
template<typename TConcreteClass>
void *removeWhenLambdaSupportWillBeAdded()
{
    return new TConcreteClass();
}

//------------------------------------------------------------------------------
template<typename TInterface, typename TConcreteClass>
void IServiceLocator::bindType(const QString &tag)
{
    factoryMethod creator = &removeWhenLambdaSupportWillBeAdded<TConcreteClass>;
    this->registerType<TInterface>(creator, tag);
}

//------------------------------------------------------------------------------
template<typename TInterface>
TInterface *IServiceLocator::buildInstance() const
{
    return buildInstance<TInterface>("");
}

//------------------------------------------------------------------------------
template<typename TInterface>
TInterface *IServiceLocator::buildInstance(const QString &tag) const
{
    const char *typeIdName = typeid(TInterface).name();
    void *data = this->_buildInstance(typeIdName, tag);

    // TODO: use static checks (c++11) during type registering and building.
    QObject *obj = reinterpret_cast<QObject *>(data);
    TInterface *instance = dynamic_cast<TInterface *>(obj);

    return instance;
}

//------------------------------------------------------------------------------
template<typename TService>
TService *IServiceLocator::locate()
{
    return this->locate<TService>("");
}

//------------------------------------------------------------------------------
template<typename TService>
TService *IServiceLocator::locate(const QString &i_tag)
{
    const QString &service_name = typeid(TService).name();
    void *p_service = this->_getService(service_name, i_tag);

    return reinterpret_cast<TService *>(p_service);
}

//------------------------------------------------------------------------------
template<typename TService>
void IServiceLocator::registerInstance(TService *ip_instance)
{
    this->registerInstance<TService>(ip_instance, "");
}

//------------------------------------------------------------------------------
template<typename TService>
void IServiceLocator::registerInstance(TService *ip_instance, const QString &i_tag)
{
    const QString &service_name = typeid(TService).name();
    this->_register(reinterpret_cast<void *>(ip_instance), service_name, i_tag);
}

//------------------------------------------------------------------------------
template<typename TInterface>
void IServiceLocator::registerType(factoryMethod method)
{
    this->registerType<TInterface>(method, "");
}

//------------------------------------------------------------------------------
template<typename TInterface>
void IServiceLocator::registerType(factoryMethod method, const QString &tag)
{
    const char *typeIdName = typeid(TInterface).name();
    this->_registerType(typeIdName, method, tag);
}

//------------------------------------------------------------------------------
#endif // BASESERVICELOCATOR_H
