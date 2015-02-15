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

#ifndef ISERVICELOCATOR_H
#define ISERVICELOCATOR_H

#include <carousel/carousel_global.h>

#include <QtCore/QObject>
#include <QtCore/QString>

#include <functional>

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
 *   override BootloaderBase::configureServiceLocator() function and register your own services (if you
 *   develop own application), or you can extend registry registering the component services
 *   and type factories at the IComponent::startup() member (if you develop extensions for the
 *   application). Further you can obtain current service through the template IServiceLocator::locate()
 *   member, where template parameter is the expected service typemor IServiceLocator::buildInstance()
 *   to create pure abstract class (interface) without knowledge of concrete class.
 *
 *   The services and type factories are unique in the registry, and this uniqueness is defined by
 *   the two parameters: registered class name (obtained through @a meta-object) and the tag.
 *   So, if you want to register existing service type or existing type factory you have to adding
 *   the unique tag for it.
 *   The service or type factory registered without special tag will be tagged with "" (empty
 *   string) in service locator implementation.
 *
 *   If you call CarouselBootloader::configureServiceLocator() from your derived loader class,
 *   the IComponentProvider, QMainWindow and IComponentManager will be registered.
 *
 *   Here is simple example of service locator usage:
 * @code
 *   class IA : public QObject {
 *     Q_OBJECT
 *     public: virtual ~IA(){}
 *     };
 *
 *   class A : public IA {
 *     Q_OBJECT
 *     public: A(){}
 *     };
 *
 *   class IB {
 *     Q_OBJECT
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
 *   class IC : public QObject{
 *     Q_OBJECT
 *     public: virtual ~IC(){}
 *     };
 *
 *   class C : public IC {
 *     Q_OBJECT
 *     public:
 *       C(IB* b, IA* a) : m_b(b) , m_a(a) {}
 *
 *       IB* m_b;
 *       IA* m_a;
 *     };
 * @endcode
 *
 *   Register type dependencies with lambdas:
 * @code
 *   IServiceLocator *locator = new ServiceLocator();
 *   locator->bindType<IA, A>();
 *
 *   locator->registerType<IB>([locator]()
 *     {
 *     IA* a = locator->buildInstance<IA>();
 *     IB* b = new B(a);
 *     return b;
 *     });
 *
 *   locator->registerType<IC>([locator]()
 *     {
 *     IA* a = locator->buildInstance<IA>();
 *     IB* b = new B(a);
 *     IC* c = new C(b, a);
 *     return c;
 *     });
 * @endcode
 *
 * or with templated TypeCreator:
 *
 * @code
 *   IServiceLocator *locator = new ServiceLocator();
 *   locator->registerInstance<IA, a>();
 *   locator->registerInstance<IB, b>();
 *
 *   TypeCreator<IC, IA, IB> icCreator{locator};
 *
 *   locator->registerType<IC>(icCreator);
 * @endcode
 *
 *   Usage:
 * @code
 *   IC *c1 = locator->buildInstance<IC>();
 * @endcode
 *   Here the cliens does not know what exactly instance is instantiated, and also
 *   they avoid all complex constructor injections.
 *
 *   Since @a qobject_cast() is used all services should be derived from the QObject
 *   and have Q_OBJECT macro.
 *
 * @note Does not take ownership of the services or of the created by factories types.
 */
class CAROUSEL_API IServiceLocator
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
    TInterface *buildInstance();

    /*!
     * @details
     *   Creates and returns a @a TInterface pointer using specified tag and registered
     *   factory method (based on type), if any. First, type must be registered, using registerType().
     *   Returns nullptr otherwise.
     * @sa registerType()
     * @note Does not take ownership of the created pointer.
     */
    template<typename TInterface>
    TInterface *buildInstance(const QString &tag);

    /*!
     * @details
     *   This is overload method.
     *   Creates and returns a @a className pointer using empty tag.
     * @sa registerType(), buildInstance()
     * @note Does not take ownership of the created pointer.
     */
    virtual QObject *buildObject(const QString &className) = 0;

    /*!
     * @details
     *   Creates and returns a @a className pointer using specified tag and registered
     *   factory method, if any. First, type must be registered, using registerType().
     *   Returns nullptr otherwise. This may be usefull for scpipting, where no templates are supported.
     * @return the corresponding service if such found. Null pointer otherwise.
     * @sa registerType(), buildInstance()
     * @note Does not take ownership of the created pointer.
     */
    virtual QObject *buildObject(const QString &className, const QString &tag) = 0;

    /*!
     * @details
     *   Finds the service registered with @a className and empty tag and returns
     *   a QObject pointer to it.
     *   This may be usefull for scpipting, where no templates.
     * @return the corresponding service if such found. Null pointer otherwise.
     */
    virtual QObject *locateToObject(const QString &className) = 0;

    /*!
     * @details
     *   Finds the service registered with @a className and empty tag and returns
     *   a QObject pointer to it.
     *   This may be usefull for scpipting, where no templates.
     * @return the corresponding service if such found. Null pointer otherwis
     */
    virtual QObject *locateToObject(const QString &className, const QString &tag) = 0;

    /*!
     * @details
     *   Finds the service registered with @a TService type name and empty tag.
     * @return the corresponding service if such found. Null pointer otherwise.
     */
    template<typename TService>
    TService *locate();

    /*!
     * @details
     *   Finds the service registered with @a TService type name and specified @a tag.
     * @return the corresponding service if such found. Null pointer otherwise.
     */
    template<typename TService>
    TService *locate(const QString &tag);

    /*!
     *   Gets the services, registered with an empty tag
     */
    virtual QStringList services() const = 0;

    /*!
     *   Gets the registered with @a tag services;
     */
    virtual QStringList services(const QString &tag) const = 0;

    /*!
     * @details
     *   This is overload method.
     *   Registers a service instance with empty tag with the locator.
     *
     * @sa unregisterInstance(), locate()
     */
    template<typename TService>
    void registerInstance(TService *instance);

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
     *   The type which type name @a instance should be associated while registered in locator with.
     *
     * @sa unregisterInstance(), locate()
     */
    template<typename TService>
    void registerInstance(TService *instance, const QString &tag);

    /*!
     * @details
     *   This is overload method.
     *   Registers a type with factory method and empty tag with the locator.
     *
     * @sa buildInstance(), buildObject()
     */
    template<typename TInterface>
    void registerType(factoryMethod method);

    /*!
     * @details
     *   Registers a type with factory method and specified tag with the locator.
     *   The @a method should return new instance of the @a TInterface type. Further, this type can be created by using
     *   buildInstance() or buildObject() method.
     *
     * @sa buildInstance(), buildObject()
     */
    template<typename TInterface>
    void registerType(factoryMethod method, const QString &tag);

    /*!
     * @details
     *   Unregisters a service instance with specified type and tag from the locator (if any) and
     *   removes it from the locator map.
     *
     * @tparam TService
     *   The type which type name will be found while.
     *
     *   Returns found instance or nullptr, if instance with specified
     *   type and tag was not found.
     *
     * @sa registerInstance()
     */
    template<typename TService>
    TService *unregisterInstance(const QString &tag);

    /*!
     * @details
     *   This is overload method.
     *   Unregisters a service instance with specified type from the locator (if any) and
     *   removes it from the locator map.
     *
     * @sa registerInstance()
     */
    template<typename TService>
    TService *unregisterInstance();

protected:
    /*!
     * @details
     *   When overridden in derived classes finds the factory method associated with
     *   specified type id and specified @a tag in inner objects dictionary and
     *   creates instance of the interface using factory method
     * @return The raw pointer corresponded with specified interface id and tag if such found.
     *   Null pointer otherwise.
     */
    virtual void *buildInstanceImpl(const QString &className, const QString &tag) = 0;

    /*!
     * @details
     *   When overridden in derived classes finds the pointer associated with specified
     *   type id and specified @a tag in inner objects dictionary.
     * @return The raw pointer corresponded with specified type id and tag if such found.
     *   Null pointer otherwise.
     */
    virtual void *getService(const QString &className, const QString &tag) = 0;

    /*!
     * @details
     *   When overridden in derived classes registers a raw pointer with specified
     *   tag in inner objects dictionary.
     * @param className
     *   The name of type which @a instance should be associated with.
     */
    virtual void registerInstanceImpl(void *instance, const QString &className, const QString &tag) = 0;

    /*!
     * @details
     *   When overridden in derived classes unregisters (removes) a service instance with specified
     *   type id and tag from the inner objects dictionary (if any).
     * @param className
     *   The name of type which removed instance should be associated with.
     * @return The raw pointer corresponded with specified type id and tag if such found.
     *   Null pointer otherwise.
     */
    virtual void *unregisterInstanceImpl(const QString &className, const QString &tag) = 0;

    /*!
     * @details
     *   When overridden in derived classes binds an interface type id with
     *   specified factory method (that should create instance of interface) and
     *   with specified tag in inner objects dictionary.
     * @param className
     *   The name of type which @a factory method should be associated with.
     */
    virtual void registerTypeImpl(const QString &className, factoryMethod method, const QString &tag) = 0;

private:
    Q_DISABLE_COPY(IServiceLocator)
};

