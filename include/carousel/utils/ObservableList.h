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

#ifndef OBSERVABLELIST_H
#define OBSERVABLELIST_H

#include <carousel/utils/IListObserver.h>
#include <carousel/utils/Changes.h>

#include <QtCore/QList>
#include <QtCore/QSet>
#include <QtCore/QtAlgorithms>

/*!
 * @brief
 *   The ObservableList class is a template class that provides observable lists.
 * @details
 *   ObservableList<TItem> extends Qt's generic container classes by adding observable availability.
 *   It stores a list of values and provides almost all functionality as well as QList<TItem> does.
 *
 *   Also it provides two methods for inistalling (installObserver()) and removing (removeObserver())
 *   observers, which want to know about this list changed (items were added, removed, sorted, etc).
 *
 * @note ObservableList does not take ownership on the observers.
 */
template <typename TItem>
class ObservableList
{
public:
    ObservableList();
    ~ObservableList();

    void installObserver(IListObserver<TItem> *observer) const;
    bool removeObserver(IListObserver<TItem> *observer) const;

    /*!
     * @details
     *   Inserts @a item at the end of the list.
     *
     *   This is the same as list.insert(0, @a item).
     *   This operation is usually very fast (constant time), because list
     *   preallocates extra space on both sides of its internal buffer to
     *   allow for fast growth at both ends of the list.
     *
     *   Notify observers with ChangedAction::Add action and added item.
     */
    void append(const TItem &item);

    /*!
     * @details
     * @overload
     *
     *   Appends the items of the value list to this list.
     */
    void append(const QList<TItem> &items);

    /*!
     * @details
     *   Inserts @a item at the beginning of the list.
     *
     *   This is the same as list.insert(0, @a item).
     *   This operation is usually very fast (constant time), because list
     *   preallocates extra space on both sides of its internal buffer to
     *   allow for fast growth at both ends of the list.
     *
     *   Notify observers with ChangedAction::Add action and added item.
     */
    void prepend(const TItem &item);

    /*!
     * @details
     *   Returns the number of items in the list.
     */
    int size() const;

    /*!
     * @details
     *   Returns true if the list contains no items; otherwise returns false.
     */
    bool isEmpty() const;

    /*!
     * @details
     *   Removes all items from the list.
     *
     *   Notify observers with ChangedAction::Reset action and purged items.
     */
    void clear();

    /*!
     * @details
     *   Returns the item at index position @a index as a modifiable reference.
     *   @a index must be a valid index position in the list (i.e., 0 <= @a index < size()).
     *
     *   This function is very fast (constant time).
     */
    const TItem &at(int index) const;

    /*!
     * @details
     *   Returns the item at index position @a index as a modifiable reference.
     *   @a index must be a valid index position in the list (i.e., 0 <= @a index < size()).
     *
     *   This function is very fast (constant time).
     */
    const TItem &operator[](int index) const;

    /*!
     * @details
     * @overload
     *
     *   Same as at().
     */
    TItem operator[](int index);

    /*!
     * @details
     *   Reserve space for @a size elements.
     *
     *   If @a size is smaller than the current size of the list,
     *   nothing will happen.
     *
     *   Use this function to avoid repetetive reallocation of list's
     *   internal data if you can predict how many elements will be appended.
     *   Note that the reservation applies only to the internal pointer array.
     */
    void reserve(int size);

    /*!
     * @details
     *   Removes the item at index position @a index. @a index must be a valid
     *   index position in the list (i.e., 0 <= @a index < size()).
     *
     *   Notify observers with ChangedAction::Remove action and removed
     *   by specified index item.
     */
    void removeAt(int index);

    /*!
     * @details
     *   Removes all occurrences of value in the list and returns the number of
     *   entries removed.
     *
     *   Notify observers with ChangedAction::Remove action and removed
     *   items.
     */
    int removeAll(const TItem &item);

    /*!
     * @details
     *   Removes the first occurrence of @a item in the list and returns true
     *   on success; otherwise returns false.
     *
     *   Notify observers with ChangedAction::Remove action and removed item.
     */
    bool removeOne(const TItem &item);

    /*!
     * @details
     *   Returns the index position of the first occurrence of @a item in the
     *   list, searching forward from index position @a from. Returns -1 if
     *   no item matched.
     */
    int indexOf(const TItem &item, int from = 0) const;

    /*!
     * @details
     *   Returns the index position of the last occurrence of @a item in the list,
     *   searching backward from index position @a from. If @a from is -1 (the default),
     *   the search starts at the last item. Returns -1 if no item matched.
     */
    int lastIndexOf(const TItem &item, int from = -1) const;

    /*!
     * @details
     *   Returns @a true if the list contains an occurrence of @a item;
     *   otherwise returns @a false.
     *
     *   This function requires the @a item type to have an implementation
     *   of operator==().
     */
    bool contains(const TItem &item) const;

    /*!
     * @details
     *   Returns the number of items in the list. This is effectively the same as size().
     */
    int count() const;

