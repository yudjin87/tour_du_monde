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

#include <QtCore/QStringList>
#include <QtCore/QString>
#include <QtCore/QVector>

#include <algorithm>
#include <functional>

template<typename>
struct InstanceObject;

/*!
 * @brief
 *   This utility class is a dictionary, used to store anonymous object
 *   by a key.
 * @details
 *   This class designed to store objects of anonymous type with unique keys.
 *   It is used in service locators and component extensions.
 */
template<typename TValue>
class TypeObjectsMap
{
public:
    TypeObjectsMap();
    ~TypeObjectsMap();

    /*!
     * @details
     *   Finds pointer associated with specified @a key and empty tag
     *   in inner objects dictionary.
     * @return The value corresponded with specified @a key if such found. Null pointer otherwise.
     */
    TValue getInstance(const QString &key, bool* success) const;

    /*!
     * @details
     *   Finds pointer associated with specified @a key and @a tag
     *   in inner objects dictionary.
     * @return The value corresponded with specified @a key if such found. Null pointer otherwise.
     */
    TValue getInstance(const QString &key, const QString &tag, bool* success) const;

    /*!
     * @details
     *   Registers a value with empty tag and specified @a key in inner objects dictionary.
     */
    void registerInstance(TValue instance, const QString &key);

    /*!
     * @details
     *   Registers a value with specified @a key and @a tag in inner objects dictionary.
     */
    void registerInstance(TValue instance, const QString &key, const QString &tag);

    /*!
     * @details
     *   Returns the amount of registered in map objects.
     */
    int size() const;

    /*!
     * @details
     *   Removes value with specified @a key and @a tag from the inner objects dictionary.
     * @return The raw pointer corresponded with specified @a key and @a tag if such found.
     *   Default value TValue() otherwise.
     */
    TValue unregisterInstance(const QString &key, const QString &tag);

    /*!
     * @details
     *   Returns all registered keys for instances;
     */
    QStringList keys() const;

    /*!
     * @details
     *   Returns all registered with specified @a tag keys for instances;
     */
    QStringList keys(const QString &tag) const;

private:
    InstanceObject<TValue> *findInstance(const QString &key, const QString &tag) const;
    static bool findPredicate(InstanceObject<TValue> *object, const QString &key, const QString &tag);

private:
    typedef QVector<InstanceObject<TValue> *> InstanceObjects;
    InstanceObjects m_objects;
};

//------------------------------------------------------------------------------
template<typename TObject>
struct InstanceObject
{
    InstanceObject<TObject>(TObject instance, const QString &aKey, const QString &tag)
        : instance(instance)
        , key(aKey)
        , tag(tag)
    {
    }

    TObject const instance;
    const QString key;
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
    for (InstanceObject<TValue> *object : m_objects)
        delete object;
}

//------------------------------------------------------------------------------
template<typename TValue>
TValue TypeObjectsMap<TValue>::getInstance(const QString &key, bool *success) const
{
    return getInstance(key, "", success);
}

//------------------------------------------------------------------------------
template<typename TValue>
TValue TypeObjectsMap<TValue>::getInstance(const QString &key, const QString &tag, bool* success) const
{
    InstanceObject<TValue> *foundObject = findInstance(key, tag);
    if (foundObject == nullptr)
    {
        if (success != nullptr) *success = false;
        return TValue();
    }

    if (success != nullptr) *success = true;
    return foundObject->instance;
}

//------------------------------------------------------------------------------
template<typename TValue>
void TypeObjectsMap<TValue>::registerInstance(TValue instance, const QString &key)
{
    registerInstance(instance, key, "");
}

//------------------------------------------------------------------------------
template<typename TValue>
void TypeObjectsMap<TValue>::registerInstance(TValue instance, const QString &key, const QString &tag)
{
    // should not register existing type:
    if (findInstance(key, tag) != nullptr)
        return;

    InstanceObject<TValue> *newObj = new InstanceObject<TValue>(instance, key, tag);

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
bool TypeObjectsMap<TValue>::findPredicate(InstanceObject<TValue> *object, const QString &key, const QString &tag)
{
    return (object->key == key) && (object->tag == tag);
}

//------------------------------------------------------------------------------
template<typename TValue>
TValue TypeObjectsMap<TValue>::unregisterInstance(const QString &key, const QString &tag)
{
    auto predicate = std::bind(&TypeObjectsMap<TValue>::findPredicate, std::placeholders::_1, key, tag);
    auto result = std::find_if(m_objects.begin(), m_objects.end(), predicate);

    if (result == m_objects.end())
        return TValue();

    InstanceObject<TValue> * foundInstance = *result;

    m_objects.erase(result);

    return foundInstance->instance;
}

//------------------------------------------------------------------------------
template<typename TValue>
QStringList TypeObjectsMap<TValue>::keys() const
{
    return keys("");
}

//------------------------------------------------------------------------------
template<typename TValue>
QStringList TypeObjectsMap<TValue>::keys(const QString &tag) const
{
    QStringList result;
    for (InstanceObject<TValue> *obj : m_objects) {
        if (obj->tag == tag)
            result.push_back(obj->key);
    }

    return result;
}

//------------------------------------------------------------------------------
template<typename TValue>
InstanceObject<TValue> *TypeObjectsMap<TValue>::findInstance(const QString &key, const QString &tag) const
{
    auto predicate = std::bind(&TypeObjectsMap<TValue>::findPredicate, std::placeholders::_1, key, tag);
    auto result = std::find_if(m_objects.begin(), m_objects.end(), predicate);

    if (result == m_objects.end())
        return nullptr;

    InstanceObject<TValue> * foundInstance = *result;
    return foundInstance;
}

//------------------------------------------------------------------------------
#endif // TYPEOBJECTSMAP_H
