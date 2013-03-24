#include "Utils.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtTest/QtTest>

#ifdef Q_OS_WIN32
    static const QString libraryPattern("%1.dll");
#endif // Q_WS_WIN
#ifdef Q_OS_MAC
    static const QString libraryPattern("lib%1.dylib");
#endif // Q_WS_MAC
#ifdef Q_OS_LINUX
    static const QString libraryPattern("lib%1.so");
#endif // Q_WS_X11

//------------------------------------------------------------------------------
QString pathToLib(const QString &i_libName, bool decorateName)
{
    QDir libDir(qApp->applicationDirPath());
    libDir.cd("libs");

    QString libName = decorateName
            ? libraryPattern.arg(i_libName)
            : i_libName;

    QString absoluteLibFileName = libDir.absoluteFilePath(libName);

    QTest::qVerify(!absoluteLibFileName.isEmpty(), "!absoluteLibFileName.isEmpty()", "Empty path string", __FILE__, __LINE__);

    return absoluteLibFileName;
}

//------------------------------------------------------------------------------
QString pathToComponent(const QString &i_libName, bool decorateName)
{
    QDir componentDir(qApp->applicationDirPath());
    componentDir.cd("components");

    QString componentName = decorateName
            ? libraryPattern.arg(i_libName)
            : i_libName;

    QString absoluteComponentFileName = componentDir.absoluteFilePath(componentName);

    QTest::qVerify(!absoluteComponentFileName.isEmpty(), "!absoluteLibFileName.isEmpty()", "Empty path string", __FILE__, __LINE__);

    return absoluteComponentFileName;
}

//------------------------------------------------------------------------------
QString pathToComponentDefinition(const QString &i_libName)
{
    QDir componentDir(qApp->applicationDirPath());
    componentDir.cd("components");

    QString definitionFileName = QString("%1.definition").arg(i_libName);

    QString absoluteComponentFileName = componentDir.absoluteFilePath(definitionFileName);

    QTest::qVerify(!absoluteComponentFileName.isEmpty(), "!absoluteLibFileName.isEmpty()", "Empty path string", __FILE__, __LINE__);

    return absoluteComponentFileName;
}

//------------------------------------------------------------------------------
QString pathToComponentsDir()
{
    QDir libDir(qApp->applicationDirPath());
    libDir.cd("components");

    QTest::qVerify(!libDir.absolutePath().isEmpty(), "!libDir.absolutePath().isEmpty()", "Empty path string", __FILE__, __LINE__);

    return libDir.absolutePath();
}

//------------------------------------------------------------------------------
MockChildComponent* createParentComponent(const QString &i_name, const QString &i_dependsOn)
{
    MockChildComponent *p_component = new MockChildComponent(i_name);
    p_component->parents().push_back(i_dependsOn);

    return p_component;
}

//------------------------------------------------------------------------------
MockChildComponent *createParentComponent(const QString &i_name, const QString &i_dependsOn, const QString &i_dependsOn2)
{
    MockChildComponent *p_component = new MockChildComponent(i_name);
    p_component->parents().push_back(i_dependsOn);
    p_component->parents().push_back(i_dependsOn2);

    return p_component;
}

//------------------------------------------------------------------------------
MockComponent* createComponent(const QString &i_name)
{
    MockComponent *p_component = new MockComponent(i_name);
    return p_component;
}

//------------------------------------------------------------------------------
