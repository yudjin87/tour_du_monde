#include "CartoBaseTool.h"

#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <carousel/utils/IServiceLocator.h>
#include <carousel/logging/LoggerFacade.h>

#include <QtGui/QMouseEvent>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("CartoBaseTool");
}

//------------------------------------------------------------------------------
CartoBaseTool::CartoBaseTool(const QString &text, QActionGroup *actionGroup)
    : ToolBase(text, actionGroup)
    , m_serviceLocator(nullptr)
{
}

//------------------------------------------------------------------------------
CartoBaseTool::CartoBaseTool(const QIcon &icon, const QString &text, QActionGroup *actionGroup)
    : ToolBase(icon, text, actionGroup)
    , m_serviceLocator(nullptr)
{

}

//------------------------------------------------------------------------------
void CartoBaseTool::initialize(IServiceLocator *serviceLocator)
{
    ToolBase::initialize(serviceLocator);
    m_serviceLocator = serviceLocator;
}

//------------------------------------------------------------------------------
void CartoBaseTool::onMouseMove(QMouseEvent *event)
{
    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    DisplayTransformation* transform = display->transformation();
    QPointF mapPoint = transform->toMapPoint(event->pos());

    Log.d(QString("x: %1, y: %2").arg(mapPoint.x()).arg(mapPoint.y()));
}

//------------------------------------------------------------------------------
