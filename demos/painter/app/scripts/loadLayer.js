var factory = serviceLocator.build("IShapeFileWorkspaceFactory", true);
var workspace = factory.openFromFile("./data");
var featureClass = workspace.openFeatureClass("waterways");
//var featureClass = workspace.openFeatureClass("buildings");
var featureLayer = serviceLocator.build("FeatureLayer");
featureLayer.featureClass = featureClass;

var scriptService = serviceLocator.locate("IScriptingService");
var docController = serviceLocator.locate("IPainterDocumentController");
var doc = docController.document;
var map = doc.map;


map.addLayer(featureLayer); 
map.refresh();