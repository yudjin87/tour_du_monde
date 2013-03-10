#ifndef TEXTLOGGERTEST_H
#define TEXTLOGGERTEST_H

#include <QtCore/QObject>

class TextLoggerTest : public QObject
{
    Q_OBJECT
public:
    TextLoggerTest();

private Q_SLOTS:
    void writeToStream_data();
    void writeToStream();
};

#endif // TEXTLOGGERTEST_H
