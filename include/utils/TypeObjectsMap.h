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

#include <algorithm>
#include <functional>

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
    TValue getInstance(const QString &byTypeId) const;

    /*!
     * @details
     *   Finds pointer associated with specified type id and specified @a tag
     *   in inner objects dictionary.
     * @return The value corresponded with specified type id and tag if such found. Null pointer otherwise.
     */
    TValue getInstance(const QString &byTypeId, const QString &tag) const;

    /*!
     * @details
     *   Registers a value with empty tag in inner objects dictionary.
     * @param forTypeId
     *   The name of type which @a instance should be associated with.
     */
    void registerInstance(TValue instance, const QString &forTypeId);

    /*!
     * @details
     *   Registers a value with specified tag in inner objects dictionary.
     * @param forTypeId
     *   The name of type which @a instance should be associated with.
     */
    void registerInstance(TValue instance, const QString &forTypeId, const QString &tag);

    /*!
     * @details
     *   Returns the amount of registered in map objects.
     */
    int size() const;

    /*!
     * @details
     *   Removes value with specified type and tag from the inner objects dictionary.
     * @param forTypeId
     *   The name of type which removed instance should be associated with.
     * @return The raw pointer corresponded with specified type id and tag if such found.
     *   Null pointer otherwise.
     */
    TValue unregisterInstance(const QString &forTypeId, const QString &tag);

private:
    InstanceObject<TValue> *findInstance(const QString &type_id, const QString &tag) const;
    static bool findPredicate(InstanceObject<TValue> *object, const QString &type_id, const QString &tag);

private:
    typedef QVector<InstanceObject<TValue> *> InstanceObjects;
    InstanceObjects m_objects;
};

//------------------------------------------------------------------------------
template<typename TObject>
struct InstanceObject
{
    InstanceObject<TObject>(TObject instance, const QString &typeId, const QString &tag)
        : instance(instance)
        , typeId(typeId)
        , tag(tag)
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
TValue TypeObjectsMap<TValue>::getInstance(const QString &byTypeId) const
{
    return getInstance(byTypeId, "");
}

//------------------------------------------------------------------------------
template<typename TValue>
TValue TypeObjectsMap<TValue>::getInstance(const QString &byTypeId, const QString &tag) const
{
    InstanceObject<TValue> *foundObject = findInstance(byTypeId, tag);
    if (foundObject == nullptr)
      return nullptr;

    return foundObject->instance;
}

//------------------------------------------------------------------------------
template<typename TValue>
void TypeObjectsMap<TValue>::registerInstance(TValue instance, const QString &forTypeId)
{
    registerInstance(instance, forTypeId, "");
}

//------------------------------------------------------------------------------
template<typename TValue>
void TypeObjectsMap<TValue>::registerInstance(TValue instance, const QString &forTypeId, const QString &tag)
{
    // should not register existing type:
    if (findInstance(forTypeId, tag) != nullptr)
        return;

    InstanceObject<TValue> *newObj = new InstanceObject<TValue>(instance, forTypeId, tag);

    m_objects.push_back(newObj);
}

//------------------------------------------------------------------------------
template<typename TValue>
int TypeObjectsMap<TValue>::size() const
{
    return m_objects.size();
}

//------------------------------------------------------------------------------
template<typename TValue>
bool TypeObjectsMap<TValue>::findPredicate(InstanceObject<TValue> *object, const QString &type_id, const QString &tag)
{
    return (object->typeId == type_id) && (object->tag == tag);
}

//------------------------------------------------------------------------------
template<typename TValue>
TValue TypeObjectsMap<TValue>::unregisterInstance(const QString &forTypeId, const QString &tag)
{
    auto predicate = std::bind(&TypeObjectsMap<TValue>::findPredicate, std::placeholders::_1, forTypeId, tag);
    auto result = std::find_if(m_objects.begin(), m_objects.end(), predicate);

    if (result == m_objects.end())
        return TValue();

    InstanceObject<TValue> * foundInstance = *result;

    m_objects.erase(result);

    return foundInstance->instance;
}

//------------------------------------------------------------------------------
template<typename TValue>
InstanceObject<TValue> *TypeObjectsMap<TValue>::findInstance(const QString &type_id, const QString &tag) const
{
    auto predicate = std::bind(&TypeObjectsMap<TValue>::findPredicate, std::placeholders::_1, type_id, tag);
    auto result = std::find_if(m_objects.begin(), m_objects.end(), predicate);

    if (result == m_objects.end())
        return nullptr;

    InstanceObject<TValue> * foundInstance = *result;
    return foundInstance;
}

//------------------------------------------------------------------------------

#endif // TYPEOBJECTSMAP_H
