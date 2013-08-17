var cm = serviceLocator.locate("IComponentManager");
var startedComponents = cm.startedComponents;
for (var i = 0; i < startedComponents.length; ++i) {
    var comp = startedComponents[i];
    var def = comp.definition;	
    print(def);
    print(def.shortComponentName);    	
}
print(startedComponents.length);    
