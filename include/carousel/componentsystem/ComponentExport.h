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
#include <QtCore/QPointer>

// This header has been written by influence of the similiar QtCore/qplugin.h

#ifdef __cplusplus
#  define EXTERN_C extern "C"
#else
#  define EXTERN_C extern
#endif // #ifdef __cplusplus

#if defined (Q_OS_WIN32) && defined(Q_CC_BOR)
#   define STANDARD_CALL __stdcall
#else
#   define STANDARD_CALL
#endif // #if defined (Q_OS_WIN32) && defined(Q_CC_BOR)

#define CREATE_INSTANCE createInstance
#define RELEASE_INSTANCE releaseInstance

#define CREATE_FUNCTION_NAME "createInstance"
#define RELEASE_FUNCTION_NAME "releaseInstance"

#define CREATE_INSTANCE_FUNCTION(COMPONENT_CLASS)                                               \
    EXTERN_C Q_DECL_EXPORT void * STANDARD_CALL CREATE_INSTANCE()                               \
    {                                                                                           \
        static QPointer<IComponent> component;                                                  \
        if (component.isNull())                                                                 \
            component = new COMPONENT_CLASS();                                                  \
        return component;                                                                       \
    }                                                                                           \

#define RELEASE_INSTANCE_FUNCTION(COMPONENT_CLASS)                                              \
    EXTERN_C Q_DECL_EXPORT void STANDARD_CALL RELEASE_INSTANCE(void *component)                 \
    {                                                                                           \
        delete reinterpret_cast<COMPONENT_CLASS *>(component);                                  \
    }                                                                                           \

#define EXPORT_COMPONENT(COMPONENT_CLASS)                                                       \
    CREATE_INSTANCE_FUNCTION(COMPONENT_CLASS)                                                   \
    RELEASE_INSTANCE_FUNCTION(COMPONENT_CLASS)                                                  \