//------------------------------------------------------------------------------
template<typename TInterface, typename TConcreteClass>
void IServiceLocator::bindType()
{
    static_assert(std::is_base_of<QObject, TInterface>::value, "TInterface should derive from the QObject!");
    static_assert(std::is_base_of<TInterface, TConcreteClass>::value, "TConcreteClass should derive from the TInterface!");

    this->bindType<TInterface, TConcreteClass>("");
}

//------------------------------------------------------------------------------
template<typename TInterface, typename TConcreteClass>
void IServiceLocator::bindType(const QString &tag)
{
    static_assert(std::is_base_of<QObject, TInterface>::value, "TInterface should derive from the QObject!");
    static_assert(std::is_base_of<TInterface, TConcreteClass>::value, "TConcreteClass should derive from the TInterface!");

    auto creator = [](){return new TConcreteClass();};
    this->registerType<TInterface>(creator, tag);
}

//------------------------------------------------------------------------------
template<typename TInterface>
TInterface *IServiceLocator::buildInstance()
{
    static_assert(std::is_base_of<QObject, TInterface>::value, "TInterface should derive from the QObject!");

    return buildInstance<TInterface>("");
}

//------------------------------------------------------------------------------
template<typename TInterface>
TInterface *IServiceLocator::buildInstance(const QString &tag)
{
    static_assert(std::is_base_of<QObject, TInterface>::value, "TInterface should derive from the QObject!");

    const char *className = TInterface::staticMetaObject.className();
    void *data = this->buildInstanceImpl(className, tag);

    QObject *obj = reinterpret_cast<QObject *>(data);
    TInterface *instance = qobject_cast<TInterface *>(obj);

    return instance;
}

