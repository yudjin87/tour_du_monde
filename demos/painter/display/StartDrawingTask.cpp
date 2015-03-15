#include <display/StartDrawingTask.h>
#include <display/MultithreadDisplay.h>
#include <carousel/logging/LoggerFacade.h>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("StartDrawingTask");
}

StartDrawingTask::StartDrawingTask(MultithreadDisplay *display, QObject *parent)
    : QObject(parent)
    , IDrawingTask()
    , m_display(display)
{
}

void StartDrawingTask::draw(IDisplay &)
{
    Log.d("Calling create pixmap");
    m_display->callCreatePixmap();
}

