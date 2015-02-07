#include <carto/FeatureLayerDrawingTask.h>
#include <display/FeatureRenderer.h>
#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QThread>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

#include <chrono>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("FLDrawTask");
}

FeatureLayerDrawingTask::FeatureLayerDrawingTask(IFeatureClass::FeatureList &&features, FeatureRenderer *renderer, QObject *parent)
    : QObject(parent)
    , IDrawingTask()
    , m_features(std::move(features))
    , m_renderer(renderer)
{
}

FeatureLayerDrawingTask::~FeatureLayerDrawingTask()
{
}

void FeatureLayerDrawingTask::draw(IDisplay &display)
{
    typedef std::chrono::system_clock Clock;
    typedef std::chrono::milliseconds milliseconds;

    const Clock::time_point started = Clock::now();

    QPixmapPtr tmp = display.createPixmap();
    {
        const DisplayTransformation* transform = display.transformation();
        const QTransform &viewport = transform->transform();

        QPainter painter(tmp.get());
        painter.setTransform(viewport, false);
        //QThread::msleep(1500);
        m_renderer->draw(m_features, &painter);
    }
    Clock::time_point finishedDrawOnly = Clock::now();
    milliseconds msOnly = std::chrono::duration_cast<milliseconds>(finishedDrawOnly - started);

    QPixmap& pixmap = display.lockPixmap();
    QPainter painter(&pixmap);
    painter.drawPixmap(0, 0, *tmp);
    display.unlockPixmap();

    Clock::time_point finished = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(finished - started);

    Log.d(QString("Drawing task (%1 features): Full %2, raw drawing: %3 ms").arg(m_features.size()).arg(ms.count()).arg(msOnly.count()));
}

