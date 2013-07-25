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

#include "CodeHighlighter.h"
#include "ColorTheme.h"
#include "LexemeAppearance.h"

//------------------------------------------------------------------------------
CodeHighlighter::CodeHighlighter(ColorTheme *theme, QObject *parent)
    : QSyntaxHighlighter(parent)
    , m_theme(theme)
{
}

//------------------------------------------------------------------------------
CodeHighlighter::~CodeHighlighter()
{

}

//------------------------------------------------------------------------------
void CodeHighlighter::highlightBlock(const QString &text)
{
    highlightLines(text);
    highlightCommentBlocks(text);
}

//------------------------------------------------------------------------------
void CodeHighlighter::highlightLines(const QString &text)
{
    const QList<LexemeAppearance *> &lexemes = m_theme->lexemes();
    for (const LexemeAppearance *lexeme : lexemes) {
        const QRegExp &pattern = lexeme->pattern();
        int index = pattern.indexIn(text);
        while (index >= 0) {
            int length = pattern.matchedLength();
            setFormat(index, length, *lexeme->format());
            index = pattern.indexIn(text, index + length);
        }
    }
}

//------------------------------------------------------------------------------
void CodeHighlighter::highlightCommentBlocks(const QString &text)
{
    const QList<LexemeAppearance *> &lexemes = m_theme->blockLexemes();

    for (const LexemeAppearance *lexeme : lexemes) {
        const QRegExp &startPattern = lexeme->pattern();
        const QRegExp &endPattern = lexeme->endPattern();

        setCurrentBlockState(0);

        int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = startPattern.indexIn(text);

        while (startIndex >= 0) {
            int endIndex = endPattern.indexIn(text, startIndex);
            int commentLength;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex + endPattern.matchedLength();
            }

            setFormat(startIndex, commentLength, *lexeme->format());
            startIndex = startPattern.indexIn(text, startIndex + commentLength);
        }
    }
}

//------------------------------------------------------------------------------




