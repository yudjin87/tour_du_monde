var scriptService = serviceLocator.locate("IScriptingService");
var docController = serviceLocator.locate("IPainterDocumentController");
var doc = docController.document;
var map = doc.map;
var layer = map.layers[0];
var render = layer.renderer;
var symbol = render.symbol;
var color = symbol.color;
symbol.setColor(255, 0, 0);
map.refresh();

	