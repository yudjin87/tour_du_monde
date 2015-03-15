function loadLayer(workspacePath, name) {
    print("Loading " + name + "...");

    var factory = serviceLocator.build("IShapeFileWorkspaceFactory", true);
    var workspace = factory.openFromFile(workspacePath);
    var featureClass = workspace.openFeatureClass(name);

    var featureLayer = serviceLocator.build("FeatureLayer");
    featureLayer.featureClass = featureClass;

    return featureLayer;
}

var scriptService = serviceLocator.locate("IScriptingService");
var docController = serviceLocator.locate("IPainterDocumentController");
var doc = docController.document;
var map = doc.map;

map.addLayer(loadLayer("./data", "landuse"))
map.addLayer(loadLayer("./data", "natural"))
map.addLayer(loadLayer("./data", "buildings"))
map.addLayer(loadLayer("./data", "waterways"))
map.addLayer(loadLayer("./data", "railways"))

map.refresh();
