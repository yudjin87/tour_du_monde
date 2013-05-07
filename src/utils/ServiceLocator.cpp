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
    : m_objects(new TypeObjectsMap<void *>())
    , m_creators(new TypeObjectsMap<factoryMethod>())
{
}

//------------------------------------------------------------------------------
ServiceLocator::~ServiceLocator()
{
    delete m_objects;
    m_objects = nullptr;

    delete m_creators;
    m_creators = nullptr;
}

//------------------------------------------------------------------------------
void ServiceLocator::_registerType(const QString &typeIdName, factoryMethod method, const QString &tag)
  {
    m_creators->registerInstance(method, typeIdName, tag);
}

//------------------------------------------------------------------------------
void *ServiceLocator::_unregister(const QString &forTypeId, const QString &tag)
{
    void *foundInstance = m_objects->unregisterInstance(forTypeId, tag);
    return foundInstance;
}

//------------------------------------------------------------------------------
void *ServiceLocator::_buildInstance(const QString &typeIdName, const QString &tag) const
  {
  const factoryMethod &creator = m_creators->getInstance(typeIdName, tag);
  void *data = creator();
  return data;
  }

//------------------------------------------------------------------------------
void *ServiceLocator::_getService(const QString &byTypeId, const QString &tag) const
{
    return m_objects->getInstance(byTypeId, tag);
}

//------------------------------------------------------------------------------
void ServiceLocator::_register(void *instance, const QString &forTypeId, const QString &tag)
{
    m_objects->registerInstance(instance, forTypeId, tag);
}

//------------------------------------------------------------------------------
