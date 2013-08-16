#ifndef DIRECTORYCOMPONENTPROVIDERTEST_H
#define DIRECTORYCOMPONENTPROVIDERTEST_H

#include <QtCore/QObject>

class DirectoryComponentProviderTest : public QObject
{
    Q_OBJECT
public:
    explicit DirectoryComponentProviderTest(QObject *parent = 0);
    
private Q_SLOTS:
    void shouldNotSetupWrongDirectoryPath();
    void shouldSetupPathAccordingToTheApplicationDir();
    void shouldCorrectlySetupAbsolutePath();

    void initialize_shouldReturnTrue();
    void initialize_shouldCallUpdate();
    void initialize_shouldReturnFalseIfPathIsEmpty();

    void update_shouldCallReadOnParserForEachDefinition();
    void update_shouldReturnTwoComponents();
    void update_shouldPopulateTwoComponents();
    void update_shouldPopulateOnlyWithNewComponents();
    void update_shouldReturnOnlyNewComponents();
    void update_shouldNotPopulateComponentIfItsInitializationFault();

private:
    const QString definitionsLocation;
};

#endif // DIRECTORYCOMPONENTPROVIDERTEST_H
