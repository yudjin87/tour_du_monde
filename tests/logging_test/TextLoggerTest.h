#pragma once
#include <QtCore/QObject>

class TextLoggerTest : public QObject
{
    Q_OBJECT
public:
    TextLoggerTest();

private Q_SLOTS:
    void writeToStream();
};

