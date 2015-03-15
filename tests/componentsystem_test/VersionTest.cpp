#include "VersionTest.h"

#include <carousel/componentsystem/Version.h>

#include <QtTest/QTest>

VersionTest::VersionTest(QObject *parent)
    : QObject(parent)
{
}

void VersionTest::parseString_shouldReturnTrueFor4Numbers()
{
    QString vers = "1.2.3.4";
    int major = 0;
    int minor = 0;
    int build = 0;
    int revision = 0;

    QVERIFY(Version::parseString(vers, &major, &minor, &build, &revision));

    QCOMPARE(major, 1);
    QCOMPARE(minor, 2);
    QCOMPARE(build, 3);
    QCOMPARE(revision, 4);
}

void VersionTest::parseString_shouldReturnTrueFor3Numbers()
{
    QString vers = "1.2.3";
    int major = 0;
    int minor = 0;
    int build = 0;

    QVERIFY(Version::parseString(vers, &major, &minor, &build));

    QCOMPARE(major, 1);
    QCOMPARE(minor, 2);
    QCOMPARE(build, 3);
}

void VersionTest::parseString_shouldReturnTrueFor2Numbers()
{
    QString vers = "1.2";
    int major = 0;
    int minor = 0;

    QVERIFY(Version::parseString(vers, &major, &minor));

    QCOMPARE(major, 1);
    QCOMPARE(minor, 2);
}

void VersionTest::parseString_shouldReturnFalseFor1Number()
{
    QString vers = "1.";
    int major = 0;
    int minor = 0;

    QCOMPARE(Version::parseString(vers, &major, &minor), false);

    QCOMPARE(major, 0);
    QCOMPARE(minor, 0);
}

void VersionTest::fromString_shouldReturnVersion()
{
    QString vers = "1.2.3.4";
    bool ok = false;

    Version *version = Version::fromString(vers, &ok);
    QVERIFY(ok);

    QCOMPARE(version->toString(), QString("1.2.3.4"));

    delete version;
}

void VersionTest::fromString_shouldReturnNullIfFailed()
{
    QString vers = "1.";
    bool ok = false;

    Version *version = Version::fromString(vers, &ok);
    QVERIFY(!ok);

    QVERIFY(version == nullptr);
}