    /*!
     * @details
     *   Returns the number of occurrences of @a item in the list.
     *
     *   This function requires the @a item type to have an implementation
     *   of operator==().
     */
    int count(const TItem &item) const;

    /*!
     * @details
     *   Returns a reference to the first item in the list.
     *   The list must not be empty. If the list can be empty,
     *   call isEmpty() before calling this function.
     */
    TItem first();

    /*!
     * @details
     * @overload
     */
    const TItem& first() const;

    /*!
     * @details
     *   Returns a reference to the last item in the list.
     *   The list must not be empty. If the list can be empty,
     *   call isEmpty() before calling this function.
     */
    TItem last();

    /*!
     * @details
     * @overload
     */
    const TItem& last() const;

    class const_iterator : public QList<TItem>::const_iterator
    {
    public:
        const_iterator(const typename QList<TItem>::const_iterator &other)
            : QList<TItem>::const_iterator(other)
        {
        }
    };

    /*!
     * @details
     *   Returns a const STL-style iterator pointing to the
     *   first item in the list.
     */
    typename QList<TItem>::const_iterator begin() const;

    /*!
     * @details
     *   Returns a const STL-style iterator pointing to the
     *   first item in the list.
     */
    typename QList<TItem>::const_iterator constBegin() const;

    /*!
     * @details
     *   Returns a const STL-style iterator pointing to the
     *   imaginary item after the last item in the list.
     */
    typename QList<TItem>::const_iterator end() const;

    /*!
     * @details
     *   Returns a const STL-style iterator pointing to the
     *   imaginary item after the last item in the list.
     */
    typename QList<TItem>::const_iterator constEnd() const;

    /*!
     * @details
     *   This function is provided for STL compatibility. It is equivalent
     *   to append(@a item).
     *
     *   Notify observers with ChangedAction::Add action and added item.
     */
    void push_back(const TItem &item);
    /*!
     * @details
     *   This function is provided for STL compatibility. It is equivalent
     *   to prepend(@a item).
     *
     *   Notify observers with ChangedAction::Add action and added item.
     */
    void push_front(const TItem &item);

    /*!
     * @details
     *   This function is provided for STL compatibility. It is equivalent
     *   to first(). The list must not be empty. If the list can be empty,
     *   call isEmpty() before calling this function.
     */
    const TItem& front() const;

    /*!
     * @details
     *   This function is provided for STL compatibility. It is equivalent to
     *   last(). The list must not be empty. If the list can be empty, call
     *   isEmpty() before calling this function.
     */
    const TItem& back() const;

    /*!
     * @details
     *   This function is provided for STL compatibility. It is equivalent to
     *   isEmpty() and returns true if the list is empty.
     */
    bool empty() const;

    /*!
     * @details
     *   Returns list representation.
     */
    QList<TItem> toList() const;

    /*!
     * @details
     *   Sorts the items in ascending order using the the QtAlgorithms'
     *   qSort() method.
     *
     *   Notify observers with ChangedAction::Reset action and all items.
     */
    void sort();

    /*!
     * @details
     * @overload
     *
     *   Uses the @a lessThan function instead of operator<() to compare the items.
     */
    template< template <typename> class LessThan>
    void sort(LessThan<TItem> &lessThan);

private:
    void notifyObservers(Changes<TItem>& changes);

private:
    QList<TItem> m_items;
    mutable QSet<IListObserver<TItem> *> m_observers;
};

//------------------------------------------------------------------------------
template <typename TItem>
ObservableList<TItem>::ObservableList()
    : m_observers(QSet<IListObserver<TItem> *>())
{
}

