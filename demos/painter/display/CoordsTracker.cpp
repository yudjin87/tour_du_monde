#include <display/CoordsTracker.h>
#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <components/interactivity/InputDispatcher.h>

#include <QtGui/QMouseEvent>
#include <QtWidgets/QStatusBar>

//------------------------------------------------------------------------------
CoordsTracker::CoordsTracker(const IDisplay *display, QStatusBar *statusBar, QObject *parent)
    : QObject(parent)
    , BaseInputReceiver()
    , m_display(display)
    , m_statusBar(statusBar)
    , m_dispatcher(new InputDispatcher())
{
    m_dispatcher->setReceiver(this);
    m_dispatcher->setSender(m_display->viewport());
    m_dispatcher->activate();
}

//------------------------------------------------------------------------------
bool CoordsTracker::onMouseMove(QMouseEvent *event)
{
    const DisplayTransformation* transform = m_display->transformation();
    QPointF mapPoint = transform->toMapPoint(event->pos());

    m_statusBar->showMessage(QString("x: %1, y: %2").arg(mapPoint.x()).arg(mapPoint.y()), 2000);

    // let's other objects to continue with this event
    return false;
}

//------------------------------------------------------------------------------



