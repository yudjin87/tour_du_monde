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

QString formatLibraryName(const QString &i_libName);
QString pathToLib(const QString &i_libName, bool decorateName = true);
QString pathToComponent(const QString &i_libName, bool decorateName = true);
QString pathToComponentDefinition(const QString &i_libName);
QString pathToComponentsDir();

bool removeDir(const QString & dirName);
//------------------------------------------------------------------------------

// TODO: will replace with std::uniq_ptr when c++11 is supported
typedef std::auto_ptr<IComponent> IComponentPtr;
typedef std::auto_ptr<MockComponent> MockComponentPtr;
typedef std::auto_ptr<MockChildComponent> ChildComponentPtr;

MockComponent *createComponent(const QString &i_name);
MockChildComponent *createParentComponent(const QString &i_name, const QString &i_dependsOn);
MockChildComponent *createParentComponent(const QString &i_name, const QString &i_dependsOn, const QString &i_dependsOn2);


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
