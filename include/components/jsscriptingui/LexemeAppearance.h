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
#include <components/jsscriptingui/jsscriptingui_global.h>

#include <QtCore/QObject>
#include <QtCore/QRegExp>
#include <QtGui/QColor>

class QRegExp;
class QTextCharFormat;

/*!
 * @brief
 */
class JSSCRIPTING_UI_API LexemeAppearance : public QObject
{
    Q_OBJECT
public:
    explicit LexemeAppearance(QObject *parent = nullptr);
    explicit LexemeAppearance(const QString &name, QObject *parent = nullptr);
    LexemeAppearance(const QString &name, const QString &pattern, QObject *parent = nullptr);
    LexemeAppearance(const QString &name, const QString &pattern, int weight, const QColor &foreground, QObject *parent = nullptr);
    LexemeAppearance(const QString &name, const QString &pattern, const QString &endPattern, int weight, const QColor &foreground, QObject *parent = nullptr);
    ~LexemeAppearance();

    const QString &name() const;
    void setName(const QString &name);

    const QRegExp &pattern() const;
    void setPattern(const QString &pattern);

    const QRegExp &endPattern() const;
    void setEndPattern(const QString &pattern);

    QTextCharFormat *format();
    const QTextCharFormat *format() const;

private:
    Q_DISABLE_COPY(LexemeAppearance)

private:
    QString m_name;
    QRegExp m_pattern;
    QRegExp m_endPattern;
    QTextCharFormat *m_format;
};

