#include "MockDirectoryComponentProvider.h"

#include "MockComponent.h"

#include <QtCore/QtAlgorithms>
//------------------------------------------------------------------------------
MockDirectoryComponentProvider::MockDirectoryComponentProvider()
    : DirectoryComponentProvider()
    , parser(nullptr)
    , updateCalled(0)
    , providersCreated(0)
    , initializeCalled(false)
    , initializeReturnValue(true)
{
}

//------------------------------------------------------------------------------
MockDirectoryComponentProvider::MockDirectoryComponentProvider(const QString &path)
    : DirectoryComponentProvider(path)
    , parser(nullptr)
    , updateCalled(0)
    , providersCreated(0)
    , initializeCalled(false)
    , initializeReturnValue(true)
{
}

//------------------------------------------------------------------------------
MockDirectoryComponentProvider::~MockDirectoryComponentProvider()
{
    qDeleteAll(this->components());
}

//------------------------------------------------------------------------------
QVector<IComponent *> MockDirectoryComponentProvider::update()
{
    updateCalled++;

    if (updateResult.isEmpty())
        return DirectoryComponentProvider::update();

    return updateResult;
}

//------------------------------------------------------------------------------
bool MockDirectoryComponentProvider::initialize()
{
    initializeCalled = true;
    DirectoryComponentProvider::initialize();

    return initializeReturnValue;
}

//------------------------------------------------------------------------------
FileComponentProvider *MockDirectoryComponentProvider::createFileComponentProvider(const QString &definitionPath)
{
    ++providersCreated;
    return new FakeFileComponentProvider(definitionPath);
}

//------------------------------------------------------------------------------
bool FakeFileComponentProvider::initializeReturnValue = true;

//------------------------------------------------------------------------------
FakeFileComponentProvider::FakeFileComponentProvider(QObject *parent)
    : FileComponentProvider(parent)
{
}

//------------------------------------------------------------------------------
FakeFileComponentProvider::FakeFileComponentProvider(const QString &path, QObject *parent)
    : FileComponentProvider(path, parent)
{
}

//------------------------------------------------------------------------------
bool FakeFileComponentProvider::_initialize()
{
    FileComponentProvider::_initialize();
    return initializeReturnValue;
}

//------------------------------------------------------------------------------
