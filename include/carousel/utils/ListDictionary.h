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

#pragma once
#include <QtCore/QList>
#include <QtCore/QMap>

/*!
 * @brief
 *   The ListDictionary class is specialisation for the multivalue string dictionary.
 */
template<typename TKey, typename TValue>
class ListDictionary : public QMap <TKey, QList<TValue> *>
{
public:
    typedef QList<TValue> Container;
public:
    ~ListDictionary();

public:
    /*!
     * @details
     *   Adds key with empty list to the dictionary.
     */
    void add(const TKey &key);

    /*!
     * @details
     *   Adds value to the list for specified key. If lists not found
     *   for this key, adds key with empty list to the dictionary.
     */
    void add(const TKey &key, const TValue &value);

private:
    Container* createNewList(const TKey &key);
};

template<typename TKey, typename TValue>
ListDictionary<TKey, TValue>::~ListDictionary()
{
    typename ListDictionary::Iterator it = QMap <TKey, Container *>::begin();
    typename ListDictionary::Iterator endIt = QMap <TKey, Container *>::end();
    for(; it != endIt; ++it)
        delete *it;
}

template<typename TKey, typename TValue>
void ListDictionary<TKey, TValue>::add(const TKey &key)
{
    createNewList(key);
}

template<typename TKey, typename TValue>
void ListDictionary<TKey, TValue>::add(const TKey &key, const TValue &value)
{
    if (this->contains(key)) {
        this->value(key)->push_back(value);
    }
    else {
        Container* values = createNewList(key);
        values->push_back(value);
    }
}

template<typename TKey, typename TValue>
typename ListDictionary<TKey, TValue>::Container* ListDictionary<TKey, TValue>::createNewList(const TKey &key)
{
    Container* values = new Container();
    this->insert(key, values);
    return values;
}


