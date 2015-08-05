var mw = serviceLocator.locate("QMainWindow");
var oldPosition = mw.pos;
mw.focus = true;

// Corner positioning:
mw.pos = new QPoint(50, 50);
wait(250);

// Lets carousel begin!
for (x = 0; x < 250; x+= 2) {
    mw.pos = new QPoint(50 + x, mw.pos.y);
    wait(10);	
}   

wait(250);

for (y = 0; y < 250; y+= 2) {
    mw.pos = new QPoint(mw.pos.x, 50 + y);
    wait(10);	
}   

wait(350);

mw.pos = oldPosition;

