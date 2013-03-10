#include "GraphicsPoinItem.h"

#include <QtGui/QPainter>

//------------------------------------------------------------------------------
GraphicsPoinItem::GraphicsPoinItem(const QPointF &data)
    : m_data(data)
{
}

//------------------------------------------------------------------------------
QRectF GraphicsPoinItem::boundingRect() const
{
    return QRectF(m_data, QSize(5, 5));
}

//------------------------------------------------------------------------------
void GraphicsPoinItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawEllipse(m_data, 3 / painter->transform().m11(), 3 / painter->transform().m22());
}

//------------------------------------------------------------------------------
