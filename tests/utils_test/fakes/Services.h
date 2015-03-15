#ifndef SERVICE1_H
#define SERVICE1_H

#include "IService.h"

class Service1 : public IService
{
    Q_OBJECT
public:
    Service1(int id = 0);
    ~Service1();

    static int instancesCount;
};


#endif // SERVICE1_H
