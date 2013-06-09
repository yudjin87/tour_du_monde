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

protected:
    /*!
     * @details
     *   When overridden in derived classes finds the factory method associated with
     *   specified type id and specified @a tag in inner objects dictionary and
     *   creates instance of the interface using factory method
     * @return The raw pointer corresponded with specified interface id and tag if such found.
     *   Null pointer otherwise.
     */
    void *buildInstanceImpl(const QString &forClassName, const QString &tag) const;

    /*!
     * @details
     *   Finds the pointer associated with specified
     *   type id and specified @a tag in inner objects dictionary.
     * @return The raw pointer corresponded with specified type id and tag if such found.
     *   Null pointer otherwise.
     */
    void *getService(const QString &forClassName, const QString &tag) const;

    /*!
     * @details
     *   Registers a raw pointer with specified tag in inner objects dictionary.
     * @param forClassName
     *   The name of type which @a instance should be associated with.
     */
    void registerInstanceImpl(void *instance, const QString &forClassName, const QString &tag);

    /*!
     * @details
     *   Binds an interface type id with specified factory method (that should create
     *   instance of interface) and with specified tag in inner objects dictionary.
     * @param forClassName
     *   The name of type which @a factory method should be associated with.
     */
    void registerTypeImpl(const QString &forClassName, factoryMethod method, const QString &tag);

    /*!
     * @details
     *   When overridden in derived classes unregisters (removes) a service instance with specified
     *   type id and tag from the inner objects dictionary (if any).
     * @param forClassName
     *   The name of type which removed instance should be associated with.
     * @return The raw pointer corresponded with specified type id and tag if such found.
     *   Null pointer otherwise.
     */
    void *unregisterInstanceImpl(const QString &forClassName, const QString &tag);

protected:
    TypeObjectsMap<void *> *m_objects;
    TypeObjectsMap<factoryMethod> *m_creators;
};

#endif // SERVICELOCATOR_H
