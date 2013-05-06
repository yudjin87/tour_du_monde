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

#include "ServiceLocator.h"

#include "TypeObjectsMap.h"

//------------------------------------------------------------------------------
ServiceLocator::ServiceLocator()
    : mp_objects(new TypeObjectsMap<void *>())
    , mp_creators(new TypeObjectsMap<factoryMethod>())
{
}

//------------------------------------------------------------------------------
ServiceLocator::~ServiceLocator()
{
    delete mp_objects;
    mp_objects = nullptr;

    delete mp_creators;
    mp_creators = nullptr;
}

//------------------------------------------------------------------------------
void ServiceLocator::_registerType(const QString &typeIdName, factoryMethod method, const QString &tag)
  {
    mp_creators->registerInstance(method, typeIdName, tag);
}

//------------------------------------------------------------------------------
void *ServiceLocator::_unregister(const QString &i_forTypeId, const QString &i_tag)
{
    void *foundInstance = mp_objects->unregisterInstance(i_forTypeId, i_tag);
    return foundInstance;
}

//------------------------------------------------------------------------------
void *ServiceLocator::_buildInstance(const QString &typeIdName, const QString &tag) const
  {
  const factoryMethod &creator = mp_creators->getInstance(typeIdName, tag);
  void *data = creator();
  return data;
  }

//------------------------------------------------------------------------------
void *ServiceLocator::_getService(const QString &i_byTypeId, const QString &i_tag) const
{
    return mp_objects->getInstance(i_byTypeId, i_tag);
}

//------------------------------------------------------------------------------
void ServiceLocator::_register(void *ip_instance, const QString &i_forTypeId, const QString &i_tag)
{
    mp_objects->registerInstance(ip_instance, i_forTypeId, i_tag);
}

//------------------------------------------------------------------------------
