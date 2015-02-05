#include <display/UpdateTask.h>

#include <carousel/logging/LoggerFacade.h>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("UpdateTask");
}

//------------------------------------------------------------------------------
UpdateTask::UpdateTask(QWidget* widget, QObject *parent)
    : QObject(parent)
{
    QObject::connect(this, SIGNAL(callUpdate()), widget, SLOT(update()));
}

//------------------------------------------------------------------------------
void UpdateTask::draw(IDisplay &)
{
    Log.d("Emit update needed");
    emit callUpdate();
}

//------------------------------------------------------------------------------
