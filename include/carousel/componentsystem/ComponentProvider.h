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

#ifndef COMPONENTPROVIDER_H
#define COMPONENTPROVIDER_H

#include <carousel/componentsystem/componentsystem_global.h>
#include <carousel/componentsystem/IComponentProvider.h>

/*!
 * @brief
 *   Provides base methods to register components statically in code.
 * @details
 *   Created by defaul in the BootloaderBase::createComponentProvider() method during boot loading
 *   sequence. You can override BootloaderBase::createComponentProvider() method to instantiate your
 *   own component provider (e.g. DirectoryComponentProvider, that can discovering components in the file system).
 *
 *   You also might to override BootloaderBase::configureComponentProvider() to add compile-time-known components 
 *   statically in code using registerComponent() method:
 * @code
 *   class MyBootloader : public CarouselBootloader
 *   {
 *   protected:
 *      void MyBootloader::configureComponentProvider()
 *      {
 *          m_componentProvider->registerComponent(new MyComponentA());
 *          m_componentProvider->registerComponent(new MyComponentB());
 *      }
 *   };
 * @endcode
 *   The ComponentProvider also serves as a base class for more specialized Providers.
 * @note it does not take ownership for registered components.
 */
class COMP_API ComponentProvider : public IComponentProvider
{
    Q_OBJECT
public:
    explicit ComponentProvider(QObject *parent = nullptr);
    ~ComponentProvider();

     /*!
     * @details
     *   Gets the all components registered at the provider.
     */
    QList<IComponent *> components() const;

    /*!
     * @details
     *   Initializes the provider, which may load and validate the components.
     *   Returns @a true, if initialization was succesful; otherwise, returns @a false.
     */
    bool initialize();

    /*!
     * @details
     *   Returns @a true, if provider alreadyinitialzied; otherwise, returns @a false.
     */
    bool isInitialized() const;

    /*!
     * @details
     *   Registers the specified component at the provider.
     *   Usually, you can register the same components or components with same names using 
     *   existing providers, but when components will be pushed to the IComponentManager
     *   from the providers - the last one doesn't allow duplicating components.
     *   @a Null pointers will be skipped.
     */
    void registerComponent(IComponent *component);

protected:
    /*!
     * @details
     *   It is a defensive declaration of the public initialize() method, that invokes only if provider is 
     *   not initialized yet.
     *   When override in derived classes initializes the provider, which may load and validate 
     *   the components. Nothing to do by default.
     */
    virtual bool onInitialize();

private:
    QList<IComponent *> m_components;
    bool m_alreadyInit;
};

#endif // COMPONENTPROVIDER_H
