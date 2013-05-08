#ifndef MOCKCOMPONENTPROVIDER_H
#define MOCKCOMPONENTPROVIDER_H

#include <componentsystem/ComponentProvider.h>

class MockComponentProvider : public ComponentProvider
{
    Q_OBJECT
public:
    MockComponentProvider();

    bool hasBeenInit() const;

protected:
    virtual bool onInitialize();

private:
    bool m_hasBeenInit;

};

#endif // MOCKCOMPONENTPROVIDER_H
