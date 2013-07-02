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

#ifndef PARENTCOMPONENTS_H
#define PARENTCOMPONENTS_H

#include <carousel/componentsystem/componentsystem_global.h>

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>

class ParentDefinition;
class Version;

/*!
 * @brief
 *   This class defines a collection of the parent component properties,
 *   required for the child startup.
 * @details
 *   Besides standart collection manipulating methods it also provides convinient methods
 *   for specific tasks, like existing by name.
 *
 * @sa ComponentDefinition::parents()
 */
class COMP_API ParentDefinitions : public QObject
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{ParentDefinitions}.
     */
    explicit ParentDefinitions(QObject *parent = nullptr);
    ~ParentDefinitions();

    /*!
     * @details
     *    Returns @a true, if parent definition with such name exists.
     *    Otherwise, returns @a false.
     */
    bool contains(const QString &parentName) const;

    /*!
     * @details
     *   Adds a @a parent description to the collection.
     *
     *   Note, that it takes ownership for the @a parent.
     */
    void append(ParentDefinition *parent);

    /*!
     * @details
     *    Returns amount of parent definitions in the collection.
     */
    int size() const;

    /*!
     * @details
     *    Returns a version of parent definition by its name, if any.
     *    Otherwise, a @a nullptr will be returned.
     */
    const Version *operator[](const QString &parentName) const;

    /*!
     * @details
     *    Returns a parent definition by its @a index.
     *
     * @note The bounds are not checked.
     */
    const ParentDefinition *operator[](int index) const;

    class const_iterator : public QList<ParentDefinition *>::const_iterator
    {
    public:
        const_iterator(const QList<ParentDefinition *>::const_iterator &other)
            : QList<ParentDefinition *>::const_iterator(other)
        {
        }
    };

    /*!
     * @details
     *   Returns a const STL-style iterator pointing to the
     *   first parent in the list.
     */
    QList<ParentDefinition *>::const_iterator begin() const;

    /*!
     * @details
     *   Returns a const STL-style iterator pointing to the
     *   first parent in the list.
     */
    QList<ParentDefinition *>::const_iterator constBegin() const;

    /*!
     * @details
     *   Returns a const STL-style iterator pointing to the
     *   imaginary item after the last parent in the list.
     */
    QList<ParentDefinition *>::const_iterator end() const;

    /*!
     * @details
     *   Returns a const STL-style iterator pointing to the
     *   imaginary item after the last parent in the list.
     */
    QList<ParentDefinition *>::const_iterator constEnd() const;

private:
    Q_DISABLE_COPY(ParentDefinitions)

private:
    QList<ParentDefinition *> m_parents;
};

#endif // PARENTCOMPONENTS_H
