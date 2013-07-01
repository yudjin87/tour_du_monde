#include "Utils.h"

#include <carousel/componentsystem/ParentDefinition.h>

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
QString formatLibraryName(const QString &libName)
{
    return libraryPattern.arg(libName);
}

//------------------------------------------------------------------------------
QString pathToLib(const QString &libName, bool decorateName)
{
    QDir libDir(qApp->applicationDirPath());
    libDir.cd("libs");

    QString decoratedLibName = decorateName
            ? libraryPattern.arg(libName)
            : libName;

    QString absoluteLibFileName = libDir.absoluteFilePath(decoratedLibName);

    QTest::qVerify(!absoluteLibFileName.isEmpty(), "!absoluteLibFileName.isEmpty()", "Empty path string", __FILE__, __LINE__);

    return absoluteLibFileName;
}

//------------------------------------------------------------------------------
QString pathToComponent(const QString &libName, bool decorateName)
{
    QDir componentDir(qApp->applicationDirPath());
    componentDir.cd("components");

    QString componentName = decorateName
            ? libraryPattern.arg(libName)
            : libName;

    QString absoluteComponentFileName = componentDir.absoluteFilePath(componentName);

    QTest::qVerify(!absoluteComponentFileName.isEmpty(), "!absoluteLibFileName.isEmpty()", "Empty path string", __FILE__, __LINE__);

    return absoluteComponentFileName;
}

//------------------------------------------------------------------------------
QString pathToComponentDefinition(const QString &libName)
{
    QDir componentDir(qApp->applicationDirPath());
    componentDir.cd("components");

    QString definitionFileName = QString("%1.definition").arg(libName);

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
MockChildComponent* createParentDefinition(const QString &name, const QString &dependsOn)
{
    MockChildComponent *component = new MockChildComponent(name);
    component->parents().append(new ParentDefinition(dependsOn));

    return component;
}

//------------------------------------------------------------------------------
MockChildComponent *createParentDefinition(const QString &name, const QString &dependsOn, const QString &dependsOn2)
{
    MockChildComponent *component = new MockChildComponent(name);
    component->parents().append(new ParentDefinition(dependsOn));
    component->parents().append(new ParentDefinition(dependsOn2));

    return component;
}

//------------------------------------------------------------------------------
MockComponent* createComponent(const QString &name)
{
    MockComponent *component = new MockComponent(name);
    return component;
}

//------------------------------------------------------------------------------
bool removeDir(const QString & dirName)
{
    bool result = false;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        foreach(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

//------------------------------------------------------------------------------
