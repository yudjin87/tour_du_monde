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

#include "Version.h"

#include <QtCore/QStringList>

//------------------------------------------------------------------------------
Version::Version(QObject *parent)
    : QObject(parent)
    , m_major_version(0)
    , m_minor_version(0)
    , m_build_version(0)
    , m_revision_version(0)
{
}

//------------------------------------------------------------------------------
Version::Version(int major_version, int minor_version, int build_version, int revision_version, QObject *parent)
    : QObject(parent)
    , m_major_version(major_version)
    , m_minor_version(minor_version)
    , m_build_version(build_version)
    , m_revision_version(revision_version)
{
}

//------------------------------------------------------------------------------
Version::~Version()
{
    m_major_version = 0;
    m_minor_version = 0;
    m_build_version = 0;
    m_revision_version = 0;
}

//------------------------------------------------------------------------------
Version *Version::fromString(const QString &version, bool *ok)
{
    if (ok != nullptr)
        *ok = false;

    int major = 0;
    int minor = 0;
    int build = 0;
    int revision = 0;

    if(!Version::parseString(version, &major, &minor, &build, &revision))
        return nullptr;

    if (ok != nullptr)
        *ok = true;

    return new Version(major, minor, build, revision);
}

//------------------------------------------------------------------------------
bool Version::parseString(const QString &version, int *major, int *minor, int *build, int *revision)
{
    *major = 0;
    *minor = 0;
    if (build != nullptr)
        *build = 0;

    if (revision != nullptr)
        *revision = 0;

    QStringList numbers = version.split('.');
    QStringList::ConstIterator it = numbers.begin();

    bool result = true;
    int temp_major = (*it).toInt(&result);
    if (!result)
        return false;

    ++it;
    int temp_minor = (*it).toInt(&result);
    if (!result)
        return false;

    ++it;
    if (it == numbers.end()) { // We can skip last two numbers
        *major = temp_major;
        *minor = temp_minor;
        return true;
    }

    int temp_build = (*it).toInt(&result);
    if (!result)
        return false;

    ++it;
    if (it == numbers.end()) { // We can skip last number
        *major = temp_major;
        *minor = temp_minor;
        *build = temp_build;
        return true;
    }

    int temp_revision = (*it).toInt(&result);
    if (!result)
        return false;

    *major = temp_major;
    *minor = temp_minor;
    if (build != nullptr)
        *build = temp_build;

    if (revision != nullptr)
        *revision = temp_revision;

    return true;
}

//------------------------------------------------------------------------------
bool Version::isEmpty() const
{
    return *this == Version(0, 0, 0, 0);
}

//------------------------------------------------------------------------------
bool Version::operator<(const Version &other) const
{
    return (compare(other) < 0);
}

//------------------------------------------------------------------------------
bool Version::operator<=(const Version &other) const
{
    return (compare(other) <= 0);
}

//------------------------------------------------------------------------------
bool Version::operator>(const Version &other) const
{
    return (compare(other) > 0);
}

//------------------------------------------------------------------------------
bool Version::operator>=(const Version &other) const
{
    return (compare(other) >= 0);
}

//------------------------------------------------------------------------------
bool Version::operator==(const Version &other) const
{
    return (m_major_version == other.m_major_version)
            && (m_minor_version == other.m_minor_version)
            && (m_build_version == other.m_build_version)
            && (m_revision_version == other.m_revision_version);
}

//------------------------------------------------------------------------------
bool Version::operator!=(const Version &other) const
{
    return !(*this == other);
}

//------------------------------------------------------------------------------
void Version::setVersion(int major_version, int minor_version, int build_version, int revision_version)
{
    m_major_version = major_version;
    m_minor_version = minor_version;
    m_build_version = build_version;
    m_revision_version = revision_version;
}

//------------------------------------------------------------------------------
QString Version::toString() const
{
    return QString("%1.%2.%3.%4")
            .arg(m_major_version)
            .arg(m_minor_version)
            .arg(m_build_version)
            .arg(m_revision_version);
}

//------------------------------------------------------------------------------
void Version::setMajor(int major_version)
{
    m_major_version = major_version;
}

//------------------------------------------------------------------------------
void Version::setMinor(int minor_version)
{
    m_minor_version = minor_version;
}

//------------------------------------------------------------------------------
void Version::setBuild(int build_version)
{
    m_build_version = build_version;
}

//------------------------------------------------------------------------------
void Version::setRevision(int revision_version)
{
    m_revision_version = revision_version;
}

//------------------------------------------------------------------------------
int Version::major() const
{
    return m_major_version;
}

//------------------------------------------------------------------------------
int Version::minor() const
{
    return m_minor_version;
}

//------------------------------------------------------------------------------
int Version::build() const
{
    return m_build_version;
}

//------------------------------------------------------------------------------
int Version::revision() const
{
    return m_revision_version;
}

//------------------------------------------------------------------------------
int Version::compare(const Version &other) const
{
    if (m_major_version < other.m_major_version)
        return -1;
    else if (m_major_version > other.m_major_version)
        return 1;

    if (m_minor_version < other.m_minor_version)
        return -1;
    else if (m_minor_version > other.m_minor_version)
        return 1;

    if (m_build_version < other.m_build_version)
        return -1;
    else if (m_build_version > other.m_build_version)
        return 1;

    if (m_revision_version < other.m_revision_version)
        return -1;
    else if (m_revision_version > other.m_revision_version)
        return 1;

    return 0;
}
