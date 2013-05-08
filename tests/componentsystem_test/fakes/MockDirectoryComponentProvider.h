#ifndef MOCKDIRECTORYCOMPONENTPROVIDER_H
#define MOCKDIRECTORYCOMPONENTPROVIDER_H

#include <componentsystem/DirectoryComponentProvider.h>
#include <componentsystem/FileComponentProvider.h>

class FakeFileComponentProvider;

class MockDirectoryComponentProvider : public DirectoryComponentProvider
{
public:
    MockDirectoryComponentProvider();
    MockDirectoryComponentProvider(const QString &path);
    ~MockDirectoryComponentProvider();

    QList<IComponent *> update();

    bool initialize();

protected:
    FileComponentProvider *createFileComponentProvider(const QString &definitionPath);

public:
    FakeFileComponentProvider *parser;
    int updateCalled;
    int providersCreated;
    bool initializeCalled;
    bool initializeReturnValue;
    QList<IComponent *> updateResult;
};

class FakeFileComponentProvider : public FileComponentProvider
{
public:
    explicit FakeFileComponentProvider(QObject *parent = nullptr);
    FakeFileComponentProvider(const QString &path, QObject *parent = nullptr);

protected:
    bool onInitialize();

public:
    static bool initializeReturnValue;
};

#endif // MOCKDIRECTORYCOMPONENTPROVIDER_H
