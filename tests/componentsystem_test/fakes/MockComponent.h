#ifndef MOCKCOMPONENT_H
#define MOCKCOMPONENT_H

#include <componentsystem/BaseComponent.h>

class MockComponent : public BaseComponent
{
   Q_OBJECT
public:
    explicit MockComponent(const QString &name = "MockComponent", bool isBuiltIn = false);

    ~MockComponent();

    QObject *data() const;

    void setRegistrator(QList<MockComponent *> *registrator);

protected:
    bool _onStartup(QObject *initData);
    void _onShutdown();

signals:
    void whenStarted(const QString &name);
    void whenShutdown(const QString &name);

public:
    QObject *m_initData;
    bool m_returnValue;
    QList<MockComponent *> *m_registrator;
};

#endif // MOCKCOMPONENT_H
