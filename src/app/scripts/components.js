var cm = serviceLocator.locate("IComponentManager");
var startedComponents = cm.startedComponents;
var componentsCount = startedComponents.length;
print("Started components: " + componentsCount);
for (var i = 0; i < startedComponents.length; ++i) {
    var comp = startedComponents[i];
    var def = comp.definition;
    print(def.shortComponentName);
}

wait(2000);

var installCmd = serviceLocator.build("InstallComponentsCommand");

// All dependencies for this components also will be installed
installCmd.addDefinitionPath("externalSource/org.carousel.demos.CartoUI.definition");
installCmd.addDefinitionPath("externalSource/org.carousel.demos.NewComponentsDialog.definition");
installCmd.addDefinitionPath("externalSource/org.carousel.demos.NavigationOperations.definition");

installCmd.pushToStack();

startedComponents = cm.startedComponents;
print("\nComponents after installation: " + startedComponents.length);
for (var i = componentsCount; i < startedComponents.length; ++i) {
    var comp = startedComponents[i];
    var def = comp.definition;
    print(def.shortComponentName);
}
