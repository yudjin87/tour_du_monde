#ifndef MOCKCOMPONENT_H
#define MOCKCOMPONENT_H

#include <componentsystem/BaseComponent.h>

class MockComponent : public BaseComponent
{
   Q_OBJECT
public:
    explicit MockComponent(const QString &i_name = "MockComponent", bool isBuiltIn = false);

    ~MockComponent();

    QObject *data() const;

    void setRegistrator(QList<MockComponent *> *ip_registrator);

    void loadAvailability();

protected:
    bool _onStartup(QObject *ip_initData);
    void _onShutdown();

signals:
    void whenStarted(const QString &i_name);
    void whenShutdown(const QString &i_name);

public:
    QObject *mp_initData;
    bool m_returnValue;
    QList<MockComponent *> *mp_registrator;
};

#endif // MOCKCOMPONENT_H
