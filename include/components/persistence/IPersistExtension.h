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

#ifndef IPERSISTEXTENSION_H
#define IPERSISTEXTENSION_H

#include <carousel/componentsystem/IComponentExtension.h>
#include <components/persistence/persistence_global.h>

class IServiceLocator;
class QJsonObject;

/*!
 * @brief
 *
 * @sa IComponent::extension()
 */
class PERSISTENCE_API IPersistExtension : public IComponentExtension
{
public:
    /*!
     * @details
     * @constructor{IPersistExtension}.
     */
    IPersistExtension(){}

    virtual void save(IServiceLocator *locator, QJsonObject &obj) = 0;
    virtual void load(IServiceLocator *locator, const QJsonObject &obj) = 0;

private:
    Q_DISABLE_COPY(IPersistExtension)
};
#endif // IPERSISTEXTENSION_H
