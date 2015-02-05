#include "PanTool.h"

#include <carousel/utils/IServiceLocator.h>

#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <carto/IMap.h>
#include <carto/IPainterDocument.h>
#include <carto/IPainterDocumentController.h>

#include <QtGui/QMouseEvent>

//------------------------------------------------------------------------------
PanTool::PanTool()
    : ToolBase("Pan")
    , m_serviceLocator(nullptr)
    , m_tracked(false)
{
    setIcon(QIcon(":/navigation/images/pan.png"));
    setIconVisibleInMenu(true);
}

//------------------------------------------------------------------------------
void PanTool::execute()
{
    ToolBase::execute();
    IDisplay *display = m_serviceLocator->locate<IDisplay>();

    // TODO: move cursors to base class
    display->setCursor(Qt::OpenHandCursor);
}

//------------------------------------------------------------------------------
void PanTool::initialize(IServiceLocator *serviceLocator)
{
    ToolBase::initialize(serviceLocator);
    m_serviceLocator = serviceLocator;
}

//------------------------------------------------------------------------------
void PanTool::onMouseDown(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    m_tracked = true;
    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    display->panStart(event->pos());
    display->setCursor(Qt::ClosedHandCursor);
}

//------------------------------------------------------------------------------
void PanTool::onMouseMove(QMouseEvent *event)
{
    // TODO: move tracking to base class
    if (!m_tracked)
        return;

    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    display->panMoveTo(event->pos());
}

//------------------------------------------------------------------------------
void PanTool::onMouseUp(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    m_tracked = false;
    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    display->panStop();
    display->setCursor(Qt::OpenHandCursor);

    IPainterDocumentController* docController = m_serviceLocator->locate<IPainterDocumentController>();
    IPainterDocument *doc = docController->document();
    IMap *map = doc->map();
    map->refresh();
}

//------------------------------------------------------------------------------
void PanTool::stopExecuting()
{
    ToolBase::stopExecuting();

    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    display->unsetCursor();
}

//------------------------------------------------------------------------------
