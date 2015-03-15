#ifndef TESTCONFIGUREDCOMPONENT_H
#define TESTCONFIGUREDCOMPONENT_H

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/BaseComponent.h>

class TestDescriptionComponent : public BaseComponent
{
    Q_OBJECT
public:
    TestDescriptionComponent();
    TestDescriptionComponent(const QString &name);

protected:
    bool onStartup(IServiceLocator *serviceLocator);
    ComponentDefinition *definition() const;

signals:
    void whenStarted(QString name);

public:
    ComponentDefinition m_definition;
    bool startUpResult;
};

#endif // TESTCONFIGUREDCOMPONENT_H
