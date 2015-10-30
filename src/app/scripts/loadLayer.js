function loadLayer(workspacePath, name) {
    console.log("Loading " + name + "...");

    var workspace = shapeFileWorkspaceFactory.openFromFile(workspacePath);
    var featureClass = workspace.openFeatureClass(name);

    var featureLayer = serviceLocator.build("FeatureLayer");
    featureLayer.featureClass = featureClass;

    return featureLayer;
}

var doc = documentController.document;
var map = doc.map;

map.addLayer(loadLayer("./data", "natural"))
map.addLayer(loadLayer("./data", "landuse"))
map.addLayer(loadLayer("./data", "buildings"))
map.addLayer(loadLayer("./data", "waterways"))
map.addLayer(loadLayer("./data", "railways"))

map.refresh();
