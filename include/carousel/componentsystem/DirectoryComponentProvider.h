/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#ifndef DIRECTORYCOMPONENTPROVIDER_H
#define DIRECTORYCOMPONENTPROVIDER_H

#include <carousel/componentsystem/IDirectoryComponentProvider.h>

#include <QtCore/QStringList>

class ComponentProvider;
class FileComponentProvider;

/*!
 * @brief
 *   The DirectoryComponentProvider uses to load custom components from the specified
 *   library path.
 * @details
 *   DirectoryComponentProvider does not instantiate components from the shared libraries,
 *   it uses FileComponentProvider instead.
 *
 *   To export your component in shared library you have to define it:
 *
 * @code
 *   #include <carousel/componentsystem/BaseComponent.h>
 *
 *   class MyComponent : public BaseComponent
 *   {
 *       Q_OBJECT
 *   public:
 *       MyComponent(QObject *parent = nullptr);
 *   protected:
 *       bool onStartup(IServiceLocator *serviceLocator);
 *   private:
 *       IServiceLocator *m_serviceLocator;
 *   };
 * @endcode
 *
 *   and to export it in @a MyComponent.cpp file using macros EXPORT_COMPONENT:
 *
 * @code
 *   #include "MyComponent.h"
 *   #include <carousel/componentsystem/ComponentExport.h>
 *
 *   MyComponent::MyComponent(QObject *parent)
 *      : BaseComponent("MyComponent", parent)
 *      , m_serviceLocator(nullptr)
 *   {
 *   }
 *
 *   bool MyComponent::onStartup(IServiceLocator *serviceLocator)
 *   {
 *       m_serviceLocator = serviceLocator;
 *       return (m_serviceLocator != nullptr);
 *   }
 *
 *   EXPORT_COMPONENT(MyComponent)
 *
 * @endcode
 *
 *   You also should provide definition for the component:
 *
 * @code
 *   <component name="MyComponent">
 *       <productName>My super product</productName>
 *       <description>Ultra feature</description>
 *       <location>./MyComponent</location>
 *       <parents>
 *           <parentComponent name="ComponentA"/>
 *           <parentComponent name="ComponentC"/>
 *           <parentComponent name="ComponentB"/>
 *       </parents>
 *   </component>
 * @endcode
 *
 *   XmlDefinitionParser will be used to read this meta-information, by which ProxyComponent
 *   should load the real component.
 *
 *   Then you should override BootloaderBase::createComponentProvider() to return
 *   DirectoryComponentProvider pointer or BootloaderBase::configureComponentProvider()
 *   to specify path for the library:
 * @code
 *   IComponentProvider *MyBootloader::createComponentProvider()
 *   {
 *       return new DirectoryComponentProvider("plugins/");
 *   }
 *   void MyBootloader::configureComponentProvider()
 *   {
 *       static_cast<DirectoryComponentProvider *>(m_componentProvider)->setPath("plugins/");
 *   }
 * @endcode
 *   During boot loading sequence DirectoryComponentProvider will find all component
 *   definitions in the @a plugins/ directory and instantiate proxy components for them,
 *   which creates real components by demand.
 * @note it does not take ownership neither for proxy components that will be @a discovered in
 *   libraries nor for components registered by registerComponent().
 */
class COMP_API DirectoryComponentProvider : public IDirectoryComponentProvider
{
    Q_OBJECT
public:
    explicit DirectoryComponentProvider(QObject *parent = nullptr);
    DirectoryComponentProvider(const QString &path, QObject *parent = nullptr);
    DirectoryComponentProvider(const QString &path, const QString &definitionExtension, QObject *parent = nullptr);
    ~DirectoryComponentProvider();

public:
    /*!
     * @details
     *   Gets the all components registered at the provider.
     */
    QList<IComponent *> components() const override;

    /*!
     * @details
     *   Initializes the provider, which may load and validate the components.
     *   Returns @a true, if initialization was succesful; otherwise, returns @a false.
     */
    bool initialize() override;

    /*!
     * @details
     *   Returns @a true, if provider alreadyinitialzied; otherwise, returns @a false.
     */
    bool isInitialized() const override;

    /*!
     * @details
     *   Registers the specified component at the provider.
     *   Usually, you can register the same components or components with same names using
     *   existing providers, but when components will be pushed to the IComponentManager
     *   from the providers - the last one doesn't allow duplicating components.
     *   @a Null pointers will be skipped.
     */
    void registerComponent(IComponent *component) override;

   /*!
    * @details
    *   Sets the root directory path containing component definitions.
    */
   void setPath(const QString &path) override;

   /*!
    * @details
    *   Sets the definition files extension "*.definition" is by default.
    */
   void setExtension(const QString &definitionExtension) override;

   /*!
    * @details
    *   Sets the filters for searching files in the specified path.
    *
    *   QDir::NoDotAndDotDot | QDir::Readable are by default.
    */
   void setFilters(QDir::Filters filters) override;

   /*!
    * @details
    *   Sets the flag for iterating over files in the specified path.
    *
    *   QDirIterator::Subdirectories is by default.
    */
   void setFlags(QDirIterator::IteratorFlags flags) override;

   /*!
    * @details
    *   Gets the directory path containing component definitions.
    */
   const QString &path() const override;

   /*!
    * @details
    *   Gets the definition files extension.
    */
   const QString &extension() const override;

   /*!
    * @details
    *   Gets the filters for searching files in the specified path.
    */
   QDir::Filters filters() const override;

   /*!
    * @details
    *   Gets the flag for iterating over files in the specified path.
    */
   QDirIterator::IteratorFlags flags() const override;

   /*!
    * @details
    *   Loads definitions from the specified root path and tries to create
    *   proxy the components from them if they have not created yet.
    *
    *   Returns list of the new discovered components.
    */
    QList<IComponent *> update() override;

protected:
    /*!
     * @details
     *   Initializes the provider and calls update() to load components.
     *
     * @return @a false, if path is empty.
     */
    bool onInitialize();

    /*!
     * @details
     *   Creates a file provider to instantiate component from the definition.
     *
     *   Note that it takes ownership for the provider.
     */
    virtual FileComponentProvider *createFileComponentProvider(const QString &definitionPath);

private:
    static QString getCheckedDirectoryPath(const QString &path);

private:
    QString m_path;
    QString m_definitionExtension;
    QDirIterator::IteratorFlags m_flags;
    QDir::Filters m_filters;
    QStringList m_processedFiles;
    bool m_alreadyInit;
    ComponentProvider *m_provider;
};

#endif // DIRECTORYCOMPONENTPROVIDER_H
