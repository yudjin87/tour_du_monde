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

#include "XmlDefinitionParserTest.h"

#include <carousel/componentsystem/XmlDefinitionParser.h>

#include <QtTest/QTest>

XmlDefinitionParserTest::XmlDefinitionParserTest(QObject *parent)
    : QObject(parent)
{
}

void XmlDefinitionParserTest::shouldReadValues()
{
    XmlDefinitionParser parser;
    bool result = parser.read(simpleXml);

    QVERIFY(result);
    QCOMPARE(parser.provider(), QString("CarouselTeam"));
    QCOMPARE(parser.componentName(), QString("TestingComponentDescription"));
    QCOMPARE(parser.componentShortName(), QString("org.test.TestingComponentDescription"));
    QCOMPARE(parser.version(), QString("1.2.3.4"));
    QCOMPARE(parser.description(), QString("Component Description"));
    QCOMPARE(parser.productName(), QString("Testing Component Description"));
    QCOMPARE(parser.componentLocation(), QString("/a/b/c/TestingComponentDescription"));
    QCOMPARE(parser.parents().size(), 3);
    QCOMPARE(parser.parents()["ComponentA"], QString("1.2.3.4"));
    QCOMPARE(parser.parents()["ComponentB"], QString("2.3.4.5"));
    QCOMPARE(parser.parents()["ComponentC"], QString("3.4.5.6"));
}

void XmlDefinitionParserTest::shouldReadMinimalRequiredValues()
{
    XmlDefinitionParser parser;
    bool result = parser.read(minimalisticXml);

    QVERIFY(result);
    QCOMPARE(parser.componentName(), QString("TestingComponentDescription"));
    QCOMPARE(parser.description(), QString(""));
    QCOMPARE(parser.productName(), QString(""));
    QCOMPARE(parser.componentLocation(), QString(""));
    QCOMPARE(parser.parents().size(), 0);
}

void XmlDefinitionParserTest::shouldReadNotFullValues()
{
    XmlDefinitionParser parser;
    bool result = parser.read(notFullXml);

    QVERIFY(result);
    QCOMPARE(parser.componentName(), QString("TestingComponentDescription"));
    QCOMPARE(parser.productName(), QString("Testing Component Description"));
    QCOMPARE(parser.componentLocation(), QString("/a/b/c/TestingComponentDescription"));
    QCOMPARE(parser.parents().size(), 0);
}

void XmlDefinitionParserTest::shouldReturnFalseIfRootTagIsWrong()
{
    XmlDefinitionParser parser;
    bool result = parser.read(wrongRootTagXml);

    QVERIFY(!result);
}

void XmlDefinitionParserTest::shouldReturnFalseIfComponentNameAttrIsWrong()
{
    XmlDefinitionParser parser;
    bool result = parser.read(wrongComponentNameAttrXml);

    QVERIFY(!result);
}

void XmlDefinitionParserTest::shouldReturnFalseIfComponentNameAttrIsEmpty()
{
    XmlDefinitionParser parser;
    bool result = parser.read(emptyComponentNameAttrXml);

    QVERIFY(!result);
}

void XmlDefinitionParserTest::shouldNotReturnFalseIfShortNameAttrIsWrong()
{
    XmlDefinitionParser parser;
    bool result = parser.read(wrongComponentShortNameAttrXml);

    QVERIFY(result);
}

void XmlDefinitionParserTest::shouldNotReturnFalseIfShortNameAttrIsEmpty()
{
    XmlDefinitionParser parser;
    bool result = parser.read(emptyComponentShortNameAttrXml);

    QVERIFY(result);
}


const QByteArray XmlDefinitionParserTest::simpleXml(
        "<component name=\"TestingComponentDescription\" shortName=\"org.test.TestingComponentDescription\">"
        "    <version>1.2.3.4</version> "
        "    <productName>Testing Component Description</productName>"
        "    <provider>CarouselTeam</provider> "
        "    <description>Component Description</description>"
        "    <location>/a/b/c/TestingComponentDescription</location>"
        "    <parents>"
        "        <parentComponent name=\"ComponentA\" version=\"1.2.3.4\"/>"
        "        <parentComponent name=\"ComponentC\" version=\"3.4.5.6\"/>"
        "        <parentComponent name=\"ComponentB\" version=\"2.3.4.5\"/>"
        "    </parents>"
        "</component>");

const QByteArray XmlDefinitionParserTest::minimalisticXml(
        "<component name=\"TestingComponentDescription\" >"
        "</component>");

const QByteArray XmlDefinitionParserTest::notFullXml(
        "<component name=\"TestingComponentDescription\" shortName=\"org.test.TestingComponentDescription\">"
        "    <productName>Testing Component Description</productName>"
        "    <location>/a/b/c/TestingComponentDescription</location>"
        "</component>");


const QByteArray XmlDefinitionParserTest::wrongRootTagXml(
        "<plugin name=\"TestingComponentDescription\">"
        "</plugin>");

const QByteArray XmlDefinitionParserTest::wrongComponentNameAttrXml(
        "<component componentName=\"TestingComponentDescription\">"
        "</component>");

const QByteArray XmlDefinitionParserTest::emptyComponentNameAttrXml(
        "<component name=\" \">"
        "</component>");


const QByteArray XmlDefinitionParserTest::wrongComponentShortNameAttrXml(
        "<component name=\"TestingComponentDescription\" shortName=\"org.test.TestingComponentDescription\">"
        "</component>");

const QByteArray XmlDefinitionParserTest::emptyComponentShortNameAttrXml(
        "<component name=\"TestingComponentDescription\" shortName=\" \">"
        "</component>");

