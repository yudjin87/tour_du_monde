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

#include "LexemeAppearance.h"

#include <QtGui/QTextCharFormat>

//------------------------------------------------------------------------------
LexemeAppearance::LexemeAppearance(QObject *parent)
    : QObject(parent)
    , m_name("")
    , m_pattern()
    , m_endPattern()
    , m_format(new QTextCharFormat())
{
}

//------------------------------------------------------------------------------
LexemeAppearance::LexemeAppearance(const QString &name, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_pattern()
    , m_endPattern()
    , m_format(new QTextCharFormat())
{
}

//------------------------------------------------------------------------------
LexemeAppearance::LexemeAppearance(const QString &name, const QString &pattern, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_pattern(pattern)
    , m_endPattern()
    , m_format(new QTextCharFormat())
{

}

//------------------------------------------------------------------------------
LexemeAppearance::LexemeAppearance(const QString &name, const QString &pattern, int weight, const QColor &foreground, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_pattern(pattern)
    , m_endPattern()
    , m_format(new QTextCharFormat())
{
    m_format->setForeground(foreground);
    m_format->setFontWeight(weight);
}

//------------------------------------------------------------------------------
LexemeAppearance::LexemeAppearance(const QString &name, const QString &pattern, const QString &endPattern, int weight, const QColor &foreground, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_pattern(pattern)
    , m_endPattern(endPattern)
    , m_format(new QTextCharFormat())
{
    m_format->setForeground(foreground);
    m_format->setFontWeight(weight);
}

//------------------------------------------------------------------------------
LexemeAppearance::~LexemeAppearance()
{
    delete m_format;
    m_format = nullptr;
}

//------------------------------------------------------------------------------
const QRegExp &LexemeAppearance::pattern() const
{
    return m_pattern;
}

//------------------------------------------------------------------------------
void LexemeAppearance::setPattern(const QString &pattern)
{
    m_pattern.setPattern(pattern);
}

//------------------------------------------------------------------------------
const QRegExp &LexemeAppearance::endPattern() const
{
    return m_endPattern;
}

//------------------------------------------------------------------------------
void LexemeAppearance::setEndPattern(const QString &pattern)
{
    m_endPattern.setPattern(pattern);
}

//------------------------------------------------------------------------------
QTextCharFormat *LexemeAppearance::format()
{
    return m_format;
}

//------------------------------------------------------------------------------
const QTextCharFormat *LexemeAppearance::format() const
{
    return m_format;
}

//------------------------------------------------------------------------------
const QString &LexemeAppearance::name() const
{
    return m_name;
}

//------------------------------------------------------------------------------
void LexemeAppearance::setName(const QString &name)
{
    m_name = name;
}

//------------------------------------------------------------------------------
