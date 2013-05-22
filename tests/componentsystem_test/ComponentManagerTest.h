#ifndef COMPONENTMANAGERTEST_H
#define COMPONENTMANAGERTEST_H

#include <utils/ServiceLocator.h>

#include <QtCore/QObject>

class ComponentManagerTest : public QObject
{
    Q_OBJECT
public:
    ComponentManagerTest();

private slots:
    void addComponent_shouldAddComponentToTheStoppedComponents();
    void addComponent_shouldSetCheckedFlagToFalse();

    void check_shouldCallResolving();
    void check_shouldSetCheckedFlag();
    void check_shouldNotResolveComponentsAgainIfCheckedFlagIsTrue();

    // orphan, missing components during startup
    void check_shouldFillMissingComponents();
    void check_shouldFillOrphanComponents();

    // startup activities
    void startup_shouldShouldNotCallIfAlreadyDid();
    void startup_shouldStartComponents();
    void startup_shouldNotStartDisabledComponent();
    void startupAllComponents_shouldCallCheck(); // which calls resolving
    void startupAllComponents_shouldRemoveThemFromStoppedList();
    void startupAllComponents_shouldAddThemToTheStartedList();
    void startupAllComponents_shouldEmit();
    void startupAllComponents_shouldStartComponents();
    void startupAllComponents_shouldPassInitDataToComponent();
    void startupAllComponents_shouldEnableDisabledComponent();
    void startupAllComponents_shouldHandleNullComponent();
    void startupAllComponents_shouldNotStartChildComponentsIfParentCouldNotStart();
    void startupAllComponents_shouldStartOrphanComponentIfParentAppeared();
    void startupComponents_shouldStartOrphanComponentsWhenParentsAppeared();
    void startupComponents_shouldNotStartOrphanComponentsWhenOtherParentsAppeared();
    void startupComponents_shouldReturnJustStartedComponents();

    void shutdownAllComponents_shouldEmit();
    void shutdownAllComponents_shouldEmitAboutSignal();
    void shutdownAllComponents_shouldRemoveThemFromStartedList();
    void shutdownAllComponents_shouldAddThemToTheStoppedList();
    void shutdownAllComponents_shouldNotShutdownUnexistingComponent();
    void shutdownAllComponents_shouldNotShutdownBuiltInComponent();
    void shutdownAllComponents_shouldDisableComponent();
    void shutdownComponents_shouldReturnJustShutDownComponents();
    void shutdown_shouldShutdownAllComponents();
    void shutdown_shouldShutdownBuiltInComponents();
    void shutdown_shouldNotDisableComponent();
    void shutdown_shouldEmit();

    // Integration tests:
    void startupComponent_shouldPassRightComponentsInRightOrder();
    void startupAllComponents_shouldPassComponentsInRightOrder();
    void startupAllComponents_shouldPassComponentsInRightOrder_ComplexDependencies();
    void shutdownComponent_shouldPassComponentsInReverseOrder();
    void shutdownAllComponents_shouldPassComponentsInRightOrder();

private:
    ServiceLocator m_locator;
};

#endif // COMPONENTMANAGERTEST_H


