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

#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H

#include <carousel/utils/IServiceLocator.h>

template<typename TValue>
class TypeObjectsMap;

/*!
 * @brief
 *   The ServiceLocator class provides default implementation of the central registry of the services.
 * @details
 *   It is a utility class and you won't use often in trivial - use IServiceLocator interface instead.
 *   The ServiceLocator instance created by default by the BootloaderBase::createServiceLocator() member
 *   during the loading sequence, and you should to override this member if you want use your own service 
 *   locator in the application.
 */
class UTILS_API ServiceLocator : public IServiceLocator
{
public:
    ServiceLocator();
    ~ServiceLocator();

    /*!
     * @details
     *   Creates and returns a @a className pointer using empty tag and registered
     *   factory method, if any. Returns nullptr otherwise.
     *   This may be usefull for scpipting, where no templates.
     * @return the corresponding service if such found. Null pointer otherwise.
     * @note Does not take ownership of the created pointer.
     */
    QObject *buildObject(const QString &className) override;

    /*!
     * @details
     *   Creates and returns a @a className pointer using specified tag and registered
     *   factory method, if any. Returns nullptr otherwise.
     *   This may be usefull for scpipting, where no templates.
     * @return the corresponding service if such found. Null pointer otherwise.
     * @note Does not take ownership of the created pointer.
     */
    QObject *buildObject(const QString &className, const QString &tag) override;

    /*!
     * @details
     *   Finds the service registered with @a className and empty tag and returns
     *   a QObject pointer to it.
     *   This may be usefull for scpipting, where no templates.
     * @return the corresponding service if such found. Null pointer otherwis
     */
    QObject *locateToObject(const QString &className) override;

    /*!
     * @details
     *   Finds the service registered with @a className and empty tag and returns
     *   a QObject pointer to it.
     *   This may be usefull for scpipting, where no templates.
     * @return the corresponding service if such found. Null pointer otherwis
     */
    QObject *locateToObject(const QString &className, const QString &tag) override;

    /*!
     *   Gets the services, registered with an empty tag
     */
    QStringList services() const override;

    /*!
     *   Gets the registered with @a tag services;
     */
    QStringList services(const QString &tag) const override;

protected:
    /*!
     * @details
     *   When overridden in derived classes finds the factory method associated with
     *   specified type id and specified @a tag in inner objects dictionary and
     *   creates instance of the interface using factory method
     * @return The raw pointer corresponded with specified interface id and tag if such found.
     *   Null pointer otherwise.
     */
    void *buildInstanceImpl(const QString &className, const QString &tag) override;

    /*!
     * @details
     *   Finds the pointer associated with specified
     *   type id and specified @a tag in inner objects dictionary.
     * @return The raw pointer corresponded with specified type id and tag if such found.
     *   Null pointer otherwise.
     */
    void *getService(const QString &className, const QString &tag) override;

    /*!
     * @details
     *   Registers a raw pointer with specified tag in inner objects dictionary.
     * @param className
     *   The name of type which @a instance should be associated with.
     */
    void registerInstanceImpl(void *instance, const QString &className, const QString &tag) override;

    /*!
     * @details
     *   Binds an interface type id with specified factory method (that should create
     *   instance of interface) and with specified tag in inner objects dictionary.
     * @param className
     *   The name of type which @a factory method should be associated with.
     */
    void registerTypeImpl(const QString &className, factoryMethod method, const QString &tag) override;

    /*!
     * @details
     *   When overridden in derived classes unregisters (removes) a service instance with specified
     *   type id and tag from the inner objects dictionary (if any).
     * @param className
     *   The name of type which removed instance should be associated with.
     * @return The raw pointer corresponded with specified type id and tag if such found.
     *   Null pointer otherwise.
     */
    void *unregisterInstanceImpl(const QString &className, const QString &tag) override;

protected:
    TypeObjectsMap<void *> *m_objects;
    TypeObjectsMap<factoryMethod> *m_creators;
};

#endif // SERVICELOCATOR_H
