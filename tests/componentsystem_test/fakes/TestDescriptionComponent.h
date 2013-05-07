#ifndef TESTCONFIGUREDCOMPONENT_H
#define TESTCONFIGUREDCOMPONENT_H

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/BaseComponent.h>

//------------------------------------------------------------------------------
class TestDescriptionComponent : public BaseComponent
{
    Q_OBJECT
public:
    TestDescriptionComponent();
    TestDescriptionComponent(const QString &name);

protected:
    bool _onStartup(QObject *initData);
    ComponentDefinition *definition() const;

signals:
    void whenStarted(QString name);

public:
    ComponentDefinition m_definition;
    bool startUpResult;
};

//------------------------------------------------------------------------------
#endif // TESTCONFIGUREDCOMPONENT_H
