#ifndef COORDSTRACKER_H
#define COORDSTRACKER_H

#include <display/display_api.h>
#include <components/interactivity/BaseInputReceiver.h>
#include <components/interactivity/IInputDispatcher.h>
#include <QtCore/QObject>

#include <memory>

class QStatusBar;
class IDisplay;

class CoordsTracker : public QObject, public BaseInputReceiver
{
public:
    CoordsTracker(const IDisplay *display, QStatusBar* statusBar, QObject *parent);
    bool onMouseMove(QMouseEvent *event) override;

private:
    const IDisplay *m_display;
    QStatusBar *m_statusBar;
    std::unique_ptr<IInputDispatcher> m_dispatcher;
};
#endif // COORDSTRACKER_H
