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

#ifndef BOOTING_GLOBAL_H
#define BOOTING_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(STATIC_BUILD)
#   define BOOTING_API
#else
#   if defined(BOOTING_LIBRARY)
#       define BOOTING_API Q_DECL_EXPORT
#   else
#       define BOOTING_API Q_DECL_IMPORT
#   endif //#if defined(BOOTING_LIBRARY)
#endif //#if defined(STATIC_BUILD)

#endif // BOOTING_GLOBAL_H
