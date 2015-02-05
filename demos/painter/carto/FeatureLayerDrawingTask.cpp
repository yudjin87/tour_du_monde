#include <carto/FeatureLayerDrawingTask.h>
#include <display/FeatureRenderer.h>
#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <carousel/logging/LoggerFacade.h>

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
    Log.d(QString("Drawing task [0x%1] created").arg((qlonglong)this, 0, 16));
}

FeatureLayerDrawingTask::~FeatureLayerDrawingTask()
{
    Log.d(QString("Drawing task [0x%1] deleted").arg((qlonglong)this, 0, 16));
}

void FeatureLayerDrawingTask::draw(IDisplay &display)
{
    typedef std::chrono::system_clock Clock;
    typedef std::chrono::milliseconds milliseconds;

    const Clock::time_point started = Clock::now();

    QPixmap* pixmap = display.lockPixmap();

    DisplayTransformation* transform = display.transformation();
    const QTransform &viewport = transform->transform();

    QPainter painter(pixmap);
    painter.setTransform(viewport, false);

    m_renderer->draw(m_features, &painter);
    display.unlockPixmap();

    Clock::time_point finished = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(finished - started);
    Log.d(QString("Drawing task (%1 features): %2 ms").arg(m_features.size()).arg(ms.count()));
}

