#ifndef SERVICES_H
#define SERVICES_H

#include <QtCore/QObject>

//------------------------------------------------------------------------------
class IService
{
public:
    IService(int i_id = 0)
        : m_id(i_id)
    {}

    virtual ~IService() {}

public:
    virtual int id() {return m_id;}

protected:
    int m_id;
};

//------------------------------------------------------------------------------
class Service1 : public QObject, public IService
{
public:
    Service1(int i_id = 0)
        : IService(i_id)
    {
        ++instancesCount;
    }

    ~Service1()
    {
        --instancesCount;
    }


    static int instancesCount;
};

//------------------------------------------------------------------------------

#endif // SERVICES_H
