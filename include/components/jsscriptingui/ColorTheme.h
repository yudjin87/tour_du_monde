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
#include <QtCore/QList>

class LexemeAppearance;

/*!
 * @brief
 */
class JSSCRIPTING_UI_API ColorTheme : public QObject
{
    Q_OBJECT
public:
    explicit ColorTheme(QObject *parent = nullptr);
    explicit ColorTheme(const QString &name, QObject *parent = nullptr);
    ~ColorTheme();

    static ColorTheme *getDefault();

    const QString &name() const;
    void setName(const QString &name);

    /*!
     * @details
     *   Takes ownership.
     */
    void addLexeme(LexemeAppearance *lexeme);

    /*!
     * @details
     *   Takes ownership.
     */
    void addBlockLexeme(LexemeAppearance *lexeme);

    const QList<LexemeAppearance *> &lexemes() const;

    const QList<LexemeAppearance *> &blockLexemes() const;
private:
    Q_DISABLE_COPY(ColorTheme)

private:
    QString m_name;
    QList<LexemeAppearance *> m_lexemes;
    QList<LexemeAppearance *> m_blockLexemes;
};