//------------------------------------------------------------------------------
template<typename TService>
TService *IServiceLocator::locate()
{
    static_assert(std::is_base_of<QObject, TService>::value, "TService should derive from the QObject!");

    return this->locate<TService>("");
}

//------------------------------------------------------------------------------
template<typename TService>
TService *IServiceLocator::locate(const QString &tag)
{
    static_assert(std::is_base_of<QObject, TService>::value, "TService should derive from the QObject!");

    const QString &className = TService::staticMetaObject.className();
    void *data = this->getService(className, tag);

    QObject *obj = reinterpret_cast<QObject *>(data);
    TService *service = qobject_cast<TService *>(obj);

    return service;
}

//------------------------------------------------------------------------------
template<typename TService>
void IServiceLocator::registerInstance(TService *instance)
{
    static_assert(std::is_base_of<QObject, TService>::value, "TService should derive from the QObject!");

    this->registerInstance<TService>(instance, "");
}

//------------------------------------------------------------------------------
template<typename TService>
void IServiceLocator::registerInstance(TService *instance, const QString &tag)
{
    static_assert(std::is_base_of<QObject, TService>::value, "TService should derive from the QObject!");

    const QString &className = TService::staticMetaObject.className();
    this->registerInstanceImpl(reinterpret_cast<void *>(instance), className, tag);
}

//------------------------------------------------------------------------------
template<typename TInterface>
void IServiceLocator::registerType(factoryMethod method)
{
    static_assert(std::is_base_of<QObject, TInterface>::value, "TInterface should derive from the QObject!");

    this->registerType<TInterface>(method, "");
}

//------------------------------------------------------------------------------
template<typename TInterface>
void IServiceLocator::registerType(factoryMethod method, const QString &tag)
{
    static_assert(std::is_base_of<QObject, TInterface>::value, "TInterface should derive from the QObject!");

    const char *className = TInterface::staticMetaObject.className();
    this->registerTypeImpl(className, method, tag);
}

//------------------------------------------------------------------------------
template<typename TService>
TService *IServiceLocator::unregisterInstance()
{
    static_assert(std::is_base_of<QObject, TService>::value, "TService should derive from the QObject!");

    return this->unregisterInstance<TService>("");
}

//------------------------------------------------------------------------------
template<typename TService>
TService *IServiceLocator::unregisterInstance(const QString &tag)
{
    static_assert(std::is_base_of<QObject, TService>::value, "TService should derive from the QObject!");

    const char *className = TService::staticMetaObject.className();
    void *data = this->unregisterInstanceImpl(className, tag);

    QObject *obj = reinterpret_cast<QObject *>(data);
    TService *service = qobject_cast<TService *>(obj);

    return reinterpret_cast<TService *>(service);
}

//------------------------------------------------------------------------------
#endif // ISERVICELOCATOR_H
