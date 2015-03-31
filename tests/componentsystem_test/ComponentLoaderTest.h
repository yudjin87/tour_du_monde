#pragma once
#include <QtCore/QObject>

class ComponentLoaderTest : public QObject
{
    Q_OBJECT
public:
    explicit ComponentLoaderTest(QObject *parent = 0);

private slots:
    void shouldSetupFile();
    void shouldNotSetupFileNameIfFileDoesNotExist();

    void instanceShouldCallLoad();
    void instanceShouldNotCallLoadIfAlreadyDid();
    void instanceShouldReturnIComponentPointer();

    void loadShouldLoadAndCreateComponent();
    void loadShouldReturnTrue();
    void loadShouldNotCreateComponentIfAlreadyDid();
    void loadShouldReturnTrueIfLoadedSecondTime();

    void loadShouldReturnFalseIfFileNameDoesNotSet();
    void loadShouldReturnFalseIfCreateFunctionDoesNotExistInLib();
    void loadShouldReturnFalseIfReleaseFunctionDoesNotExistInLib();
    void loadShouldSetupIsLoadFlag();

    void deleteInstanceShouldDeleteComponent();
    void unloadShouldReturnFalseIfWasNotLoad();
    void unloadShouldSetupIsLoadFlag();
    void unloadShouldReturnTrueIfCan();

    void destructorShouldUnloadComponent();

    void shouldNotSetFileUntilUnload();

};

