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

#ifndef LOGGING_GLOBAL_H
#define LOGGING_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(STATIC_BUILD)
#   define LOGGING_API
#else
#   if defined(LOGGING_LIBRARY)
#       define LOGGING_API Q_DECL_EXPORT
#   else
#       define LOGGING_API Q_DECL_IMPORT
#   endif //#if defined(LOGGING_LIBRARY)
#endif //#if defined(STATIC_BUILD)

#endif // LOGGING_GLOBAL_H
