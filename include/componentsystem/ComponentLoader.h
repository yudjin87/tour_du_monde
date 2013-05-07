#ifndef COMPONENTLOADER_H
#define COMPONENTLOADER_H

#include "componentsystem/IComponentLoader.h"

#include <QtCore/QObject>

class QLibrary;

/*!
 * @brief
 *   The default implementation of the IComponentLoader class.
 * @details
 *   It is very similiar with QPluginLoader, but with few differences: ComponentLoader
 *   returns IComponent instead of QObject; ComponentLoader can be used with if your application
 *   is statically linked against Qt; ComponentLoader takes ownership for the loaded component
 *   instance; Load hints are set to QLibrary::ResolveAllSymbolsHint and
 *   QLibrary::ExportExternalSymbolsHinthints by default to enable RTTI cross the library bounds
 *   (used in IServiceLocator).
 *
 *   ComponentLoader provides access to a IComponent, stored in a shared library (a DLL) and
 *   offers these benefits over shared libraries accessed using QLibrary.
 *
 *   ComponentLoader provides direct access to a component object (instance()), instead of forcing
 *   you to resolve a C function manually.
 *
 *   An instance of a ComponentLoader object operates on a single shared library file, which we call
 *   a component. It provides access to the functionality in the component in a platform-independent
 *   way. To specify which component to load, either pass a file name in the constructor or set it
 *   with setFileName().
 *
 *   The most important functions are load() to dynamically load the component file, isLoaded() to check
 *   whether loading was successful, and instance() to access the root in the component. The instance()
 *   function implicitly tries to load the component if it has not been loaded yet.
 *
 * @note: ComponentLoader takes ownership for the loaded component instance, and it will be until
 *   ComponentLoader has been destroyed or deleteInstance() is called.
 */
class COMP_API ComponentLoader : public QObject, public IComponentLoader
{
    Q_OBJECT
public:
    ComponentLoader(QObject *parent = nullptr);
    ComponentLoader(const QString & fileName, QObject *parent = nullptr);
    /*!
     * @details
     *   Destroys the ComponentLoader object.
     *
     *   unload() will be called explicitly, the component will be destroyed (if any).
     */
    ~ComponentLoader();

    /*!
     * @details
     *   Returns a text string with the description of the last error that occurred.
     */
    QString errorString() const;

    /*!
     * @details
     *   Deletes the component and returns true if the component was deleted; otherwise returns false.
     *
     *   This happens automatically on ComponentLoader destructor, so you shouldn't normally need to call this function.
     *
     *   If other instances of ComponentLoader are using the same component, the call will fail, and unloading
     *   will only happen when every instance has called unload().
     *
     *   Don't try to delete the component object. Instead rely on that deleteInstance() will automatically delete it.
     *
     * @sa instance().
     */
    bool deleteInstance();

    /*!
     * @details
     *   Returns the file name of the component.
     *
     *   By default, this property contains an empty string.
     */
    QString fileName() const;

    /*!
     * @details
     *   Returns the root object of the component. The component is loaded if necessary. The
     *   function returns nullptr if the component could not be loaded or if the component
     *   could not be instantiated.
     *
     *   If the component object was destroyed (unload()), calling this function creates a new instance.
     *
     *   The root component, returned by this function, is deleted when the IComponentLoader is destroyed.
     *   If you want to manage component lifetime your-self, you should call unload().
     *
     * @sa load().
     */
    IComponent *instance();

    /*!
     * @details
     *   Returns true if the component is loaded; otherwise returns false.
     */
    bool isLoaded() const;

    /*!
     * @details
     *   Loads the component and returns true if the component was loaded successfully; otherwise returns
     *   false. Since instance() always calls this function before resolving any symbols it is not necessary
     *   to call it explicitly. In some situations you might want the component loaded in advance, in which
     *   case you would use this function.
     *
     * @sa deleteInstance().
     */
    bool load();

    /*!
     * @details
     *   Gets the give the load() function some hints on how it should behave. By default,
     *   QLibrary::ResolveAllSymbolsHint and QLibrary::ExportExternalSymbolsHinthints are set to enable RTTI cross
     *   the library bounds.
     *
     *   See the documentation of QLibrary::loadHints() for a complete description of how this property works.
     */
    QLibrary::LoadHints	loadHints() const;

    /*!
     * @details
     *   Sets the file name of loaded component library.
     *
     *   To be loadable, the file's suffix must be a valid suffix for a loadable library in accordance with the
     *   platform, e.g. @a .so on Unix, @a .dylib on Mac OS X, and @a .dll on Windows. The suffix can be
     *   verified with QLibrary::isLibrary().
     *
     *   If the file name does not exist, it will not be set. This property will then contain an empty string.
     *
     * @sa fileName().
     */
    void setFileName(const QString &fileName);

    /*!
     * @details
     *   Sets the file name of loaded component library.
     *
     * @sa loadHints().
     */
    void setLoadHints(QLibrary::LoadHints loadHints);

    /*!
     * @details
     *   Unloads the component and returns true if the component could be unloaded; otherwise returns false.
     *
     *   This happens automatically on IComponentLoader destructor, so you shouldn't normally need to call this function.
     *
     *   If other instances of IComponentLoader are using the same component, the call will fail, and unloading
     *   will only happen when every instance has called unload().
     *
     *   Don't try to delete the component object. Instead rely on that unload() will automatically delete it when needed.
     *
     * @sa instance(), deleteInstance() and load().
     */
    bool unload();

private:
    /*!
     * @details
     *   Defines the function loaded from the specified library, that should create IComponent instance
     *   and return pointer to it.
     */
    typedef void *(*createComponentFunc)();

    /*!
     * @details
     *   Defines the function loaded from the specified library, that should delete IComponent instance
     *   by the specified pointer to it.
     */
    typedef void (*releaseComponentFunc)(void *);

protected:
    IComponent *m_instance;

private:
    static const QString m_createFuncName;
    static const QString m_releaseFuncName;
    QString m_fileName;
    QString m_errorString;
    bool m_loaded;
    QLibrary::LoadHints m_loadHits;
    createComponentFunc m_createFunc;
    releaseComponentFunc m_releaseFunc;
    QLibrary *m_library;
};

#endif // COMPONENTLOADER_H
