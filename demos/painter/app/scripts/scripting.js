var scriptService = serviceLocator.locate("IScriptingService");
var scriptCollection = scriptService.scripts;

/*
var newScriptUnit = scriptCollection.create();
newScriptUnit.scriptText = "var scriptService = serviceLocator.locate(\"IScriptingService\");\n" 
newScriptUnit.scriptText += "var scriptCollection = scriptService.scripts;\n"
newScriptUnit.scriptText += "var scriptConsole = scriptService.console;\n" 
newScriptUnit.scriptText += "\n" 
newScriptUnit.scriptText += "print(\"Hello, new world!\");" 
newScriptUnit.printed.connect(print);

newScriptUnit.run();
*/

// Console
var scriptConsole = scriptService.console;
scriptConsole.execCommand("print(\"Hello, new world!\")");
