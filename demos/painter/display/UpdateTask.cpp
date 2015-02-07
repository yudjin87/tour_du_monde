#include <display/UpdateTask.h>
#include <display/MultithreadDisplay.h>

#include <carousel/logging/LoggerFacade.h>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("UpdateTask");
}

//------------------------------------------------------------------------------
UpdateTask::UpdateTask(MultithreadDisplay* display, QObject *parent)
    : QObject(parent)
    , m_display(display)
{
    //QObject::connect(this, SIGNAL(callUpdate()), widget, SLOT(update()));
}

//------------------------------------------------------------------------------
void UpdateTask::draw(IDisplay &)
{
    Log.d("Emit update needed");
    //emit callUpdate();
    m_display->callCopyAndUpdate();
}

//------------------------------------------------------------------------------
