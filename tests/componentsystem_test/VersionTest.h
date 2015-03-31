#pragma once
#include <QtCore/QObject>

class VersionTest : public QObject
{
    Q_OBJECT
public:
    explicit VersionTest(QObject *parent = 0);

private slots:
    void parseString_shouldReturnTrueFor4Numbers();
    void parseString_shouldReturnTrueFor3Numbers();
    void parseString_shouldReturnTrueFor2Numbers();
    void parseString_shouldReturnFalseFor1Number();

    void fromString_shouldReturnVersion();
    void fromString_shouldReturnNullIfFailed();
};

