#include "LoggerEngine.h"

LoggerEngine::LoggerEngine()
{
}

LoggerEngine::~LoggerEngine()
{
}

void LoggerEngine::d(const QString &message)
{
    Q_UNUSED(message)
}

void LoggerEngine::e(const QString &message)
{
    Q_UNUSED(message)
}

void LoggerEngine::f(const QString &message)
{
    Q_UNUSED(message)
}

void LoggerEngine::i(const QString &message)
{
    Q_UNUSED(message)
}

void LoggerEngine::t(const QString &message)
{
    Q_UNUSED(message)
}

void LoggerEngine::w(const QString &message)
{
    Q_UNUSED(message)
}

LoggerEngineCreator::LoggerEngineCreator()
{

}

ILoggerEngine *LoggerEngineCreator::getLogger(const QString &name)
{
    Q_UNUSED(name)
    return new LoggerEngine();
}
