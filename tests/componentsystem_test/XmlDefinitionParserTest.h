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
#include <QtCore/QObject>
#include <QtCore/QByteArray>

class XmlDefinitionParserTest : public QObject
{
    Q_OBJECT
public:
    explicit XmlDefinitionParserTest(QObject *parent = 0);
    
private slots:
    void shouldReadValues();
    void shouldReadMinimalRequiredValues();
    void shouldReadNotFullValues();
    void shouldReturnFalseIfRootTagIsWrong();
    void shouldReturnFalseIfComponentNameAttrIsWrong();
    void shouldReturnFalseIfComponentNameAttrIsEmpty();
    void shouldNotReturnFalseIfShortNameAttrIsWrong();
    void shouldNotReturnFalseIfShortNameAttrIsEmpty();

private:
    static const QByteArray simpleXml;
    static const QByteArray minimalisticXml;
    static const QByteArray notFullXml;
    static const QByteArray wrongRootTagXml;
    static const QByteArray wrongComponentNameAttrXml;
    static const QByteArray emptyComponentNameAttrXml;
    static const QByteArray wrongComponentShortNameAttrXml;
    static const QByteArray emptyComponentShortNameAttrXml;

};

