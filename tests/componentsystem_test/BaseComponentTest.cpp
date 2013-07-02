#include "BaseComponentTest.h"

#include "fakes/ComponentWithExtensions.h"
#include "fakes/MockComponent.h"

#include <carousel/componentsystem/BaseComponent.h>
#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/utils/ServiceLocator.h>

#include <QtTest/QtTest>
#include <QtCore/QSettings>
#include <QtTest/QSignalSpy>

class SimpleComponent : public BaseComponent
{
public:
    SimpleComponent(const QString &name = "MockComponent")
        : BaseComponent(name)
    {
    }

    void setVersion(int major_version, int minor_version, int build_version, int revision_version)
    {
        BaseComponent::setVersion(major_version, minor_version, build_version, revision_version);
    }
};

//------------------------------------------------------------------------------
BaseComponentTest::BaseComponentTest(QObject *parent)
    : QObject(parent)
{
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, ".");
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldSetAvailabilityEnabledByDefault()
{
    SimpleComponent component("");
    QCOMPARE(component.availability(), IComponent::Enabled);
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldSetLoadedAvailability()
{
    QSettings settings;
    settings.setValue(QString("components_availability/%1").arg("Comp1"), static_cast<int>(IComponent::Disabled));
    settings.sync();

    SimpleComponent component("Comp1");

    QCOMPARE(component.availability(), IComponent::Disabled);

    settings.clear();
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldEmitWhenAvailabilitySet()
{
    SimpleComponent component("Comp1");
    QSignalSpy spy(&component, SIGNAL(availabilityChanged(IComponent::Availability)));

    component.setAvailability(IComponent::Disabled);

    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldSaveSetAvailabilityInDestructor()
{
    {
        SimpleComponent component("Comp1");
        component.setAvailability(IComponent::Disabled);
    }

    QSettings settings;
    QVariant value = settings.value(QString("components_availability/Comp1"));
    QVERIFY(value.isValid());
    QCOMPARE(static_cast<IComponent::Availability>(value.toInt()), IComponent::Disabled);

    settings.clear();
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldNotSetAvailabilityIfDidNotLoad()
{
    QSettings settings;
    settings.setValue("components_availability/empty", 0);
    settings.sync();

    SimpleComponent component("Comp1");

    QCOMPARE(component.availability(), IComponent::Enabled);
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldReturnResultOfProtectedMethodOnFirstSuccessfulStartup()
{
    SimpleComponent mockComponent;
    QVERIFY(mockComponent.startup(nullptr));

    MockComponent mockComponent2; mockComponent2.m_returnValue = false;
    QVERIFY(!mockComponent2.startup(nullptr));
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldAssignResultOfProtectedMethodToTheStartedFlag()
{
    SimpleComponent mockComponent;
    mockComponent.startup(nullptr);
    QVERIFY(mockComponent.started());

    MockComponent mockComponent2; mockComponent2.m_returnValue = false;
    mockComponent2.startup(nullptr);
    QVERIFY(!mockComponent2.started());
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldNotStartupIfAlreadyStarted()
{
    MockComponent mockComponent;
    QSignalSpy spy(&mockComponent, SIGNAL(whenStarted(const QString &)));

    mockComponent.startup(nullptr);
    mockComponent.startup(nullptr); // should not be emitted the second time

    // make sure the signal was emitted exactly one time
    QCOMPARE(spy.count(), 1);
    QCOMPARE(mockComponent.started(), true);
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldShutdownIfAlreadyStoped()
{
    MockComponent mockComponent;
    QSignalSpy spy(&mockComponent, SIGNAL(whenShutdown(const QString &)));

    ServiceLocator locator;
    mockComponent.shutdown(&locator);

    // make sure the signal wasn't emitted
    QCOMPARE(spy.count(), 0);
    QCOMPARE(mockComponent.started(), false);
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldReturnRegisteredInDerivedClassesExtensions()
{
    ComponentWithExtensions componentWithExtensions;

    IComponentExtension1 *extension1 = componentWithExtensions.extension<IComponentExtension1>();
    IComponentExtension2 *extension2 = componentWithExtensions.extension<IComponentExtension2>();

    QCOMPARE(extension2, componentWithExtensions.m_extension2);
    QCOMPARE(extension1, componentWithExtensions.m_extension1);
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldReturnNullWhenUnregisteredExtensionIsQueried()
{
    ComponentWithExtensions componentWithExtensions;

    BaseComponentTest *unregisteredExtension = componentWithExtensions.extension<BaseComponentTest>();

    QVERIFY(unregisteredExtension == nullptr);
}

//------------------------------------------------------------------------------
void BaseComponentTest::isCompatible_shouldReturnTrue()
{
    SimpleComponent one; one.setVersion(1, 0, 0, 0);
    SimpleComponent other; other.setVersion(1, 0, 0, 0);

    QVERIFY(one.isCompatible(&other));
    QVERIFY(other.isCompatible(&one));
}

//------------------------------------------------------------------------------