//------------------------------------------------------------------------------
template <typename TItem>
ObservableList<TItem>::~ObservableList()
{
    m_observers.clear();
    m_items.clear();
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::installObserver(IListObserver<TItem> *observer) const
{
    m_observers.insert(observer);
}

//------------------------------------------------------------------------------
template <typename TItem>
bool ObservableList<TItem>::removeObserver(IListObserver<TItem> *observer) const
{
    return m_observers.remove(observer);
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::append(const TItem &item)
{
    m_items.append(item);

    Changes<TItem> changes(Add, item);
    notifyObservers(changes);
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::append(const QList<TItem> &items)
{
    m_items.append(items);

    Changes<TItem> changes(Add, items);
    notifyObservers(changes);
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::prepend(const TItem &item)
{
    m_items.prepend(item);

    Changes<TItem> changes(Add, item);
    notifyObservers(changes);
}

//------------------------------------------------------------------------------
template <typename TItem>
int ObservableList<TItem>::size() const
{
    return m_items.size();
}

//------------------------------------------------------------------------------
template <typename TItem>
bool ObservableList<TItem>::isEmpty() const
{
    return m_items.isEmpty();
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::clear()
{
    if (m_items.empty())
        return;

    Changes<TItem> changes(Reset, m_items);

    m_items.clear();

    notifyObservers(changes);
}

//------------------------------------------------------------------------------
template <typename TItem>
const TItem &ObservableList<TItem>::at(int index) const
{
    return m_items.at(index);
}

//------------------------------------------------------------------------------
template <typename TItem>
const TItem &ObservableList<TItem>::operator [](int index) const
{
    return m_items[index];
}

//------------------------------------------------------------------------------
template <typename TItem>
TItem ObservableList<TItem>::operator [](int index)
{
    return m_items[index];
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::reserve(int size)
{
    m_items.reserve(size);
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::removeAt(int index)
{
    const TItem &item = m_items[index];
    removeOne(item);
}

//------------------------------------------------------------------------------
template <typename TItem>
int ObservableList<TItem>::removeAll(const TItem &item)
{    
    if (m_items.indexOf(item) == -1)
        return 0;

    QList<TItem> items;
    for (const TItem &itemInList : m_items) {
        bool sameItem = itemInList == item;
        if (sameItem && m_items.contains(itemInList))
            items.push_back(itemInList);
    }

    if (items.empty())
        return 0;

    m_items.removeAll(item);

    Changes<TItem> changes(Remove, items);
    notifyObservers(changes);

    return items.size();
}

//------------------------------------------------------------------------------
template <typename TItem>
bool ObservableList<TItem>::removeOne(const TItem &item)
{
    bool result = m_items.removeOne(item);
    if (!result)
        return false;

    Changes<TItem> changes(Remove, item);
    notifyObservers(changes);

    return result;
}

//------------------------------------------------------------------------------
template <typename TItem>
int ObservableList<TItem>::indexOf(const TItem &item, int from) const
{
    return m_items.indexOf(item, from);
}

//------------------------------------------------------------------------------
template <typename TItem>
int ObservableList<TItem>::lastIndexOf(const TItem &item, int from) const
{
    return m_items.lastIndexOf(item, from);
}

//------------------------------------------------------------------------------
template <typename TItem>
bool ObservableList<TItem>::contains(const TItem &item) const
{
    return m_items.contains(item);
}

//------------------------------------------------------------------------------
template <typename TItem>
int ObservableList<TItem>::count() const
{
    return m_items.count();
}

//------------------------------------------------------------------------------
template <typename TItem>
int ObservableList<TItem>::count(const TItem &item) const
{
    return m_items.count(item);
}

//------------------------------------------------------------------------------
template <typename TItem>
TItem ObservableList<TItem>::first()
{
    return m_items.first();
}

//------------------------------------------------------------------------------
template <typename TItem>
const TItem &ObservableList<TItem>::first() const
{
    return m_items.first();
}

//------------------------------------------------------------------------------
template <typename TItem>
const TItem &ObservableList<TItem>::last() const
{
    return m_items.last();
}

//------------------------------------------------------------------------------
template <typename TItem>
TItem ObservableList<TItem>::last()
{
    return m_items.last();
}

//------------------------------------------------------------------------------
template <typename TItem>
typename QList<TItem>::const_iterator ObservableList<TItem>::begin() const
{
    return m_items.begin();
}

//------------------------------------------------------------------------------
template <typename TItem>
typename QList<TItem>::const_iterator ObservableList<TItem>::constBegin() const
{
    return m_items.constBegin();
}

//------------------------------------------------------------------------------
template <typename TItem>
typename QList<TItem>::const_iterator ObservableList<TItem>::end() const
{
    return m_items.end();
}

//------------------------------------------------------------------------------
template <typename TItem>
typename QList<TItem>::const_iterator ObservableList<TItem>::constEnd() const
{
    return m_items.constEnd();
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::push_back(const TItem &item)
{
    m_items.push_back(item);

    Changes<TItem> changes(Add, item);
    notifyObservers(changes);
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::push_front(const TItem &item)
{
    m_items.push_front(item);

    Changes<TItem> changes(Add, item);
    notifyObservers(changes);
}

//------------------------------------------------------------------------------
template <typename TItem>
const TItem &ObservableList<TItem>::front() const
{
    return m_items.front();
}

//------------------------------------------------------------------------------
template <typename TItem>
const TItem &ObservableList<TItem>::back() const
{
    return m_items.back();
}

//------------------------------------------------------------------------------
template <typename TItem>
bool ObservableList<TItem>::empty() const
{
    return m_items.empty();
}

//------------------------------------------------------------------------------
template <typename TItem>
QList<TItem> ObservableList<TItem>::toList() const
{
    return m_items;
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::sort()
{
    qSort(m_items);

    Changes<TItem> changes(Reset, m_items);
    notifyObservers(changes);
}

//------------------------------------------------------------------------------
template <typename TItem>
template <template<typename> class LessThan>
void ObservableList<TItem>::sort(LessThan<TItem> &lessThan)
{
    qSort(m_items.begin(), m_items.end(), lessThan);

    Changes<TItem> changes(Reset, m_items);
    notifyObservers(changes);
}

//------------------------------------------------------------------------------
template <typename TItem>
void ObservableList<TItem>::notifyObservers(Changes<TItem>& changes)
{
    for (IListObserver<TItem> *observer : m_observers)
        observer->onChanged(changes);
}

//------------------------------------------------------------------------------

#endif // OBSERVABLELIST_H
