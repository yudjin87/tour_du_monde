#ifndef FAKECOMPONENTLOADER_H
#define FAKECOMPONENTLOADER_H

#include <carousel/componentsystem/IComponentLoader.h>

#include <QtCore/QObject>

class MockComponent;

class FakeComponentLoader : public QObject, public IComponentLoader
{
    Q_OBJECT
public:
    FakeComponentLoader();
    FakeComponentLoader(IComponent *component);
    ~FakeComponentLoader();

    QString errorString() const;
    QString fileName() const;
    IComponent *instance();
    bool isLoaded() const;
    bool load();
    QLibrary::LoadHints	loadHints() const;
    void setFileName(const QString &fileName);
    void setLoadHints(QLibrary::LoadHints loadHints);
    bool deleteInstance();

    bool unload() { return false; }


signals:
    void unloaded();

public:
    int instanceCalled;
    int loadCalled;
    int unloadCalled;
    int setFileNameCalled;
    bool loadResult;
    bool unloadResult;
    QString passedFileName;
    IComponent *mockComponent;
};
#endif // FAKECOMPONENTLOADER_H
