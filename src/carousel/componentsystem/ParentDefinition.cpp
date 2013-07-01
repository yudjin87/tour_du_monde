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

#include "ParentDefinition.h"
#include "Version.h"

//------------------------------------------------------------------------------
ParentDefinition::ParentDefinition(const QString &name, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_version(new Version(1, 0))
{
}

//------------------------------------------------------------------------------
ParentDefinition::ParentDefinition(const QString &name, Version *version, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_version(version)
{
}

//------------------------------------------------------------------------------
ParentDefinition::ParentDefinition(const QString &name, int major_version, int minor_version, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_version(new Version(major_version, minor_version))
{
}

//------------------------------------------------------------------------------
ParentDefinition::ParentDefinition(const QString &name, int major_version, int minor_version, int build_version, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_version(new Version(major_version, minor_version, build_version))
{
}

//------------------------------------------------------------------------------
ParentDefinition::ParentDefinition(const QString &name, int major_version, int minor_version, int build_version, int revision_version, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_version(new Version(major_version, minor_version, build_version, revision_version))
{
}

//------------------------------------------------------------------------------
ParentDefinition::~ParentDefinition()
{
    delete m_version;
    m_version = nullptr;
}

//------------------------------------------------------------------------------
const QString &ParentDefinition::name() const
{
    return m_name;
}

//------------------------------------------------------------------------------
const Version *ParentDefinition::version() const
{
    return m_version;
}
