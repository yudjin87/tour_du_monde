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
#include <carousel/componentsystem/IComponentLocationConstructorDelegate.h>

/*!
 * @brief
 *   The AbsolutePathComponentLocationConstructorDelegate class is used
 *   to constuct an absolute path to the library for a component.
 * @details
 *   It uses definition's file path as a pivot, and a componen location path
 *   from the definition to format an absolute path.
 */
class CAROUSEL_API AbsolutePathComponentLocationConstructorDelegate : public IComponentLocationConstructorDelegate
{
public:
    /*!
     * @details
     *   Initializes a new instance of the AbsolutePathComponentLocationConstructorDelegate
     *   class uses the path to the definition file.
     *
     *   To get the absolute library file name a definition's file path is used
     *   as a pivot for relative component path.
     */
    AbsolutePathComponentLocationConstructorDelegate(const QString &definitionLocation);
    ~AbsolutePathComponentLocationConstructorDelegate();

    /*!
     * @details
     *   Completes component location and returns the absolute path
     *   to the component.
     */
    QString constructLocation(const QString &relativePathToComponent) override;

private:
    QString m_definitionLocation;
};

