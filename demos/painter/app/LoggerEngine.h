#ifndef LOGGERENGINE_H
#define LOGGERENGINE_H

#include <carousel/logging/ILoggerEngine.h>
#include <carousel/logging/ILoggerEngineCreator.h>

class LoggerEngine : public ILoggerEngine
{
public:
    LoggerEngine();
    ~LoggerEngine();

    void d(const QString &message) override;
    void e(const QString &message) override;
    void f(const QString &message) override;
    void i(const QString &message) override;
    void t(const QString &message) override;
    void w(const QString &message) override;
};

class LoggerEngineCreator : public ILoggerEngineCreator
{
public:
    LoggerEngineCreator();

    ILoggerEngine *getLogger(const QString &name);
};

#endif // LOGGERENGINE_H
