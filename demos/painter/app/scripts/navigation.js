var display = serviceLocator.locate("IDisplay");
var transform = display.transformation;

// Zoom to all:
transform.visibleBounds = transform.bounds
wait(250);

display.panStart(new QPoint(50, 50));
for (x = 0, y = 0; x < 150; x += 2, y += 2) {
    display.panMoveTo(new QPoint(50 + x, 50 + y));
    wait(5);	
}   
display.panStop();

wait(150);
transform.scale = transform.scale * 2
wait(150);

display.panStart(new QPoint(50, 50));
for (x = 0, y = 0; x > -150; x -= 2, y -= 2) {
    display.panMoveTo(new QPoint(50 + x, 50 + y));
    wait(5);	
}   
display.panStop();
