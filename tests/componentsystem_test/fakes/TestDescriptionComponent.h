#ifndef TESTCONFIGUREDCOMPONENT_H
#define TESTCONFIGUREDCOMPONENT_H

#include "TestComponentDefinition.h"

#include <componentsystem/BaseComponent.h>

//------------------------------------------------------------------------------
class TestDescriptionComponent : public BaseComponent
{
    Q_OBJECT
public:
    TestDescriptionComponent();
    TestDescriptionComponent(const QString &name);

protected:
    bool _onStartup(QObject *ip_initData);
    IComponentDefinition *definition() const;

signals:
    void whenStarted(QString name);

public:
    TestComponentDefinition m_definition;
};

//------------------------------------------------------------------------------
#endif // TESTCONFIGUREDCOMPONENT_H
