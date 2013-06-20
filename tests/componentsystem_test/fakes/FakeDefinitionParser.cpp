#include "FakeDefinitionParser.h"

#include "../Utils.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

//------------------------------------------------------------------------------
FakeDefinitionParser::FakeDefinitionParser()
    : QObject()
    , m_componentName("TestComponent2")
    , m_shortName("")
    , m_componentLocation("")
    , m_description("")
    , m_productName("")
    , m_provider("")
    , m_error("")
    , m_version("")
    , m_parents()
{
    QDir absolutePath = QCoreApplication::applicationDirPath();
    m_componentLocation = absolutePath.relativeFilePath(pathToComponent("TestComponent2", false));
}

//------------------------------------------------------------------------------
const QString &FakeDefinitionParser::error() const
{
    return m_error;
}

//------------------------------------------------------------------------------
bool FakeDefinitionParser::read(const QString &text)
{
    Q_UNUSED(text)
    emit readCalled();
    return true;
}

//------------------------------------------------------------------------------
bool FakeDefinitionParser::read(const QByteArray &text)
{
    Q_UNUSED(text)
    emit readCalled();
    return true;
}

//------------------------------------------------------------------------------
bool FakeDefinitionParser::read(QIODevice *dev)
{
    Q_UNUSED(dev)
    emit readCalled();
    return true;
}

//------------------------------------------------------------------------------
const QString &FakeDefinitionParser::componentName() const
{
    return m_componentName;
}

//------------------------------------------------------------------------------
const QString &FakeDefinitionParser::componentShortName() const
{
    return m_shortName;
}

//------------------------------------------------------------------------------
const QString &FakeDefinitionParser::componentLocation() const
{
    return m_componentLocation;
}

//------------------------------------------------------------------------------
const QString &FakeDefinitionParser::description() const
{
    return m_description;
}

//------------------------------------------------------------------------------
const QStringList &FakeDefinitionParser::parents() const
{
    return m_parents;
}

//------------------------------------------------------------------------------
const QString &FakeDefinitionParser::productName() const
{
    return m_productName;
}

//------------------------------------------------------------------------------
const QString &FakeDefinitionParser::provider() const
{
    return m_provider;
}

//------------------------------------------------------------------------------
const QString &FakeDefinitionParser::version() const
{
    return m_version;
}

//------------------------------------------------------------------------------
