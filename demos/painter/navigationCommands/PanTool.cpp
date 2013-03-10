#include "PanTool.h"

#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QMouseEvent>

#include <QtDebug>

//------------------------------------------------------------------------------
PanTool::PanTool()
    : ToolBase("Pan")
    , m_app(nullptr)
{
    setIcon(QIcon(":/navigation/images/pan.png"));
    setIconVisibleInMenu(true);
}

//------------------------------------------------------------------------------
void PanTool::execute()
{
    ToolBase::execute();
    IServiceLocator &locator = m_app->serviceLocator();

    QGraphicsScene *scene = locator.locate<QGraphicsScene>();
    QGraphicsView *view = scene->views().first();
    view->setDragMode(QGraphicsView::ScrollHandDrag);
//    view->fitInView(view->sceneRect());
}

//------------------------------------------------------------------------------
void PanTool::initialize(QObject *ip_startUpData)
{
    ToolBase::initialize(ip_startUpData);
    m_app = qobject_cast<AbstractApplication *>(ip_startUpData);
    if (m_app == nullptr)
        return;
}
//------------------------------------------------------------------------------
void PanTool::onMouseMove(QMouseEvent *ip_event)
{
    qDebug() << ip_event->x() << ip_event->y();
}

//------------------------------------------------------------------------------
void PanTool::stopExecuting()
{
    ToolBase::stopExecuting();
    IServiceLocator &locator = m_app->serviceLocator();

    QGraphicsScene *scene = locator.locate<QGraphicsScene>();
    QGraphicsView *view = scene->views().first();
    view->setDragMode(QGraphicsView::NoDrag);
}

//------------------------------------------------------------------------------
