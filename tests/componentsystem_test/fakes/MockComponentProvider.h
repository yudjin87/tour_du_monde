#pragma once
#include <carousel/componentsystem/ComponentProvider.h>

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

