#include "PanTool.h"

#include <utils/IServiceLocator.h>

#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtGui/QMouseEvent>

#include <QtDebug>

//------------------------------------------------------------------------------
PanTool::PanTool()
    : ToolBase("Pan")
    , m_serviceLocator(nullptr)
{
    setIcon(QIcon(":/navigation/images/pan.png"));
    setIconVisibleInMenu(true);
}

//------------------------------------------------------------------------------
void PanTool::execute()
{
    ToolBase::execute();

    QGraphicsScene *scene = m_serviceLocator->locate<QGraphicsScene>();
    QGraphicsView *view = scene->views().first();
    view->setDragMode(QGraphicsView::ScrollHandDrag);
}

//------------------------------------------------------------------------------
void PanTool::initialize(IServiceLocator *serviceLocator)
{
    ToolBase::initialize(serviceLocator);
    m_serviceLocator = serviceLocator;
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

    QGraphicsScene *scene = m_serviceLocator->locate<QGraphicsScene>();
    QGraphicsView *view = scene->views().first();
    view->setDragMode(QGraphicsView::NoDrag);
}

//------------------------------------------------------------------------------
