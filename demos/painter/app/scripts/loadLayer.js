function loadLayer(workspacePath, name) {
    print("Loading " + name + "...");

    var factory = serviceLocator.build("IShapeFileWorkspaceFactory", true);
    var workspace = factory.openFromFile(workspacePath);
    var featureClass = workspace.openFeatureClass(name);

    var featureLayer = serviceLocator.build("FeatureLayer");
    featureLayer.featureClass = featureClass;

    var scriptService = serviceLocator.locate("IScriptingService");
    var docController = serviceLocator.locate("IPainterDocumentController");
    var doc = docController.document;
    var map = doc.map;
    map.addLayer(featureLayer);
    map.refresh();
}

loadLayer("./data", "waterways");
loadLayer("./data", "railways");
loadLayer("./data", "natural");
loadLayer("./data", "landuse");
loadLayer("./data", "buildings");
