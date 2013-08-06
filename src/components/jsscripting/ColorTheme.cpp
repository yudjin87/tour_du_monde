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

#include "ColorTheme.h"
#include "LexemeAppearance.h"

#include <QtCore/QtAlgorithms>
#include <QtGui/QFont>

//------------------------------------------------------------------------------
namespace
{
ColorTheme *createDefaultTheme()
{
    ColorTheme *theme = new ColorTheme();

    // keyword lexems
    theme->addLexeme(new LexemeAppearance("var",        "\\bvar\\b",       QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("Array",      "\\bArray\\b",     QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("function",   "\\bfunction\\b",  QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("return",     "\\breturn\\b",    QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("arguments",  "\\barguments\\b", QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("if",         "\\bif\\b",        QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("else",       "\\belse\\b",      QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("for",        "\\bfor\\b",       QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("switch",     "\\bswitch\\b",    QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("case",       "\\bcase\\b",      QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("break",      "\\bbreak\\b",     QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("while",      "\\bwhile\\b",     QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("true",      "\\btrue\\b",     QFont::Bold, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("false",      "\\bfalse\\b",     QFont::Bold, Qt::darkBlue));

    //
    theme->addLexeme(new LexemeAppearance("number",     "\\b[0-9]+\\b",            QFont::Normal, Qt::darkBlue));
    theme->addLexeme(new LexemeAppearance("class",      "\\bQ[A-Za-z]+\\b",        QFont::Bold,   Qt::darkMagenta));
    theme->addLexeme(new LexemeAppearance("quotation",  "\".*\"",                  QFont::Normal, Qt::darkGreen));
    theme->addLexeme(new LexemeAppearance("apostrophe", "\'.*\'",                  QFont::Normal, Qt::darkGreen));
    theme->addLexeme(new LexemeAppearance("function()", "\\b[A-Za-z0-9_]+(?=\\()", QFont::Normal, Qt::blue));

    // comments
    theme->addLexeme(new LexemeAppearance("comment",               "//[^\n]*", QFont::Normal, Qt::darkGray));
    theme->addBlockLexeme(new LexemeAppearance("block comment (start)", "/\\*", "\\*/", QFont::Normal, Qt::darkGray));

    return theme;
}
} // namespace

//------------------------------------------------------------------------------
ColorTheme::ColorTheme(QObject *parent)
    : QObject(parent)
    , m_name("")
    , m_lexemes(QList<LexemeAppearance *>())
    , m_blockLexemes(QList<LexemeAppearance *>())
{
}

//------------------------------------------------------------------------------
ColorTheme::ColorTheme(const QString &name, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_lexemes(QList<LexemeAppearance *>())
    , m_blockLexemes(QList<LexemeAppearance *>())
{

}

//------------------------------------------------------------------------------
ColorTheme::~ColorTheme()
{
    qDeleteAll(m_lexemes);
    m_lexemes.clear();

    qDeleteAll(m_blockLexemes);
    m_blockLexemes.clear();
}

//------------------------------------------------------------------------------
const QString &ColorTheme::name() const
{
    return m_name;
}

//------------------------------------------------------------------------------
void ColorTheme::setName(const QString &name)
{
    m_name = name;
}

//------------------------------------------------------------------------------
void ColorTheme::addLexeme(LexemeAppearance *lexeme)
{
    m_lexemes.push_back(lexeme);
}

//------------------------------------------------------------------------------
void ColorTheme::addBlockLexeme(LexemeAppearance *lexeme)
{
    m_blockLexemes.push_back(lexeme);
}

//------------------------------------------------------------------------------
const QList<LexemeAppearance *> &ColorTheme::lexemes() const
{
    return m_lexemes;
}

//------------------------------------------------------------------------------
const QList<LexemeAppearance *> &ColorTheme::blockLexemes() const
{
    return m_blockLexemes;
}

//------------------------------------------------------------------------------
ColorTheme *ColorTheme::getDefault()
{
    static ColorTheme *theme = createDefaultTheme();
    return theme;
}

//------------------------------------------------------------------------------
