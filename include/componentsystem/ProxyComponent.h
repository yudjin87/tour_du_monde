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

#ifndef PROXYCOMPONENT_H
#define PROXYCOMPONENT_H

#include "componentsystem/BaseComponent.h"

class IDefinitionParser;
class IComponentLoader;

class COMP_API ProxyComponent : public BaseComponent
{
    Q_OBJECT
public:
    /*!
     * @details
     *   Initializes a new instance of the ProxyComponent class with
     *   default component loader and specified parent.
     */
    explicit ProxyComponent(ComponentDefinition *definition, QObject *parent = nullptr);

    /*!
     * @details
     *   Initializes a new instance of the ProxyComponent class with
     *   component loader and parent.
     */
    ProxyComponent(ComponentDefinition *definition, IComponentLoader *loader, QObject *parent = nullptr);

    ~ProxyComponent();

    /*!
     * @details
     *   Finds extension's pointer associated with it type id
     *   in inner objects dictionary.
     * @return The raw pointer corresponded with specified type id if such found. Null pointer otherwise.
     */
    void *getExtension(const QString &i_byTypeId) const;

    IComponent *loadedComponent() const;

    /*!
     * @details
     *   Sets up definition properties and component name using @a parser.
     *
     *   Returns false if component library could not be loaded.
     *
     *   @a parser should already read properties.
     */
    virtual bool initialize();

    /*!
     * @details
     *   Sets the path to the definition file.
     *
     *   To get the absolute library file name a definition's file path is used
     *   as a pivot for relative component path. The DirectoryComponentProvider
     *   should set up this property.
     */
    void setDefinitionLocation(const QString &definitionLocation);

protected:
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

private:
    Q_DISABLE_COPY(ProxyComponent)
    IComponentLoader *mp_loader;
    IComponent *mp_component;
    bool m_initialized;
    QString m_definitionLocation;
};

#endif // PROXYCOMPONENT_H
