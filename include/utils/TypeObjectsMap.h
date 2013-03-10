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

#ifndef TYPEOBJECTSMAP_H
#define TYPEOBJECTSMAP_H

#include <QtCore/QString>
#include <QtCore/QVector>

template<typename>
struct InstanceObject;

/*!
 * @brief
 *   This utility class is a dictionary, used to store anonymous object
 *   and its type id as a key.
 * @details
 *   This class designed to store objects of unique anonymous type,
 *   and it uses type id to register specified instance and to navigate
 *   to it. It is used in service locators and component extensions.
 */
template<typename TValue>
class TypeObjectsMap
{
public:
    TypeObjectsMap();
    ~TypeObjectsMap();

    /*!
     * @details
     *   Finds pointer associated with specified type id and empty tag
     *   in inner objects dictionary.
     * @return The value corresponded with specified type id if such found. Null pointer otherwise.
     */
    TValue getInstance(const QString &i_byTypeId) const;

    /*!
     * @details
     *   Finds pointer associated with specified type id and specified @a i_tag
     *   in inner objects dictionary.
     * @return The value corresponded with specified type id and tag if such found. Null pointer otherwise.
     */
    TValue getInstance(const QString &i_byTypeId, const QString &i_tag) const;

    /*!
     * @details
     *   Registers a value with empty tag in inner objects dictionary.
     * @param i_forTypeId
     *   The name of type which @a ip_instance should be associated with.
     */
    void registerInstance(TValue ip_instance, const QString &i_forTypeId);

    /*!
     * @details
     *   Registers a value with specified tag in inner objects dictionary.
     * @param i_forTypeId
     *   The name of type which @a ip_instance should be associated with.
     */
    void registerInstance(TValue ip_instance, const QString &i_forTypeId, const QString &i_tag);

    /*!
     * @details
     *   Returns the amount of registered in map objects.
     */
    int size() const;

private:
    InstanceObject<TValue> *_findInstance(const QString &i_type_id, const QString &i_tag) const;

private:
    typedef QVector<InstanceObject<TValue> *> InstanceObjects;
    InstanceObjects m_objects;
};

//------------------------------------------------------------------------------
template<typename TObject>
struct InstanceObject
{
    InstanceObject<TObject>(TObject ip_instance, const QString &i_typeId, const QString &i_tag)
        : instance(ip_instance)
        , typeId(i_typeId)
        , tag(i_tag)
    {
    }

    TObject const instance;
    const QString typeId;
    const QString tag;
};

//------------------------------------------------------------------------------
template<typename TValue>
TypeObjectsMap<TValue>::TypeObjectsMap()
{
}

//------------------------------------------------------------------------------
template<typename TValue>
TypeObjectsMap<TValue>::~TypeObjectsMap()
{
    foreach(InstanceObject<TValue> *object, m_objects)
        delete object;
}

//------------------------------------------------------------------------------
template<typename TValue>
TValue TypeObjectsMap<TValue>::getInstance(const QString &i_byTypeId) const
{
    return getInstance(i_byTypeId, "");
}

//------------------------------------------------------------------------------
template<typename TValue>
TValue TypeObjectsMap<TValue>::getInstance(const QString &i_byTypeId, const QString &i_tag) const
{
    InstanceObject<TValue> *p_foundObject = _findInstance(i_byTypeId, i_tag);
    if (p_foundObject == nullptr)
      return nullptr;

    return p_foundObject->instance;
}

//------------------------------------------------------------------------------
template<typename TValue>
void TypeObjectsMap<TValue>::registerInstance(TValue ip_instance, const QString &i_forTypeId)
{
    registerInstance(ip_instance, i_forTypeId, "");
}

//------------------------------------------------------------------------------
template<typename TValue>
void TypeObjectsMap<TValue>::registerInstance(TValue ip_instance, const QString &i_forTypeId, const QString &i_tag)
{
    // should not register existing type:
    if (_findInstance(i_forTypeId, i_tag) != nullptr)
        return;

    InstanceObject<TValue> *p_newObj = new InstanceObject<TValue>(ip_instance, i_forTypeId, i_tag);

    m_objects.push_back(p_newObj);
}

//------------------------------------------------------------------------------
template<typename TValue>
int TypeObjectsMap<TValue>::size() const
{
    return m_objects.size();
}

//------------------------------------------------------------------------------
template<typename TValue>
InstanceObject<TValue> *TypeObjectsMap<TValue>::_findInstance(const QString &i_type_id, const QString &i_tag) const
{
    foreach(InstanceObject<TValue> *p_object, m_objects) {
        if ((p_object->typeId == i_type_id) && (p_object->tag == i_tag))
            return p_object;
    }

    return nullptr;
}

//------------------------------------------------------------------------------

#endif // TYPEOBJECTSMAP_H
