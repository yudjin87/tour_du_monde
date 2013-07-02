#ifndef UTILS_H
#define UTILS_H

#include "fakes/MockChildComponent.h"
#include "fakes/MockComponent.h"

#include <QtCore/QtAlgorithms>
#include <QtCore/QString>

#include <memory>

#define QVERIFY_THROW(expression, ExpectedExceptionType) \
do \
{ \
    bool caught_ = false; \
    try { expression; } \
    catch (ExpectedExceptionType const&) { caught_ = true; } \
    catch (...) {} \
    if (!QTest::qVerify(caught_, #expression ", " #ExpectedExceptionType, "", __FILE__, __LINE__))\
        return; \
} while(0)
// #define QVERIFY_THROW

QString formatLibraryName(const QString &libName);
QString pathToLib(const QString &libName, bool decorateName = true);
QString pathToComponent(const QString &libName, bool decorateName = true);
QString pathToComponentDefinition(const QString &libName);
QString pathToComponentsDir();

bool removeDir(const QString & dirName);
//------------------------------------------------------------------------------

typedef std::unique_ptr<IComponent> IComponentPtr;
typedef std::unique_ptr<MockComponent> MockComponentPtr;
typedef std::unique_ptr<MockChildComponent> ChildComponentPtr;

MockComponent *createComponent(const QString &name, int major_version = 1, int minor_version = 0, int build_version = 0, int revision_version = 0);
MockChildComponent *createParentDefinition(const QString &name, const QString &dependsOn, int major_version = 1, int minor_version = 0, int build_version = 0, int revision_version = 0);
MockChildComponent *createParentDefinition(const QString &name, const QString &dependsOn, const QString &dependsOn2);
MockChildComponent *createParentDefinition(const QString &name, const QString &dependsOn, int major_version, const QString &dependsOn2, int major_version2);

//------------------------------------------------------------------------------
class IDirectoryComponentProvider;
template<typename TProvider>
class AutoComponentProvider : public TProvider
{
public:
    AutoComponentProvider(){}
    AutoComponentProvider(const QString &path)
        : TProvider(path){}

    AutoComponentProvider(IDirectoryComponentProvider *provider)
        : TProvider(provider){}

    ~AutoComponentProvider() { qDeleteAll(this->components()); }
};

#endif // UTILS_H
